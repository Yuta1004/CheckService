#include <string>
#include <iostream>
#include <vector>
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

