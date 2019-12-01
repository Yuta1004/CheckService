#include <string>
#include "network_connector.h"

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr) : Connector(ipAddr, 80)
{
    /* do nothing */
}

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr, int32_t port) : Connector(ipAddr, port)
{
    /* do nothing */
}


yn0014::net::TCPConnector::~TCPConnector()
{
    /* do nothing */
}

void yn0014::net::TCPConnector::send(std::string msg)
{
    /* TODO */
}

std::string yn0014::net::TCPConnector::getRecv()
{
    /* TODO */
    return "";
}
