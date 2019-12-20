#include <iostream>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include "../net/tcp_connector.h"

using std::cout;
using std::endl;

int main()
{
    // 172.217.26.14  => google.com
    // 153.120.168.14 => www.yuge.ac.jp
    yn0014::net::TCPConnector tcpA("153.120.168.14");
    tcpA.sendMsg("GET / HTTP/1.0\r\n\r\n");
    /* tcpA.sendMsg("GET / HTTP/1.0\r\nUser-Agent:yn0014-TCPConnector\r\n\n"); */
    cout << tcpA.getRecv() << endl;
}
