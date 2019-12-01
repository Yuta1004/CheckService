#include "../net/network_connector.h"

int main()
{
    // 172.217.26.14 => google.com
    yn0014::net::TCPConnector tcpA("172.217.26.14");
    yn0014::net::TCPConnector tcpB("172.217.26.14", 80);
}
