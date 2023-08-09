#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include "./wrap.h"
#define MAXLINE 100
#define SERV_PORT 7838
#define CLI_PORT 9000
int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	int sockfd;
	char buf[MAXLINE];
	int len;
	//create socket
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	//设置socket属性
	int flag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&flag, sizeof(flag));
	int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));

	//bind
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("Accepting connections ...\n");

	cliaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.1.255", &cliaddr.sin_addr);
	cliaddr.sin_port = htons(CLI_PORT);

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		len = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		if (len == -1)
			perr_exit("sendto error");
	}
	Close(sockfd);	
	return 0;
}


