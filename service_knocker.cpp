#include <iostream>
#include <string>
#include "service_knocker.hpp"

yn0014::ServiceKnocker::ServiceKnocker(std::string host) {}

int32_t yn0014::ServiceKnocker::knock()
{
    this->result = 200;
    return 0;
}

