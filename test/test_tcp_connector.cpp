#include "../net/network_connector.h"

int main()
{
    yn0014::net::TCPConnector tcpA("1.2.3.4");
    yn0014::net::TCPConnector tcpB("1.2.3.4", 80);
}
