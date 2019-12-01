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

void yn0014::net::Connector::closeSock()
{
    if(sock != 0) close(sock);
}
