#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include "./wrap.h"

#define MAXBUF 1024
#define SER_PORT 7838
int main(int argc, char **argv)
{
	int sockfd, new_fd,handlerfd;
	socklen_t clilen;
	struct sockaddr_in seraddr,cliaddr;
	char buf[MAXBUF];
	fd_set rfds,allfds;
	struct timeval tv;
	int retval, maxfd = -1,maxi;
	int client[FD_SETSIZE];/* FD_SETSIZE 默认为 1024 */
	int len,i;
	//creat socket
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);	
	//bind
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(SER_PORT);
	Bind(sockfd, (struct sockaddr *) &seraddr, sizeof(seraddr));
	//listen
	Listen(sockfd, 20);//设置监听队列长度最大20默认为128

	maxi = -1;/* client[]的下标 */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;/* 用-1初始化client[] */
	FD_ZERO(&allfds);
	FD_SET(0, &allfds);/* 构造select监控文件描述符集 */
	FD_SET(sockfd, &allfds);
	maxfd = sockfd;/* 初始化 */
	while(1)
	{
		rfds=allfds;		
		tv.tv_sec = 60;//设置延时时间为60秒
		tv.tv_usec = 0;
		//select
		retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);//中间三个参数分别监听读,写,错误文件集,均为传入传出参数
	    if (retval == -1) 
		{
			perror("select");
			exit(EXIT_FAILURE);
		} 
		else if (retval == 0) 
		{
	     		continue;
	    } 
		else
		{
			// new client connection 
	        if (FD_ISSET(sockfd, &rfds)) 
			{ 
	        	clilen = sizeof(cliaddr);
				new_fd = Accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
				printf("connect from %s at PORT %d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
				for (i = 0; i < FD_SETSIZE; i++)
				{
					if (client[i] < 0) {
						client[i] = new_fd; /* 保存accept返回的文件描述符到client[]里 */
						break;
					}
				}
				/* 达到select能监控的文件个数上限 1024 */
				if (i == FD_SETSIZE) {
					fputs("too many clients\n", stderr);
					exit(1);
				}
				FD_SET(new_fd, &allfds);/* 添加一个新的文件描述符到监控信号集里 */
				if (new_fd > maxfd)
					maxfd = new_fd; /* select第一个参数需要 */
				if (i > maxi)
					maxi = i;/* 更新client[]最大下标值 */
				if (--retval == 0)
					continue;/* 如果没有更多的就绪文件描述符继续回到上面select阻塞监听,负责处理未处理完的就绪文件描述符 */
   			}
			for (i = 0; i <= maxi; i++) {/* 检测哪个clients 有数据就绪 */
				if ((handlerfd=client[i]) < 0)
					continue;
				if (FD_ISSET(handlerfd, &rfds)) {
					if ((len = Read(handlerfd, buf, MAXBUF)) <= 0) {
					/* 当client关闭链接时，服务器端也关闭对应链接 */
						Close(handlerfd);
						FD_CLR(handlerfd, &allfds);/* 解除select监控此文件描述符 */
						client[i] = -1;
					} else {
						buf[len-1]='\0';
						printf ("read success :%s,%dbyte recv\n", buf, len);
					}
					if (--retval == 0)
						break;
				}
			}
	     }
	}
	close(sockfd);
	return 0;
}
