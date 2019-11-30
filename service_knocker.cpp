#include <iostream>
#include <string>
#include "service_knocker.h"

/* Public */
yn0014::ServiceKnocker::ServiceKnocker(std::string host)
{
    this->hostIP = resolveHost(host);
}

int yn0014::ServiceKnocker::knock()
{
    this->result = 200;
    return 0;
}

/* Private */
std::string yn0014::ServiceKnocker::resolveHost(std::string host)
{
    return "";
}
