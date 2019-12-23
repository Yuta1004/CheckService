#include <iostream>
#include <string>
#include "service_knocker.hpp"
#include "net/tcp_connector.hpp"
#include "net/dns_resolver.hpp"
#include "net/util.hpp"
#include "mystring/mystring.hpp"

using std::cout;
using std::endl;

yn0014::ServiceKnocker::ServiceKnocker(std::string serviceURL)
{
    yn0014::net::DNSResolver resolver;
    url = new yn0014::net::util::URLParser(serviceURL);
    hostIP = resolver.resolve(url->host)[0];
}

yn0014::ServiceKnocker::~ServiceKnocker()
{
    delete(url);
}

int32_t yn0014::ServiceKnocker::knock()
{
    yn0014::net::TCPConnector conn(hostIP);
    conn.sendMsg(
        yn0014::mystring::format("GET %s HTTP/1.0\r\n\r\n", url->docpath.c_str())
    );
    resp = yn0014::mystring::split((const char*)conn.getRecv(), "\n");
    return (result = 200);
}

