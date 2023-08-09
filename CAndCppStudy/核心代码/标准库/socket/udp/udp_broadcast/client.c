#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./wrap.h"
#define MAXLINE 100
#define SERV_PORT 7838
//客户端为发送方
int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	int sockfd, len,yes;
	char buf[MAXLINE];
	char localIp[INET_ADDRSTRLEN]="192.168.142.255";//本机的广播地址 
	socklen_t servaddr_len;
	//create socket
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	//设置socket属性
	yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, localIp, &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);


	while (fgets(buf, MAXLINE, stdin) != NULL) {
		len = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		if (len == -1)
			perr_exit("sendto error");
	}
	Close(sockfd);
	return 0;
}
