#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLEN 100

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("%s [ip] [post]\n",argv[0]);
		return 0;
	}
	//creat socket
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("create socket error!\n");
		return 1;
	}
	//设置socket属性使得处于TIME_WAIT状态下的socket可以重复绑定。
	int flag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&flag, sizeof(flag));
	//bind  bind函数的作用是将套接字绑定一个IP地址和端口号，因为这两个元素可以在网络环境中唯一地址表示一个进程 不绑定系统则会随机分配
	struct sockaddr_in seraddr;
	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	//seraddr.sin_addr.s_addr = htonl(argv[1]);//INADDR_ANY 表示可以跟任何（any）地址通信---> 0.0.0.0
	inet_pton(AF_INET,argv[1],&seraddr.sin_addr.s_addr);	
	seraddr.sin_port = htons(atoi(argv[2]));	
	if(bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr))==-1)
	{
		perror("bind error\n");
        close(sockfd);
        return 2;
	}
	//listen
	if(listen(sockfd,128)==-1)
	{
		perror("listen error\n");
		close(sockfd);
		return 3;
	}

	printf("bind and listen success!wait accept...\n");
	//accept
	struct sockaddr_in cliaddr;
	char buf[MAXLEN];
	while(1)
	{
		socklen_t len=sizeof(cliaddr);
		//会将accept到的套接字的地址和端口存入到cliaddr结构体,并返回其文件描述符 &len是传入传出参数,会返回其真实长度
		int con_fd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
		if(con_fd < 0){
            perror("accept error\n");
			close(sockfd);
            return 4;
        }
		printf("get connect,ip is : %s port is : %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		//数据处理
		int n=read(con_fd,buf,MAXLEN);
		for (int i = 0; i < n; i++)
			buf[i] = toupper(buf[i]);
		write(con_fd, buf, n);
		close(con_fd);
	}
	close(sockfd);
	return 0;
}
