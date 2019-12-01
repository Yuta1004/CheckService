#include <iostream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include "network_connector.h"

using std::cout;
using std::cerr;
using std::endl;

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr) : TCPConnector(ipAddr, 80) {}

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr, int32_t port) : Connector(ipAddr, port)
{
    if(!createSock(IPPROTO_TCP))
        cerr << "Cannot create socket" << endl;

    if(!connectSock())
        cerr << "Cannot connect to host" << endl;
}


yn0014::net::TCPConnector::~TCPConnector()
{
    closeSock();
}

bool yn0014::net::TCPConnector::sendMsg(std::string msg)
{
    int32_t result = 0;
    const char *cmsg = msg.c_str();
    size_t cmsg_len = strlen(cmsg)+1;
    result = send(sock, cmsg, cmsg_len, 0);
    return result == (int32_t)cmsg_len;
}

std::string yn0014::net::TCPConnector::getRecv()
{
    int32_t result = 0;
    char recvBuf[BUFLEN];

    result = recv(sock, recvBuf, BUFLEN, 0);
    if(result < 0)
        return "";

    recvBuf[result] = '\0';
    return std::string(recvBuf);
}
