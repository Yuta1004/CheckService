#include <iostream>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include "../net/tcp_connector.hpp"

using std::cout;
using std::endl;

int main()
{
    // 172.217.26.14  => google.com
    // 153.120.168.14 => www.yuge.ac.jp
    // 52.69.186.44 => github.com
    uint8_t *resp;

    yn0014::net::TCPConnector tcpA("153.120.168.14");
    tcpA.sendMsg("GET / HTTP/1.0\r\n\r\n");
    resp = tcpA.getRecv();
    cout << (char*)resp << endl << endl;
    free(resp);

    yn0014::net::TCPConnector tcpB("52.69.186.44", 443);
    tcpB.startSSL();
    tcpB.sendMsg("GET /Yuta1004 HTTP/1.0\r\nHost: github.com\r\n\r\n");
    resp = tcpB.getRecv();
    cout << (char*)resp << endl << endl;
    free(resp);
}
