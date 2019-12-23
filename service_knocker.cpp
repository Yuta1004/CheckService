#include <iostream>
#include <string>
#include "service_knocker.hpp"
#include "net/dns_resolver.hpp"
#include "net/util.hpp"

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
    return (result = 200);
}

