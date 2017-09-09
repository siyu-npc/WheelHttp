/*************************************************************************
    > File Name: server.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: Sat 09 Sep 2017 10:48:50 AM CST
 ************************************************************************/

#include "server.h"
#include <errno.h>
#include <unistd.h>
#include <thread>
#include <arpa/inet.h>

WheelHttp::WheelHttp(uint16_t port){
    int httpd = socket(AF_INET,SOCK_STREAM,0);
    httpd_ = httpd;
    if (httpd == -1)
        throw server_error(errno);

    std::memset(&socket_,0,sizeof(sockaddr_in));
    socket_.sin_family = AF_INET;
    socket_.sin_port = htons(port);
    socket_.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(httpd,(sockaddr *)(&socket_),sizeof(socket_)) < 0)
        throw server_error(errno);

    if (port == 0){
        socklen_t len = sizeof(socket_);
        if (getsockname(httpd_,(sockaddr *)(&socket_),&len) == -1)
            throw server_error(errno);
    }
}

void WheelHttp::startup() {
    if (listen(httpd_,5) == -1)
        throw server_error(errno);

    sockaddr_in client;
    socklen_t clientdlen;
    int clientd;
    while (true){
        clientd = accept(httpd_,(sockaddr *)(&client),&clientdlen);
        if (clientd == -1)
            throw server_error(errno);

        clients_.push_back(clientd);

        //在新的线程中处理用户连接
        std::thread serve(&WheelHttp::handle,this,clientd);
        serve.join();
    }
}

void WheelHttp::handle(int clientd) {
    printf("Connection from %s : %d\n",getPeerIpAddress(clientd).c_str(),getPeerPort(clientd));
    char welcome[] = "Hello,Welcome";
    write(clientd,welcome,strlen(welcome));
}

uint16_t WheelHttp::port() const {
    return ntohs(socket_.sin_port);
}
std::string WheelHttp::getPeerIpAddress(int clientd) const {
    sockaddr_in clientSock;
    socklen_t clientSockLen = sizeof(clientSock);
    getpeername(clientd,(sockaddr *)(&clientSock),&clientSockLen);
    return std::string(inet_ntoa(clientSock.sin_addr));
}
uint16_t WheelHttp::getPeerPort(int clientd) const {
    sockaddr_in clientSock;
    socklen_t clientSockLen = sizeof(clientSock);
    getpeername(clientd,(sockaddr *)(&clientSock),&clientSockLen);
    return ntohs(clientSock.sin_port);

}
