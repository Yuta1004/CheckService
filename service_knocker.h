#ifndef SERVICE_NOCKER_H
#define SERVICE_NOCKER_H

#include <cstdint>
#include <string>

namespace yn0014 {

class ServiceKnocker{

private:
    std::string sUrl;
    uint32_t result;

public:
    ServiceKnocker(std::string sUrl);
    int knock();
};

}

#endif
