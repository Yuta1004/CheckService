#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>
#include "dns_resolver.h"
#include "mystring/mystring.h"

using std::cout;
using std::cerr;
using std::endl;

bool checkIPv4Format(std::string strIP);

yn0014::DNSResolver::DNSResolver()
{
    masterServerIP = "8.8.8.8";     // Google DNS
}

yn0014::DNSResolver::DNSResolver(std::string masterServerIP)
{
    if(checkIPv4Format(masterServerIP)) {
        this->masterServerIP = masterServerIP;
    } else {
        cerr << "Bad IP Format : " << masterServerIP << endl;
        exit(1);
    }
}

bool checkIPv4Format(std::string strIP)
{
    std::vector<std::string> ipElems = yn0014::mystring::split(strIP, ".");
    if(ipElems.size() != 4)
        return false;

    for(uint32_t idx = 0; idx < 4; ++ idx) {
        uint32_t num = std::atoi(ipElems[idx].c_str());
        if(num < 0 || 255 < num)
            return false;
    }
    return true;
}
