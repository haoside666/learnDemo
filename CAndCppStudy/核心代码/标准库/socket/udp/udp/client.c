#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./wrap.h"
#define MAXLINE 80
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("%s [ip] [port]\n",argv[0]);
		return 0;
	}
	struct sockaddr_in servaddr;
	int sockfd, n;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	socklen_t servaddr_len;
	//create socket
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		if (n == -1)
			perr_exit("sendto error");
		n = recvfrom(sockfd, buf, MAXLINE, 0, NULL, 0);//不关心则填NULL
		if (n == -1)
			perr_exit("recvfrom error");
		printf("server: ");
		fflush(stdout);
		Write(STDOUT_FILENO, buf, n);
	}
	Close(sockfd);
	return 0;
}
