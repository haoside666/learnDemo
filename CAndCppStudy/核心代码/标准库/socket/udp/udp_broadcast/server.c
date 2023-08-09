#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include "./wrap.h"
#define MAXLINE 100
#define SERV_PORT 7838
//这里采用服务器作为接收方
int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int sockfd;
	char buf[MAXLINE];
	int len;
	//create socket
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	//bind
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("Accepting connections ...\n");
	while (1) {
		cliaddr_len=sizeof(cliaddr);
		len = recvfrom(sockfd,buf,MAXLINE,0,(struct sockaddr *)&cliaddr,&cliaddr_len);
		if (len < 0) 
		{
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		buf[len] = '\0';
		printf("recive come from %s:%d message:%s\n",
			inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), buf);
	}
	close(sockfd);
	return 0;
}
