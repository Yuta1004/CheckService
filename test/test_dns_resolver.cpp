#include <iostream>
#include <vector>
#include <string>
#include "../net/dns_resolver.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    yn0014::net::DNSResolver resolver;

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
