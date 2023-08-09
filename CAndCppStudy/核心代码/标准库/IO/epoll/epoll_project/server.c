#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include "./common.h"
#include "./wrap.h"

typedef void* (*Func)(void*);
int epoll_fd;

int in_createthread(Func run,void* p)
{
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
  pthread_t tt;
  pthread_create(&tt,&attr,run,p);
  return 0;
}
void* in_data_tran(void* p)
{
    int t[2];
    t[0]=((int*)p)[0];
    t[1]=((int*)p)[1];
    
    char buf[MAXBUF+1024];
    int len;   
    
    epoll_fd = Epoll_create(OPEN_MAX);   

    struct epoll_event ep_ev;
    ep_ev.events = EPOLLIN;
    ep_ev.data.fd = t[0];
    Epoll_ctl(epoll_fd,EPOLL_CTL_ADD,t[0],&ep_ev);
    ep_ev.events = EPOLLIN;
    ep_ev.data.fd = t[1];
    Epoll_ctl(epoll_fd,EPOLL_CTL_ADD,t[1],&ep_ev);
    
    struct epoll_event ready_ev[OPEN_MAX];
    int timeout = -1;
    int ret = 0;
    while(1){
        ret = Epoll_wait(epoll_fd,ready_ev,OPEN_MAX,timeout);
        int i = 0;
        for(;i < ret;++i){                
            int fd = ready_ev[i].data.fd; 
            int index=(fd==t[1]);
            if(ready_ev[i].events & EPOLLIN){
                int len = Read(t[index],buf,MAXBUF);
                if(len>0 && Write(t[!index],buf,len)>0)
                {
                    fprintf(stdout,"\n[+] data forwarding success\n");fflush(stdout);               
                }else
                {
                    fprintf(stdout,"\n[-] data forwarding Failure\n");fflush(stdout);
                }             
            }   
        }
    }   
    Close(t[1]);
    Close(t[0]);     
    return NULL;
}


int creat_socket()
{
    int sock;
    if((sock=Socket(AF_INET,SOCK_STREAM,0))<0)
        exit(1);
    
    int opt = 1;
    Setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;

    local.sin_family = AF_INET;
    local.sin_port = htons(SERVERPORT);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(sock,(struct sockaddr*)&local,sizeof(local));

    Listen(sock,SOMAXCONN);
    
    fprintf(stdout,"\n[+] listen and bind succeed\n"); fflush(stdout);
    return sock;
}

int set_noblock(int sock)
{
    int fl = fcntl(sock,F_GETFL);
    return fcntl(sock,F_SETFL,fl|O_NONBLOCK);
}

int Acceptfunction(int listen_fd)
{
    while(1){  
        int t[2],len;
        package_t pkg;  
        char buf[MAXBUF+1024];
        struct sockaddr_in remote;
        socklen_t remotelen = sizeof(remote);

        int accept_sock = Accept(listen_fd,(struct sockaddr*)&remote,&remotelen);

        len = Read(accept_sock,buf,sizeof(buf)-1);
        strTopackage(buf,&pkg);
        fprintf(stdout,"\n[+]accept a client..[ip]: %s,[port]: %d [destip]: %s,[destport]: %d\n",inet_ntoa(remote.sin_addr),ntohs(remote.sin_port),pkg.dest_ip,pkg.dest_port); fflush(stdout);
        fprintf(stdout,"\n[+]  Waiting Connect ip:%s Port:%d\n",pkg.dest_ip,pkg.dest_port);fflush(stdout);

        int destfd= socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in dest;
        dest.sin_family = AF_INET;
        dest.sin_port = htons(pkg.dest_port);
        inet_aton(pkg.dest_ip,&dest.sin_addr);
        Connect(destfd,(struct sockaddr*)&dest,sizeof(dest));
        t[0]=accept_sock;
        t[1]=destfd;
        set_noblock(accept_sock);
        in_createthread(in_data_tran,(void *)t);            
    }   
    Close(listen_fd);
}

int main(int argc,char *argv[])
{
    int listen_fd = creat_socket();
    Acceptfunction(listen_fd); 
    return 0;
}

