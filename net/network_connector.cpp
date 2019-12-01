#include <string>
#include <cstdint>
#include "network_connector.h"

yn0014::net::Connector::Connector(std::string ipAddr, int port)
{
    this->ipAddr = ipAddr;
    this->port = port;
}

yn0014::net::Connector::~Connector()
{
    /* do nothing */
}

std::string yn0014::net::Connector::getIPAddr()
{
    return ipAddr;
}

int32_t yn0014::net::Connector::getPort()
{
    return port;
}

