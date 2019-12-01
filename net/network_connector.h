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

            virtual ~Connector();
            virtual void send(std::string msg);
            virtual std::string getRecv();

        private:
            std::string ipAddr, recvMessage;
            int32_t port;

        };

    }
}

#endif
