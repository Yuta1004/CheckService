#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <vector>
#include <string>

namespace yn0014 {

    namespace net {

        namespace util {

            bool checkIPv4Format(std::string strIP);

            std::string getRedirectURL(std::vector<std::string> resp);

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
