#ifndef DNSRESOLVER_H
#define DNSRESOLVER_H

#include <vector>
#include <string>

namespace yn0014 {

    namespace net {

        class DNSResolver {

        public:
            DNSResolver();
            DNSResolver(std::string masterServerIP);
            std::vector<std::string> solve(std::string hostURL);

        private:
            std::string masterServerIP;

        };

    }
}


#endif
