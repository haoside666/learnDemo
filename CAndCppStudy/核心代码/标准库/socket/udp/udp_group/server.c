#include <sys/types.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>
#include "./wrap.h"
#define MAXLINE 1500
#define SERV_PORT 7838
#define CLIENT_PORT 9000
#define GROUP "239.0.0.2"
int main(int argc, char **argv)
{
    struct sockaddr_in seraddr, cliaddr;
    int sockfd;
    char buf[MAXLINE];
	struct ip_mreqn group;
	//create socket
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);	
    
	//bind
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    seraddr.sin_port = htons(SERV_PORT);		
	Bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));       

	//设置组地址
	inet_pton(AF_INET,GROUP,&group.imr_multiaddr);
	//本地任意ip
	inet_pton(AF_INET,"0,0,0,0",&group.imr_address);
	//设置网卡信息
	group.imr_ifindex=if_nametoindex("ens33"); 
	//设置服务器端属性
	setsockopt(sockfd, IPPROTO_IP,IP_MULTICAST_IF, &group,sizeof(group));

	//构造client地址 IP+端口
    bzero(&cliaddr,sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
	inet_pton(AF_INET,GROUP,&cliaddr.sin_addr.s_addr);
    cliaddr.sin_port = htons(CLIENT_PORT);		
    
   
    while(1) {
		fgets(buf,sizeof(buf),stdin);
		sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));			
    }
	close(sockfd);
	return 0;
}

