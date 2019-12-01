#include <string>
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

