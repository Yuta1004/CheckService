#ifndef NETWORK_CONNECTOR_H
#define NETWORK_CONNECTOR_h

#include <cstdint>
#include <string>

namespace yn0014 {

    namespace net {

        class Connector {

        public:
            Connector(std::string ipAddr, int32_t port);

            std::string getIPAddr();
            int32_t getPort();

            virtual ~Connector() = 0;
            virtual void send(std::string msg) = 0;
            virtual std::string getRecv() = 0;

        private:
            std::string ipAddr, recvMessage;
            int32_t port;

        };

        class TCPConnector : Connector {

        public:
            TCPConnector(std::string ipAddr);
            TCPConnector(std::string ipAddr, int32_t port);
            ~TCPConnector();
            void send(std::string msg);
            std::string getRecv();

        };

    }
}

#endif
