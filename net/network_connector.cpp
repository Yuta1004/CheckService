#include <string>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "network_connector.h"

yn0014::net::Connector::Connector(std::string ipAddr, int port)
{
    this->ipAddr = ipAddr;
    this->port = port;
}

yn0014::net::Connector::~Connector()
{
    closeSock();
}

std::string yn0014::net::Connector::getIPAddr()
{
    return ipAddr;
}

int32_t yn0014::net::Connector::getPort()
{
    return port;
}

int32_t yn0014::net::Connector::getSock()
{
    return sock;
}

bool yn0014::net::Connector::createSock(int32_t socketType)
{
    // 入力検証
    if(socketType != IPPROTO_TCP && socketType != IPPROTO_UDP)
        return false;

    // ソケット生成
    sock = socket(AF_INET, SOCK_STREAM, socketType);
    return sock < 0;
}

bool yn0014::net::Connector::connectSock()
{
    // 接続先の情報
    struct sockaddr_in sc_addr;
    memset(&sc_addr, 0, sizeof(sc_addr));
    sc_addr.sin_family = AF_INET;
    sc_addr.sin_addr.s_addr = inet_addr(ipAddr.c_str());
    sc_addr.sin_port = htons(port);

    // 接続
    return connect(sock, (struct sockaddr *)&sc_addr, sizeof(sc_addr)) < 0;
}

void yn0014::net::Connector::closeSock()
{
    if(sock != 0) close(sock);
}
