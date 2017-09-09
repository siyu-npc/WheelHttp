/*************************************************************************
    > File Name: server.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: Sat 09 Sep 2017 10:48:50 AM CST
 ************************************************************************/

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define WheelHttpPort 2520 //WheelHttp服务器默认端口号

class WheelHttp {
    sockaddr_in socket_;
    int httpd_;//套接字描述符
    std::list<int> clients_;//连接至服务器的客户套接字描述符集合
public:
    WheelHttp(uint16_t port = WheelHttpPort);

    uint16_t port() const;//返回端口号
    std::string getPeerIpAddress(int clientd) const;
    uint16_t getPeerPort(int clientd) const;

    void startup();//启动服务器开始监听并接受连接
    void handle(int clientd);//处理客户连接


};

/******************************************
 * 异常类server_error用于服务器运行过程中抛出异常
 * 异常输出的信息包括一个字符串以及相应的errno数值
 * ***************************************/
#include <exception>

class server_error : public std::exception {
    char message_[256];
public:
    server_error(int err = 0):std::exception(){
        memset(message_,0,256);
        if (err == 0) snprintf(message_,256,"Some unknown errors happened!");
        else snprintf(message_,256,"ErrMsg:%s,errno:%d",strerror(err),err);
    }
    const char * what() const noexcept {
        return message_;
    }
};

#endif //SERVER_H
