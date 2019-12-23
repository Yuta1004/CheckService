#ifndef SERVICE_NOCKER_H
#define SERVICE_NOCKER_H

#include <cstdint>
#include <string>
#include <vector>
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
        int32_t result;
        std::string hostIP;
        std::vector<std::string> resp;
        yn0014::net::util::URLParser *url;

    };

}

#endif
