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

#define ICMP_PACKET_SIZE 1024
#define MAXBUF 128

char key[MAXBUF];
char destaddr[16],localaddr[16];
int localport;

unsigned short cal_chksum(unsigned short *addr,int len);
void send_packet(int sockfd, int pid);

//crc32的校验计算方法
unsigned short cal_chksum(unsigned short *addr,int len)
{       
	int nleft=len;        
	int sum=0;        
	unsigned short *w=addr;        
	unsigned short answer=0;	    
	
	while(nleft>1)        
	{       
		sum+=*w++;                
		nleft-=2;        
	}
	
	if( nleft==1)        
	{       
		*(unsigned char *)(&answer)=*(unsigned char *)w;                
		sum+=answer;        
	}        

	sum=(sum>>16)+(sum&0xffff);        
	sum+=(sum>>16);        
	answer=~sum;        

	return answer;
}


void send_packet(int sockfd,int pid)
{       
	char buf[ICMP_PACKET_SIZE]="";
    struct icmp *icmp; 

    //开始填充icmp首部
    icmp=(struct icmp*)buf;       
	icmp->icmp_type=ICMP_ECHO;  //类型8 请求回显     
	icmp->icmp_code=0;        
	icmp->icmp_cksum=0;        
	icmp->icmp_seq=0;        
	icmp->icmp_id=pid;
	icmp->icmp_cksum=cal_chksum((unsigned short*)icmp,sizeof(struct icmp));
	//开始填充数据
	sprintf(icmp->icmp_data,"%s %15s %d",key,localaddr,localport);

	struct sockaddr_in dest_addr;
	dest_addr.sin_family=AF_INET;
	inet_pton(AF_INET,destaddr,&dest_addr.sin_addr.s_addr);
	int size=sizeof(icmp)+strlen(icmp->icmp_data);
	while(1)
	{
		if( sendto(sockfd,buf,size,0,(struct sockaddr *)&dest_addr,sizeof(dest_addr) )<0  )                
		{       
			perror("sendto error");                        
			continue;                
		}else
			break;	   
	}
	printf("send success! length=%d\n",size);
}

int main(int argc,char *argv[])
{
	int sockfd;	
	pid_t pid;	                           
	int size=50*1024;        

	if(argc!=5)        
	{       
		printf("usage:%s [dest_addr] [key] [localaddr] [localport]\n",argv[0]);                
		return 0;        
	}        
    setuid(getuid()); 

	if( (sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP) )<0)   
   	{       
		perror("socket error");                
		exit(1);        
	}        

    //改变接收buf大小 
	setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size) );        
		
	strcpy(destaddr,argv[1]);
	strcpy(key,argv[2]);
	strcpy(localaddr,argv[3]);
	localport=atoi(argv[4]);

	pid=getpid(); 
	send_packet(sockfd,pid);
	close(sockfd); 
	return 0;
}


