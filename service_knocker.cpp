#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "service_knocker.h"

/* Public */
yn0014::ServiceKnocker::ServiceKnocker(std::string host)
{
    this->hostIP = resolveHost(host);
}

int yn0014::ServiceKnocker::knock()
{
    this->result = 200;
    return 0;
}

/* Private */
std::string yn0014::ServiceKnocker::resolveHost(std::string host)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, "");
    boost::asio::ip::tcp::endpoint endp = *resolver.resolve(query);
    return endp.address().to_string();
}
