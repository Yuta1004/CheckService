#ifndef SERVICE_NOCKER_H
#define SERVICE_NOCKER_H

#include <cstdint>
#include <string>

#define SUCCESS(x)   (int)(x)/100==2
#define FAILED40x(x) (int)(x)/100==4
#define FAILED50x(x) (int)(x)/100==5

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
