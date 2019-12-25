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
            std::vector<std::string> resolve(std::string hostURL);

        private:
            std::string masterServerIP;
            uint8_t *makeDNSReqMsg(std::string hostURL);
            std::vector<std::string> parseDNSResMsg(uint8_t *msg, size_t qb_len);

        };

    }
}


#endif
