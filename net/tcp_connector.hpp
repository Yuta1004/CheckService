#ifndef NETWORK_CONNECTOR_H
#define NETWORK_CONNECTOR_H

#include <cstdint>
#include <string>
#include <openssl/ssl.h>

#define BUFLEN 1000
#define TIMEOUT 5

namespace yn0014 {

    namespace net {

        class TCPConnector {

        public:
            TCPConnector(std::string ipAddr);
            TCPConnector(std::string ipAddr, int32_t port);
            ~TCPConnector();
            bool startConn();
            bool startSSL();
            void closeConn();
            bool sendMsg(void *msg, size_t len);
            bool sendMsg(std::string msg);
            uint8_t *getRecv();

        private:
            std::string ipAddr;
            int32_t sock, port, opt;
            SSL *ssl;
            SSL_CTX *ctx;
            bool createSock();
            bool connectSock();
            bool connectSSLSock();
            void closeSock();
            bool setBlocking(bool val);

        };

    }
}

#endif
