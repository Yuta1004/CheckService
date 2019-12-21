#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include "dns_resolver.h"
#include "tcp_connector.h"
#include "util.h"
#include "../mystring/mystring.h"

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

uint8_t *yn0014::net::DNSResolver::makeDNSReqMsg(std::string hostURL)
{

    std::vector<std::string> labels = yn0014::mystring::split(hostURL, ".");
    size_t hd_len = 6 * sizeof(int16_t), qb_len = 0;
    uint16_t header[6] = {0};
    uint8_t *qsecBody = (uint8_t*)calloc(labels.size()*15+5, sizeof(uint8_t));

    /* @DNS Query Header
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
    header[1] |= RD;

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
    qsecBody[qb_len++] = FINCODE;
    qsecBody[qb_len++] = FINCODE;

    // 組み立て
    uint8_t *msg = (uint8_t*)malloc(hd_len+qb_len);
    memcpy(msg, header, hd_len);
    memcpy(msg+hd_len, qsecBody, qb_len);
    free(qsecBody);
    return msg;
}

std::vector<std::string> yn0014::net::DNSResolver::parseDNSResMsg(uint8_t *msg, size_t qb_len)
{
    uint16_t flag = 0, resp = 0, offset = 0;

    /* @DNS Response Header
        - ID         16  (リクエストに指定したものと同じ)
        - FLAG       16  (リクエストヘッダーと同じ)
        - QUERYN     16  (クエリ数)
        - RESP       16  (応答数)
        - SERVER     16  (権威サーバ数)
        - ARCOUNT    16  (Additionalセクションの数)
    */
    memcpynum16(flag, msg+2);
    memcpynum16(resp, msg+6);
    if((flag & RCODE) != 0 || (flag & RA) != RA) {
        cerr << "Received error response" << endl;
        return std::vector<std::string>();
    }
    if(resp == 0) {
        cerr << "AnswerSection is empty" << endl;
        return std::vector<std::string>();
    }
    msg += 12;

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
    memcpynum16(offset, msg);
    if((offset & 0xc000) == 0) {
        offset = 0;
        while(msg[offset] != 0) ++ offset;
    } else {
        offset = 2;
    }
    msg += offset + 10;

    return std::vector<std::string>{
        yn0014::mystring::format("%d.%d.%d.%d", msg[0], msg[1], msg[2], msg[3])
    };
}
