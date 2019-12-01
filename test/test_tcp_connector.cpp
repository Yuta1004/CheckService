#include <iostream>
#include "../net/network_connector.h"

using std::cout;
using std::endl;

int main()
{
    // 172.217.26.14 => google.com
    yn0014::net::TCPConnector tcpA("172.217.26.14");
    if(tcpA.sendMsg("hello world!!!!"))
        cout << "Success" << endl;
    else
        cout << "Failed" << endl;
}
