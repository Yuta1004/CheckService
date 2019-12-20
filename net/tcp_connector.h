#ifndef NETWORK_CONNECTOR_H
#define NETWORK_CONNECTOR_h

#include <cstdint>
#include <string>

#define BUFLEN 1000

namespace yn0014 {

    namespace net {

        class TCPConnector {

        public:
            TCPConnector(std::string ipAddr);
            TCPConnector(std::string ipAddr, int32_t port);
            ~TCPConnector();
            bool sendMsg(void *msg, size_t len);
            bool sendMsg(std::string msg);
            int8_t *getRecv();

        private:
            std::string ipAddr;
            int32_t sock, port;
            bool createSock();
            bool connectSock();
            void closeSock();

        };

    }
}

#endif
