#ifndef NETWORK_CONNECTOR_H
#define NETWORK_CONNECTOR_h

#include <cstdint>
#include <string>

#define BUFLEN 1000

namespace yn0014 {

    namespace net {

        class Connector {

        public:
            Connector(std::string ipAddr, int32_t port);
            virtual ~Connector() = 0;
            virtual bool sendMsg(std::string msg) = 0;
            virtual std::string getRecv() = 0;

        protected:
            std::string ipAddr;
            int32_t sock, port;
            void closeSock();

        };

        class TCPConnector : Connector {

        public:
            TCPConnector(std::string ipAddr);
            TCPConnector(std::string ipAddr, int32_t port);
            ~TCPConnector();
            bool sendMsg(std::string msg);
            std::string getRecv();

        private:
            bool createSock();
            bool connectSock();

        };

    }
}

#endif
