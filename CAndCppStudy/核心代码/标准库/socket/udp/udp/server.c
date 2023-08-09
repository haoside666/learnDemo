#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include "./wrap.h"
#define MAXLINE 80
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("%s ip port\n",argv[0]);
		return 0;
	}
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int sockfd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, n;
	//create socket
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));

	int flag = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&flag, sizeof(flag));
	//bind bind函数的作用是将套接字绑定一个IP地址和端口号，因为这两个元素可以在网络环境中唯一地址表示一个进程 为了方便服务器一般都进行绑定
	//绑定的IP地址是本机网卡的IP,ifconfig命令下的IP均可,0.0.0..0代表本机所有网卡
	Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("Accepting connections ...\n");
	while (1) {
		cliaddr_len = sizeof(cliaddr);
		//数据处理 (无连接)
		/*
			接收端一般都是要获取发送端的真实ip+端口 所以后两个参数都是传入传出参数
			如tcp server的accept函数
   			  udp 的recvfrom函数

			发送端由自己控制,所以长度就不是传入传出参数,
			如tcp client的connect函数
   			  udp的sendto函数
		*/

		//对于服务器而言,收发信息都是对于客户端的.所以后两个都是填客户端ip+port
		n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
		if (n == -1)
			perr_exit("recvfrom error");
		printf("received from %s at PORT %d\n",
			inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
			ntohs(cliaddr.sin_port));
		printf("client: ");
		fflush(stdout);
		Write(STDOUT_FILENO, buf, n);
		for (i = 0; i < n; i++)
			buf[i] = toupper(buf[i]);
		n = sendto(sockfd, buf, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		if (n == -1)
			perr_exit("sendto error");
	}
	return 0;
}
