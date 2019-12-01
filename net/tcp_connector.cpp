#include <iostream>
#include <string>
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

void yn0014::net::TCPConnector::send(std::string msg)
{
    /* TODO */
}

std::string yn0014::net::TCPConnector::getRecv()
{
    /* TODO */
    return "";
}
