#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include "../mystring/mystring.hpp"
#include "util.hpp"

using std::cout;
using std::cerr;
using std::endl;

bool yn0014::net::util::checkIPv4Format(std::string strIP)
{
    std::vector<std::string> ipElems = yn0014::mystring::split(strIP, ".");
    if(ipElems.size() != 4)
        return false;

    for(int32_t idx = 0; idx < 4; ++ idx) {
        int32_t num = std::atoi(ipElems[idx].c_str());
        if(num < 0 || 255 < num)
            return false;
    }
    return true;
}

std::string yn0014::net::util::getRedirectURL(std::vector<std::string> resp)
{
    char *utmp = (char*)malloc(50);
    std::vector<std::string> condStr{"Location: %s", "location: %s"};

    for(auto line : resp) {
        for(auto cond: condStr) {
            sscanf(line.c_str(), cond.c_str(), utmp);
            if(utmp[0] != 0)
                break;
        }
        if(utmp[0] != 0 && line == "")
            break;
    }

    return std::string(utmp);
}

yn0014::net::util::URLParser::URLParser(std::string url)
{
    // URLFormat =  <protocol>://<host>/<docpath>

    // <protocol>
    std::vector<std::string> protocol_host = yn0014::mystring::split(url, "://");
    protocol = protocol_host[0];
    if(protocol.size() == 0) {
        cerr << "Bad URL Format : " << protocol << endl;
        exit(1);
    }

    // <host>
    std::vector<std::string> host_docpath = yn0014::mystring::split(protocol_host[1], "/");
    host = host_docpath[0];

    // <docpah>
    size_t pro_host_len = protocol.size() + host.size() + 3;
    docpath = url.replace(url.begin(), url.begin()+pro_host_len, "");
    if(docpath == "")
        docpath = "/";
}

