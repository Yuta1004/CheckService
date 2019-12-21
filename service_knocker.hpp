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
    std::string hostIP;
    int32_t result;

    std::string resolveHost(std::string host);

public:
    ServiceKnocker(std::string host);
    int knock();
};

}

#endif
