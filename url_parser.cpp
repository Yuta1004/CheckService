#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "url_parser.h"
#include "mystring/mystring.h"

using std::cout;
using std::cerr;
using std::endl;

yn0014::URLParser::URLParser(std::string url)
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
}

