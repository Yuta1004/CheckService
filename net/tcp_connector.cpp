#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "tcp_connector.h"

using std::cout;
using std::cerr;
using std::endl;

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr) : TCPConnector(ipAddr, 80) {}

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr, int32_t port)
{
    this->ipAddr = ipAddr;
    this->port = port;

    if(!createSock()) {
        cerr << "Cannot create socket" << endl;
        exit(1);
    }

    if(!connectSock()) {
        cerr << "Cannot connect to host" << endl;
        exit(1);
    }
}


yn0014::net::TCPConnector::~TCPConnector()
{
    closeSock();
}

bool yn0014::net::TCPConnector::sendMsg(void *msg, size_t len)
{
    int32_t result = send(sock, msg, len, 0);
    return result == (int32_t)len;
}

bool yn0014::net::TCPConnector::sendMsg(std::string msg)
{
    const char *cmsg = msg.c_str();
    size_t cmsg_len = strlen(cmsg)+1;
    return sendMsg((void*)cmsg, cmsg_len);
}

uint8_t* yn0014::net::TCPConnector::getRecv()
{
    int32_t result = 0;
    uint8_t *recvBuf = (uint8_t*)malloc(BUFLEN*sizeof(uint8_t));

    result = recv(sock, recvBuf, BUFLEN, 0);
    if(result < 0)
        return NULL;
    recvBuf[result] = '\0';
    return recvBuf;
}

bool yn0014::net::TCPConnector::createSock()
{
    // ソケット生成
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return sock > 0;
}

bool yn0014::net::TCPConnector::connectSock()
{
    // 接続先の情報
    struct sockaddr_in sc_addr;
    memset(&sc_addr, 0, sizeof(sc_addr));
    sc_addr.sin_family = AF_INET;
    sc_addr.sin_addr.s_addr = inet_addr(ipAddr.c_str());
    sc_addr.sin_port = htons(port);

    // 接続
    return connect(sock, (struct sockaddr *)&sc_addr, sizeof(sc_addr)) >= 0;
}

void yn0014::net::TCPConnector::closeSock()
{
    if(sock != 0) close(sock);
}
