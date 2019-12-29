#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "tcp_connector.hpp"

#define USESSL (1<<0)
#define error_with_exit(msg) { fprintf(stderr, msg); puts(""); exit(1); }
#define error_with_ret(msg) { fprintf(stderr, msg); puts(""); return false; }

using std::cout;
using std::cerr;
using std::endl;

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr) : TCPConnector(ipAddr, 80) {}

yn0014::net::TCPConnector::TCPConnector(std::string ipAddr, int32_t port)
{
    this->ipAddr = ipAddr;
    this->port = port;
    opt = 0;

    if(!createSock())
        error_with_exit("Cannot create socket");
}


yn0014::net::TCPConnector::~TCPConnector()
{
    closeSock();
}

bool yn0014::net::TCPConnector::startConn()
{
    return connectSock();
}

bool yn0014::net::TCPConnector::startSSL()
{
    opt |= USESSL;
    if(!sock)
        error_with_exit("Socket not initialized");

    if(!connectSSLSock())
        error_with_ret("Cannot start ssl connection");
    return true;
}

void yn0014::net::TCPConnector::closeConn(){
    closeSock();
}

bool yn0014::net::TCPConnector::sendMsg(void *msg, size_t len)
{
    int32_t result;
    if((opt & USESSL) == USESSL)
        result = SSL_write(ssl, msg, len);
    else
        result = send(sock, msg, len, 0);
    return result == (int32_t)len;
}

bool yn0014::net::TCPConnector::sendMsg(std::string msg)
{
    const char *cmsg = msg.c_str();
    size_t cmsg_len = strlen(cmsg)+1;
    return sendMsg((void*)cmsg, cmsg_len);
}

uint8_t* yn0014::net::TCPConnector::getRecv()
{
    int32_t result = 0;
    uint8_t *recvBuf = (uint8_t*)malloc(BUFLEN*sizeof(uint8_t));

    if((opt & USESSL) == USESSL)
        result = SSL_read(ssl, recvBuf, BUFLEN);
    else
        result = recv(sock, recvBuf, BUFLEN, 0);

    if(result < 0)
        return NULL;
    recvBuf[result] = '\0';
    return recvBuf;
}

bool yn0014::net::TCPConnector::createSock()
{
    // ソケット生成
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return sock > 0;
}

bool yn0014::net::TCPConnector::connectSock()
{
    // 接続先の情報
    struct sockaddr_in sc_addr;
    memset(&sc_addr, 0, sizeof(sc_addr));
    sc_addr.sin_family = AF_INET;
    sc_addr.sin_addr.s_addr = inet_addr(ipAddr.c_str());
    sc_addr.sin_port = htons(port);

    // 接続
    setBlocking(false);
    if(connect(sock, (struct sockaddr *)&sc_addr, sizeof(sc_addr)) >= 0)
        error_with_ret("Cannot connect to host");

    // 接続成功確認
    int32_t ret, val_opt;
    socklen_t int_size = sizeof(int);
    fd_set myset;
    struct timeval tval;
    if(errno != EINPROGRESS)
        error_with_ret("Error in connection...");

    do {
        // レスポンス受信
        tval.tv_sec = 5;
        tval.tv_usec = 0;
        FD_ZERO(&myset);
        FD_SET(sock, &myset);
        ret = select(sock+1, NULL, &myset, NULL, &tval);

        // 受信 -> エラーチェック
        if(ret > 0) {
            if(getsockopt(sock, SOL_SOCKET, SO_ERROR, (void*)(&val_opt), &int_size) < 0)
                error_with_ret("Error in getsockopt");
            if(val_opt)
                error_with_ret("Error in delayed connection...");
            break;
        }

        // 接続エラー検出
        if(ret < 0 && errno != EINTR)
            error_with_ret("Error in connecting...");

        // タイムアウト検出
        error_with_ret("Connection TIMEOUT!!");
    } while(1);

    setBlocking(true);
    return true;
}

bool yn0014::net::TCPConnector::connectSSLSock()
{
    auto sslAssert = [](bool cond) {
        if(!cond)
            ERR_print_errors_fp(stderr);
        return cond;
    };

    // エラー読み込み & 初期化
    SSL_load_error_strings();
    SSL_library_init();

    // CTX生成 -> 接続
    ctx = SSL_CTX_new(TLSv1_2_client_method());
    ssl = SSL_new(ctx);
    return
        sslAssert(SSL_set_fd(ssl, sock) != 0)
            &&
        sslAssert(SSL_connect(ssl) == 1);
}

void yn0014::net::TCPConnector::closeSock()
{
    if((opt & USESSL) == USESSL) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        ERR_free_strings();
        opt &= ~USESSL;
    }
    if(sock != 0)
        close(sock);
}

bool yn0014::net::TCPConnector::setBlocking(bool enable_block)
{
    int64_t args;
    if((args = fcntl(sock, F_GETFL, NULL)) < 0)
        error_with_ret("Faild to get sock_args");

    if(enable_block)
        args &= ~(O_NONBLOCK);
    else
        args |= O_NONBLOCK;

    return (fcntl(sock, F_SETFL, args) >= 0);
}

