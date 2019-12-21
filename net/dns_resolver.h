#ifndef DNSRESOLVER_H
#define DNSRESOLVER_H

#include <vector>
#include <string>

#define QR      (0b1000000000000000)
#define OPCODE  (0b0111100000000000)
#define AA      (0b0000010000000000)
#define TC      (0b0000001000000000)
#define RD      (0b0000000100000000)
#define RA      (0b0000000010000000)
#define Z       (0b0000000001000000)
#define AD      (0b0000000000100000)
#define CD      (0b0000000000010000)
#define RCODE   (0b0000000000001111)
#define FINCODE (0xff/2-1)

#define NONE_STATEMENT ;
#define memcpynum16(dst, src) ((dst |= ((src)[0] << 8) | (src)[1]))
#define memcpynum32(dst, src) ((dst |= ((src)[0] << 24) | ((src)[1] << 16) | ((src)[2] << 8) | (src)[3]))

namespace yn0014 {

    namespace net {

        class DNSResolver {

        public:
            DNSResolver();
            DNSResolver(std::string masterServerIP);
            std::vector<std::string> solve(std::string hostURL);

        private:
            std::string masterServerIP;
            uint8_t *makeDNSReqMsg(std::string hostURL);
            std::vector<std::string> parseDNSResMsg(uint8_t *msg, size_t qb_len);

        };

    }
}


#endif
