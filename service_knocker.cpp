#include <string>
#include "service_knocker.h"

yn0014::ServiceKnocker::ServiceKnocker(std::string sUrl)
{
    this->sUrl = sUrl;
}

int yn0014::ServiceKnocker::knock()
{
    this->result = 200;
    return 0;
}
