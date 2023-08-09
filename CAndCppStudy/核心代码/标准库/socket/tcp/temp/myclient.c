#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#define MAXLEN 8192
#define SERVERPORT 8000
int main(int argc,char *argv[])
{
	int len;
	char buf[MAXLEN];
	if (argc!=3) {
		printf("usage: %s [serverip] [serverport]\n",argv[0]);
		exit(1);
	}
	//creat socket
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("create socket error!\n");
		return 1;
	}
	struct sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	inet_pton(AF_INET,argv[1], &seraddr.sin_addr.s_addr);
	seraddr.sin_port = htons(atoi(argv[2]));
	//connect
	connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));//传入的是请求连接服务器的IP+port
	//数据处理
	while(1)
	{
		fgets(buf,MAXLEN,stdin);
		int n=send(sockfd, buf, strlen(buf),0);
		if(n>0)
		{
			printf("send success,size:%d\n",n);
		}else
		{
			perror("send error\n");
			return 0;
		}
		len = recv(sockfd, buf, MAXLEN,0);
		printf("Response from server:");
		fflush(stdout);
		write(STDOUT_FILENO, buf, len);
		printf("\n");
	}
	close(sockfd);	
	return 0;
}
