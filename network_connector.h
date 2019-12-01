#ifndef NETWORK_CONNECTOR_H
#define NETWORK_CONNECTOR_h

#include <cstdint>
#include <string>

namespace yn0014 {

    namespace net {

        class Connector {

        public:
            Connector(std::string ipAddr, int32_t port);

            virtual ~Connector();
            virtual void send(std::string msg);
            virtual void wait();
            virtual std::string getRecv();


        private:
            std::string ipAddr, recvMessage;
            int32_t port;

        };

    }
}

#endif
