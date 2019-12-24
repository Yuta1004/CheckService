#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "service_knocker.hpp"
#include "net/tcp_connector.hpp"
#include "net/dns_resolver.hpp"
#include "net/util.hpp"
#include "mystring/mystring.hpp"

using std::cout;
using std::cerr;
using std::endl;

yn0014::ServiceKnocker::ServiceKnocker(std::string serviceURL)
{
    result = 0;
    yn0014::net::DNSResolver resolver;
    url = new yn0014::net::util::URLParser(serviceURL);
    hostIP = resolver.resolve(url->host)[0];
}

yn0014::ServiceKnocker::~ServiceKnocker()
{
    delete(url);
}

void yn0014::ServiceKnocker::knock()
{
    yn0014::net::TCPConnector conn(hostIP);
    conn.sendMsg(
        yn0014::mystring::format("GET %s HTTP/1.0\r\n\r\n", url->docpath.c_str())
    );
    resp = yn0014::mystring::split((const char*)conn.getRecv(), "\n");
}

int32_t yn0014::ServiceKnocker::getStatus()
{
    if(resp.size() == 0) {
        cerr << "Cannot parse status" << endl;
        return -1;
    }

    std::string statusStr = yn0014::mystring::split(resp[0], " ")[1];   // [HTTP/1.1, 200, OK]
    result = (int32_t)strtol(statusStr.c_str(), nullptr, 10);
    return result;
}

std::vector<std::string> yn0014::ServiceKnocker::getResp()
{
    return resp;
}
