#include <string>
#include <vector>
#include "../mystring/mystring.h"
#include "util.h"


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
