#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXLEN 100
#define SERVERPORT 8000
int main(int argc,char *argv[])
{
	int len;
	char buf[MAXLEN];
	if (argc != 2) {
		printf("usage: ./client message\n");
		exit(1);
	}
	//creat socket
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("create socket error!\n");
		return 1;
	}
	char src[]="127.0.0.1";//填服务器ip地址,或回环地址
	struct sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	inet_pton(AF_INET,src, &seraddr.sin_addr.s_addr);
	seraddr.sin_port = htons(SERVERPORT);
	//connect
	connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));//传入的是请求连接服务器的IP+port
	//数据处理
	write(sockfd, argv[1], strlen(argv[1]));
	len = read(sockfd, buf, MAXLEN);
	printf("Response from server:");
	fflush(stdout);
	write(STDOUT_FILENO, buf, len);
	printf("\n");
	close(sockfd);
	
	return 0;
}
