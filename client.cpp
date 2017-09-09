/*************************************************************************
    > File Name: client.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: Sat 09 Sep 2017 03:21:15 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>

int main(int argc,char **argv){
	sockaddr_in serverSock;
	memset(&serverSock,0,sizeof(serverSock));
	serverSock.sin_family = AF_INET;
	serverSock.sin_port = htons(2520);
	serverSock.sin_addr.s_addr = htonl(INADDR_ANY);
	int clientd = socket(AF_INET,SOCK_STREAM,0);
	int serverd;

	char message[256] = {0};
	serverd = connect(clientd,(sockaddr *)(&serverSock),sizeof(serverSock));
	if (serverd == -1)
		printf("Error:%s\n",strerror(errno));
	else {
		int n = 0;
		while(n = read(clientd,message,256)){
			if (n < 0){
				printf("Read error!\n");
				break;
			}
			else if (n == 0) break;
			else puts(message);
		}
	}
	return 0;
}
