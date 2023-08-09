#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./wrap.h"
#define MAXLINE 100
#define SERV_PORT 7838
#define CLI_PORT 9000
int main(int argc, char *argv[])
{
	struct sockaddr_in seraddr,cliaddr;
	int sockfd, len;
	char buf[MAXLINE];
	socklen_t seraddr_len;
	//create socket
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	//bind
	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliaddr.sin_port = htons(CLI_PORT);
	Bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

	while (1) {
		seraddr_len=sizeof(seraddr);
		len = recvfrom(sockfd,buf,MAXLINE,0,(struct sockaddr *)&seraddr,&seraddr_len);
		if (len < 0) 
		{
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		buf[len] = '\0';
		printf("recive come from %s:%d message:%s\n",
			inet_ntoa(seraddr.sin_addr), ntohs(seraddr.sin_port), buf);
	}
	close(sockfd);
	return 0;
}
