#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "service_knocker.hpp"
#include "net/tcp_connector.hpp"
#include "net/dns_resolver.hpp"
#include "net/util.hpp"
#include "mystring/mystring.hpp"

#define check_conn_error(result) { if(!(result)) return; }

using std::cout;
using std::cerr;
using std::endl;

yn0014::ServiceKnocker::ServiceKnocker(std::string serviceURL)
{
    result = 0;
    yn0014::net::DNSResolver resolver;
    url = new yn0014::net::util::URLParser(serviceURL);
    hostIP = resolver.resolve(url->host)[0];
}

yn0014::ServiceKnocker::~ServiceKnocker()
{
    delete(url);
}

void yn0014::ServiceKnocker::knock()
{
    // TCPConnectorセットアップ
    yn0014::net::TCPConnector *conn;
    if(url->protocol == "https") {
        conn = new yn0014::net::TCPConnector(hostIP, 443);
        check_conn_error(conn->startConn());
        check_conn_error(conn->startSSL());
    } else {
        conn = new yn0014::net::TCPConnector(hostIP);
        check_conn_error(conn->startConn());
    }

    // 送信->レスポンス受け取り
    check_conn_error(
        conn->sendMsg(
            yn0014::mystring::format(
                "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n",
                url->docpath.c_str(),
                url->host.c_str()
            )
        )
    );
    resp = yn0014::mystring::split((const char*)conn->getRecv(), "\n");
    conn->closeConn();
    delete(conn);
}

int32_t yn0014::ServiceKnocker::getStatus()
{
    if(resp.size() == 0) {
        cerr << "Cannot parse status" << endl;
        return -1;
    }

    std::string statusStr = yn0014::mystring::split(resp[0], " ")[1];   // [HTTP/1.1, 200, OK]
    result = (int32_t)strtol(statusStr.c_str(), nullptr, 10);
    return result;
}

std::vector<std::string> yn0014::ServiceKnocker::getResp()
{
    return resp;
}
