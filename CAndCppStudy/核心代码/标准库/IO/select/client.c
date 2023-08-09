/* client.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "wrap.h"
#define MAXBUF 1024
#define SER_PORT 7838
int main(int argc, char *argv[])
{
	struct sockaddr_in seraddr;
	char buf[MAXBUF];
	int sockfd, len;
	if(argc<2)
	{
		printf("./client IP\n");
		exit(1);
	}
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	if (inet_aton(argv[1], (struct in_addr *) &seraddr.sin_addr.s_addr) == 0) 
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
	seraddr.sin_port = htons(SER_PORT);
	
	Connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	while (fgets(buf, MAXBUF, stdin) != NULL) {
		len=Write(sockfd, buf, strlen(buf));
		if (len < 0) {
			printf ("message send failure");
			break;
        } else
			printf("send success,%d byte send\n",len);
	}
	Close(sockfd);
	return 0;
}
