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

void yn0014::net::Connector::closeSock()
{
    if(sock != 0) close(sock);
}
