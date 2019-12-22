#include <iostream>
#include <string>
#include "service_knocker.hpp"

yn0014::ServiceKnocker::ServiceKnocker(std::string host)
{
    this->hostIP = resolveHost(host);
}

int32_t yn0014::ServiceKnocker::knock()
{
    this->result = 200;
    return 0;
}

std::string yn0014::ServiceKnocker::resolveHost(std::string host)
{
    return "";
}
