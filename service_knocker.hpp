#ifndef SERVICE_NOCKER_H
#define SERVICE_NOCKER_H

#include <cstdint>
#include <string>
#include "net/util.hpp"

#define SUCCESS(x)   (int)(x)/100==2
#define FAILED40x(x) (int)(x)/100==4
#define FAILED50x(x) (int)(x)/100==5

namespace yn0014 {

    class ServiceKnocker{

    public:
        ServiceKnocker(std::string serviceURL);
        ~ServiceKnocker();
        int32_t knock();

    private:
        yn0014::net::util::URLParser *url;
        std::string hostIP;
        int32_t result;

    };

}

#endif
