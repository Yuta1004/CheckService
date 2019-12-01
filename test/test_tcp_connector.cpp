#include <iostream>
#include <cstdio>
#include <cstring>
#include "../net/network_connector.h"

using std::cout;
using std::endl;

int main()
{
    // 172.217.26.14  => google.com
    // 153.120.168.14 => www.yuge.ac.jp
    yn0014::net::TCPConnector tcpA("153.120.168.14");
    tcpA.sendMsg("GET / HTTP/1.0\r\n\r\n");
    cout << tcpA.getRecv() << endl;
}
