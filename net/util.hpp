#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <string>

namespace yn0014 {

    namespace net {

        namespace util {

            bool checkIPv4Format(std::string strIP);

            struct URLParser {
                std::string protocol;
                std::string host;
                std::string docpath;
                URLParser(std::string url);
            };

        }

    }

}

#endif
