#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include "dns_resolver.h"
#include "util.h"
#include "../mystring/mystring.h"

using std::cout;
using std::cerr;
using std::endl;

bool checkIPv4Format(std::string strIP);

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
    size_t hd_size = 6 * sizeof(uint16_t), qb_size = 0;
    uint16_t header[6] = {0};
    uint8_t *qsecBody = (uint8_t*)calloc(labels.size()*15+5, sizeof(uint8_t));

    // ** DNS Query Header **
    // - ID         16  C   (任意)
    // - QR         1   C   (問合せの場合は0)
    // - OPCODE     4   C   (通常クエリは0)
    // - AA         1   S   (管理権限のある応答の場合1)
    // - TC         1   S   (応答が切り詰められている場合1)
    // - RD         1   C   (名前解決要求、フルサービスリゾルバへのリクエストは1)
    // - RA         1   S   (名前解決可能な場合0)
    // - Z          1   -   (予約bit, 0にする)
    // - AD         1   S   (DNSECに成功した場合1)
    // - CD         1   C   (DNSSECを禁止する場合1)
    // - RCODE      4   S   (レスポンスステータス)
    // - QRCOUNT    16  C   (Questionセクションの数)
    // - ANCOUNT    16  S   (Answerセクションの数)
    // - NSCOUNT    16  S   (Authorityセクションの数)
    // - ARCOUNT    16  S   (Additionalセクションの数)
    header[1] |= RD;

    // ** DNS Qestion Section **
    // - size   1       (ラベルのサイズ)
    // - label  可変長  (ラベル, ASCII)
    for(auto part : labels) {
        qsecBody[qb_size++] = part.size();
        for(char c : part) {
            qsecBody[qb_size++] = c;
        }
    }
    qsecBody[qb_size++] = 0;
    qsecBody[qb_size++] = 1;
    qsecBody[qb_size++] = 0;
    qsecBody[qb_size++] = 1;
    qsecBody[qb_size++] = 0xff;

    // 組み立て
    uint8_t *msg = (uint8_t*)malloc(hd_size+qb_size);
    memcpy(msg, header, hd_size);
    memcpy(msg+hd_size, qsecBody, qb_size);
    free(qsecBody);
    return msg;
}
