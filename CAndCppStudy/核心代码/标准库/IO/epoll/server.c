#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "wrap.h"
#define MAXLINE 80
#define SERV_PORT 7838
#define OPEN_MAX 1024
int main(int argc, char *argv[])
{
	int i, j, maxi, listenfd, connfd, sockfd;
	int nready, efd, res;
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	int client[OPEN_MAX];
	struct sockaddr_in cliaddr, servaddr;
	struct epoll_event tep, ep[OPEN_MAX];
	//creat socket
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	//bind
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	//listen
	Listen(listenfd, 20);

	for (i = 0; i < OPEN_MAX; i++)
		client[i] = -1;
	maxi = -1;
	efd = Epoll_create(OPEN_MAX);
	tep.events = EPOLLIN; tep.data.fd = listenfd;
	Epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);
	for ( ; ; ) {
		nready = Epoll_wait(efd, ep, OPEN_MAX, -1);/* 阻塞监听 */
		if (nready == -1)
			perr_exit("epoll_wait");
		for (i = 0; i < nready; i++) {
			if (!(ep[i].events & EPOLLIN))
				continue;
			if (ep[i].data.fd == listenfd) {
				clilen = sizeof(cliaddr);
				connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
				printf("receivedfrom:%satPORT:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
				for (j = 0; j < OPEN_MAX; j++)
					if (client[j] < 0) {
						client[j] = connfd;/* save descriptor */
						break;
					}
				if (j == OPEN_MAX)
					perr_exit("too many clients");
				if (j > maxi)
					maxi = j;/* max index in client[] array */
				tep.events = EPOLLIN; tep.data.fd = connfd;
				res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);
				if (res == -1)
					perr_exit("epoll_ctl");
			}
			else {
				sockfd = ep[i].data.fd;
				n = Read(sockfd, buf, MAXLINE);
				if (n == 0) {
					for (j = 0; j <= maxi; j++) {
						if (client[j] == sockfd) {
							client[j] = -1;
							break;
						}
					}
					Epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					Close(sockfd);
					printf("client[%d] closed connection\n", j);
				}
				else {
					for (j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
						Writen(sockfd, buf, n);
				}
			}
		}
	}
	close(listenfd);
	close(efd);
	return 0;
}
