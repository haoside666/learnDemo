#include <sys/types.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>
#include <netdb.h>
#include "./wrap.h"
#define MAXLINE 1500
#define SERV_PORT 7838
#define CLIENT_PORT 9000
#define GROUP "239.0.0.2"

int main(int argc, char **argv)
{
	struct sockaddr_in localaddr;
	struct in_addr ia;
	int sockfd,len;
	char buf[MAXLINE];
	struct ip_mreqn group;
	
	//create socket
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	
	//初始化本地端地址
	bzero(&localaddr,sizeof(localaddr));
    localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    localaddr.sin_port = htons(CLIENT_PORT);		
	Bind(sockfd,(struct sockaddr*)&localaddr,sizeof(localaddr));   
	

	//设置组地址
	inet_pton(AF_INET,GROUP,&group.imr_multiaddr);
	//本地任意ip
	inet_pton(AF_INET,"0,0,0,0",&group.imr_address);
	//设置网卡信息
	group.imr_ifindex=if_nametoindex("ens33"); 	
	//设置client加入多播组
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group,sizeof(group));
	while(1)
	{
		len=recvfrom(sockfd,buf,sizeof(buf),0,NULL,0);
		printf("len=%d\n",len);
		write(STDOUT_FILENO,buf,len);
	}
} 

