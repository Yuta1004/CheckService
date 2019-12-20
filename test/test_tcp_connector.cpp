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
    tcpA.sendMsg("GET / HTTP/1.0\nUser-Agent:yn0014-TCPConnector\n\n");
    tcpA.getRecv();
}
