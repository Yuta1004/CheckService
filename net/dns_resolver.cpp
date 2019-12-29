#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include "dns_resolver.hpp"
#include "tcp_connector.hpp"
#include "util.hpp"
#include "../mystring/mystring.hpp"

#define QR      (0b1000000000000000)
#define OPCODE  (0b0111100000000000)
#define AA      (0b0000010000000000)
#define TC      (0b0000001000000000)
#define RD      (0b0000000100000000)
#define RA      (0b0000000010000000)
#define Z       (0b0000000001000000)
#define AD      (0b0000000000100000)
#define CD      (0b0000000000010000)
#define RCODE   (0b0000000000001111)
#define FINCODE (0xff/2-1)
#define NONE_STATEMENT ;
#define memcpynum16(dst, src) ((dst |= ((src)[0] << 8) | (src)[1]))
#define memcpynum32(dst, src) ((dst |= ((src)[0] << 24) | ((src)[1] << 16) | ((src)[2] << 8) | (src)[3]))

using std::cout;
using std::cerr;
using std::endl;

yn0014::net::DNSResolver::DNSResolver()
{
    masterServerIP = "8.8.8.8";     // Google DNS
}

yn0014::net::DNSResolver::DNSResolver(std::string masterServerIP)
{
    if(yn0014::net::util::checkIPv4Format(masterServerIP)) {
        this->masterServerIP = masterServerIP;
    } else {
        cerr << "Bad IP Format : " << masterServerIP << endl;
        exit(1);
    }
}

std::vector<std::string> yn0014::net::DNSResolver::resolve(std::string hostURL)
{
    uint8_t *reqMsg = makeDNSReqMsg(hostURL), *respMsg;
    size_t reqLen = ((uint16_t*)reqMsg)[0];
    reqLen = ((reqLen & 0xff00) >> 8) | ((reqLen & 0x00ff) << 8);
    reqLen += 2;

    yn0014::net::TCPConnector conn(masterServerIP, 53);
    conn.startConn();
    conn.sendMsg(reqMsg, reqLen);
    respMsg = conn.getRecv();
    conn.closeConn();

    std::vector<std::string> result = parseDNSResMsg(respMsg, reqLen-14);   // QuestionSectionの長さだけ欲しいのでヘッダーサイズを引く
    free(reqMsg);
    free(respMsg);
    return result;
}

uint8_t *yn0014::net::DNSResolver::makeDNSReqMsg(std::string hostURL)
{
    std::vector<std::string> labels = yn0014::mystring::split(hostURL, ".");
    size_t hd_len = 7 * sizeof(int16_t), qb_len = 0;
    uint16_t header[7] = {0};
    uint8_t *qsecBody = (uint8_t*)calloc(labels.size()*15+5, sizeof(uint8_t));

    /* @DNS Query Header(TCP)
        - SIZE       16  C   (パケットサイズ)
        - ID         16  C   (任意)
        - QR         1   C   (問合せの場合は0)
        - OPCODE     4   C   (通常クエリは0)
        - AA         1   S   (管理権限のある応答の場合1)
        - TC         1   S   (応答が切り詰められている場合1)
        - RD         1   C   (名前解決要求、フルサービスリゾルバへのリクエストは1)
        - RA         1   S   (名前解決可能な場合0)
        - Z          1   -   (予約bit, 0にする)
        - AD         1   S   (DNSECに成功した場合1)
        - CD         1   C   (DNSSECを禁止する場合1)
        - RCODE      4   S   (レスポンスステータス)
        - QRCOUNT    16  C   (Questionセクションの数)
        - ANCOUNT    16  S   (Answerセクションの数)
        - NSCOUNT    16  S   (Authorityセクションの数)
        - ARCOUNT    16  S   (Additionalセクションの数)
     */
    header[2] |= RD;
    header[3] = 1;

    /* @DNS Qestion Section
        - size   1       (ラベルのサイズ)
        - label  可変長  (ラベル, ASCII)
    */
    for(auto part : labels) {
        qsecBody[qb_len++] = part.size();
        for(char c : part) {
            qsecBody[qb_len++] = c;
        }
    }
    qsecBody[qb_len++] = 0;
    qsecBody[qb_len++] = 0;
    qsecBody[qb_len++] = 1;
    qsecBody[qb_len++] = 0;
    qsecBody[qb_len++] = 1;
    header[0] = hd_len+qb_len-2;

    // 組み立て
    uint8_t *msg = (uint8_t*)malloc(hd_len+qb_len);
    for(int32_t idx = 0; idx < (int32_t)hd_len; idx += 2) { // エンディアンの影響で素直にmemcpyが使えない
        msg[idx] = (header[idx/2] & 0xff00) >> 8;
        msg[idx+1] = header[idx/2] & 0x00ff;
    }
    memcpy(msg+hd_len, qsecBody, qb_len);
    free(qsecBody);
    return msg;
}

std::vector<std::string> yn0014::net::DNSResolver::parseDNSResMsg(uint8_t *msg, size_t qb_len)
{
    uint16_t flag = 0, resp = 0, offset = 0;

    /* @DNS Response Header(TCP)
        - SIZE       16  (パケットサイズ)
        - ID         16  (リクエストに指定したものと同じ)
        - FLAG       16  (リクエストヘッダーと同じ)
        - QUERYN     16  (クエリ数)
        - RESP       16  (応答数)
        - SERVER     16  (権威サーバ数)
        - ARCOUNT    16  (Additionalセクションの数)
    */
    memcpynum16(flag, msg+4);
    memcpynum16(resp, msg+8);
    if((flag & RCODE) != 0 || (flag & RA) != RA) {
        cerr << "Received error response" << endl;
        return std::vector<std::string>();
    }
    if(resp == 0) {
        cerr << "AnswerSection is empty" << endl;
        return std::vector<std::string>();
    }
    msg += 14;

    /* @DNS Response Question Section
         - QUERY      可変長  (送信したクエリがそのまま保存されている)
    */
    msg += qb_len;

    /* @DNS Response Answer Section
        - OFFSET     16  (00から始まる場合ドメインラベルそのまま、11の場合は圧縮情報)
        - A          16  (タイプA)
        - IN         16  (クラスIN)
        - TTL        32  (TTL)
        - IP         32  (解決結果)
    */
    std::vector<std::string> ipList;
    for(; resp > 0; -- resp) {
        memcpynum16(offset, msg);
        if((offset & 0xc000) == 0) {
            offset = 0;
            while(msg[offset] != 0) ++ offset;
        } else {
            offset = 2;
        }
        msg += offset + 10;
        ipList.emplace_back(yn0014::mystring::format("%d.%d.%d.%d", msg[0], msg[1], msg[2], msg[3]));
        msg += 4;
    }

    return ipList;
}
