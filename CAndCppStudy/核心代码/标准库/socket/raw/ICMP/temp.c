#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/time.h>
#define PACKET_SIZE     		4096

char sendpacket[PACKET_SIZE];
char recvpacket[PACKET_SIZE];

struct sockaddr_in from;

unsigned short cal_chksum(unsigned short *addr,int len);
int pack(int pid);
void send_packet(int sockfd, int pid,struct sockaddr_in dest_addr);
void recv_packet(int sockfd,int pid);


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


int pack(int pid)
{       
	int packsize;        
	struct icmp *icmp;           
	
	icmp=(struct icmp*)sendpacket;        
	icmp->icmp_type=ICMP_ECHO;  //类型8 请求回显     
	icmp->icmp_code=0;        
	icmp->icmp_cksum=0;        
	icmp->icmp_seq=0;        
	icmp->icmp_id=pid;        
	strcpy(icmp->icmp_data,"kuagu");
	packsize=8+strlen(icmp->icmp_data);         
	
	icmp->icmp_cksum=cal_chksum( (unsigned short *)icmp,packsize);         
	return packsize;
}


void send_packet(int sockfd,int pid, struct sockaddr_in dest_addr)
{       
	int packetsize,len;  
    packetsize=pack(pid);   	
	while(1)        
	{                      	                
		if( (len=sendto(sockfd,sendpacket,packetsize,0,(struct sockaddr *)&dest_addr,sizeof(dest_addr) ))<0  )                
		{       
			perror("sendto error");                        
			continue;                
		}else
            break;     
	}
	printf("send success! length=%d\n",len);
}


void recv_packet(int sockfd,int pid)
{       
	int fromlen;                     
	fromlen=sizeof(from);        
	while(1)        
	{               
		if(recvfrom(sockfd,recvpacket,sizeof(recvpacket),0,(struct sockaddr *)&from,&fromlen) <0)                
		{                             
			perror("recvfrom error");                        
			continue;                
		}                
		else
            break;           
	}
    int iphdrlen;        
	struct ip *ip;        
	struct icmp *icmp;                
	
	ip=(struct ip *)recvpacket;        
	iphdrlen=ip->ip_hl<<2;         
	icmp=(struct icmp *)(recvpacket+iphdrlen);   
	if( (icmp->icmp_type==ICMP_ECHOREPLY) && (icmp->icmp_id==pid) )        
	{       
		printf("recv success!\ndata:%s\n",icmp->icmp_data);    
	} 
}


int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in dest_addr;
	pid_t pid;                           
	int size=50*1024;        
    memset(sendpacket,0,PACKET_SIZE);
    memset(recvpacket,0,PACKET_SIZE);
	if(argc<2)        
	{       
		printf("usage:%s IP\n",argv[0]);                
		exit(1);        
	}        

	if( (sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP) )<0)       
   	{       
		perror("socket error");                
		exit(1);        
	}        

	setuid(getuid());
    //改变接收buf 
	setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size) );        
	
	bzero(&dest_addr,sizeof(dest_addr));        
	dest_addr.sin_family=AF_INET;
	inet_pton(AF_INET,argv[1],&dest_addr.sin_addr.s_addr);        	     

	pid=getpid(); 
	send_packet(sockfd,pid,dest_addr);
	recv_packet(sockfd,pid);
	close(sockfd); 
	return 0;
}

