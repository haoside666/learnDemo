#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXLEN 100
#define SERVERPORT 8000

#define MAXBUF 4096
struct msgbuf
{
    long mtype;
    char mtext[MAXBUF];
};

struct msg
{
    long type;
    union
    {
        struct msgbuf mymsgbuf;
        char message[MAXBUF];
    }content;
};
int main(int argc,char *argv[])
{
	int len;
	char buf[MAXLEN];
	if (argc!=4) {
		printf("usage: %s [serverip] [serverport] [message]\n",argv[0]);
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
	//
	unsigned char package[MAXBUF];
	struct msg m;
	memset(&m, 0, sizeof(m));
	m.type=2;
	memcpy(m.content.message, argv[3], strlen(argv[3]));
	memcpy(package, &m, sizeof(struct msg));
	//数据处理
	write(sockfd, package, strlen(buf));
	//write(sockfd, argv[3], strlen(argv[3]));
	len = read(sockfd, buf, MAXLEN);
	printf("Response from server:");
	fflush(stdout);
	write(STDOUT_FILENO, buf, len);
	printf("\n");
	close(sockfd);
	
	return 0;
}
