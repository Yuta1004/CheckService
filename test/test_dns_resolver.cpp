#include <iostream>
#include <vector>
#include <string>
#include "../net/dns_resolver.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    std::string dnsServerIP;
    cout << "Please input address of DNS server : ";
    cin >> dnsServerIP;

    yn0014::net::DNSResolver resolver(dnsServerIP);

    while(true) {
        std::string inp;
        cout << ">> ";
        cin >> inp;

        if(inp == "q")
            break;

        std::vector<std::string> result = resolver.resolve(inp);
        for(auto ip : result)
            cout << ip << endl;
        cout << endl;
    }
}
