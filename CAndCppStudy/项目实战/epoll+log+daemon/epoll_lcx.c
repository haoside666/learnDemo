#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <fcntl.h>

#include "./printlog.h"
#define BUF_LEN 8192
#define OPEN_MAX 1024

#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include<sys/epoll.h>


typedef int SOCKET;
#define ThreadReturn void*

#define delay(x) usleep(x*1000)
#define closesocket(x) close(x)

typedef ThreadReturn (*Func)(void*);

int total_connect = 0;

int main_func(int argc,char**argv);

void ctrl_c(int32_t i)
{
  DBG_FPRINT2("[+] Receive: Ctrl+C..I'll quit..");
  DBG_FPRINT2("[+] Let me exit....");
  DBG_FPRINT2("[+] All Right!\n");
  exit(0);
}

int in_createthread(Func run,void* data)
{
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
  pthread_t tt;
  pthread_create(&tt,&attr,run,data);
  delay(5);
  return 0;
}

ThreadReturn  in_data_tran(void* p)
{
  SOCKET t[2];
  t[0]=((int*)p)[0];
  t[1]=((int*)p)[1];

  struct sockaddr_in sa[2];
  const unsigned char* ip[2];
  unsigned short port[2];

  socklen_t len = sizeof(struct sockaddr_in);
  if(getpeername(t[0],(struct sockaddr*)sa,&len)==-1 || getpeername(t[1],(struct sockaddr*)(sa+1),&len)==-1)
  {
    DBG_FPRINT("[-] Get Remote Host Failed");
    closesocket(t[0]);
    closesocket(t[1]);
    return 0;
  }

  ip[0] = (unsigned char*)&sa[0].sin_addr.s_addr;
  ip[1] = (unsigned char*)&sa[1].sin_addr.s_addr;
  port[0] = htons(sa[0].sin_port);
  port[1] = htons(sa[1].sin_port);

  int epoll_fd = epoll_create(OPEN_MAX);
  if(epoll_fd < 0){
    DBG_FPRINT("[-] epoll_create Fail");
    closesocket(t[0]);
    closesocket(t[1]);
    exit(EXIT_FAILURE);
  }
  
  struct epoll_event ep_ev;
  ep_ev.events = EPOLLIN;
  ep_ev.data.fd = t[0];
  if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,t[0],&ep_ev) < 0){
    DBG_FPRINT("[-] file %d epoll_ctl Fail",t[0]);
    closesocket(t[0]);
    exit(EXIT_FAILURE);
  }
  ep_ev.events = EPOLLIN;
  ep_ev.data.fd = t[1];
  if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,t[1],&ep_ev) < 0){
    DBG_FPRINT("[-] file %d epoll_ctl Fail",t[1]);
    closesocket(t[1]);
    exit(EXIT_FAILURE);
  }

  struct epoll_event ready_ev[OPEN_MAX];
  int timeout = -1;
  
  unsigned char buf[BUF_LEN];
  int total_byte = 0,ret;
  ++total_connect;
  int flags=1;
  while(flags)
  {
    switch(ret = epoll_wait(epoll_fd,ready_ev,OPEN_MAX,timeout)){
      case -1:
        DBG_FPRINT("[-]epoll_wait");
        break;
      case 0:
        DBG_FPRINT("[-] time out...");
        break;
      default: 
      {
        int i;
        for(i=0;i < ret;++i){
          if(ready_ev[i].events & EPOLLIN)
          {
            int fd = ready_ev[i].data.fd; 
            int index=(fd==t[1]);
            int len = recv(t[index],buf,BUF_LEN,0);
            if(len>0 && send(t[!index],buf,len,0)>0 )
            {
              total_byte += len;
              char out[100];
              sprintf(out,"[+]  Send <Total %d>: %d.%d.%d.%d:%d -> %d.%d.%d.%d:%d,  %d Bytes",
                  total_connect,ip[index][0],ip[index][1],ip[index][2],ip[index][3],port[index],ip[!index][0],ip[!index][1],ip[!index][2],ip[!index][3],port[!index],len);
              DBG_FPRINT2("%s",out);
            }
            else
            {
              flags=0;
              DBG_FPRINT2("[+]  Connection <Total %d> Cutdown, Total : %d Bytes",total_connect,total_byte);            
              break;
            }
          }   
        }
        break;
      }
    }
  }
  --total_connect;
  closesocket(t[0]);
  closesocket(t[1]);
  return NULL;
}

long gethost(const char* name)
{
  if(name)
  {
    struct hostent *host = gethostbyname(name);
    long i;
    if(host&&host->h_addr)
    {
      i = *(long *)(host->h_addr);
      return i;
    }
  }
  DBG_FPRINT("[-] %s: Wrong host address",name);
  return -1;
}

int lcx_slave(const char* ip1_str,unsigned short port1,const char* ip2_str,unsigned short port2)
{
  char out1[100],out2[100];
  while(1)
  {
    unsigned long ip1 = gethost(ip1_str);
    if(-1 == ip1)
    {
      DBG_FPRINT("[-]  Reslove Host %s Failed...",ip1_str);
      break;
    }
    unsigned long ip2 = gethost(ip2_str);
    if(-1 == ip2)
    {
      DBG_FPRINT("[-]  Reslove Host %s Failed...",ip2_str);
      break;
    }
    SOCKET s[2];
    s[0] = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    s[1] = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in sa[2];
    sa[0].sin_family = AF_INET;
    sa[0].sin_port = htons(port1);
    sa[0].sin_addr.s_addr = (ip1);
    sa[1].sin_family = AF_INET;
    sa[1].sin_port = htons(port2);
    sa[1].sin_addr.s_addr = (ip2);
    unsigned char*ip[2];
    ip[0] = (unsigned char*)&ip1;
    ip[1] = (unsigned char*)&ip2;
    sprintf(out1,"%d.%d.%d.%d:%d",ip[0][0],ip[0][1],ip[0][2],ip[0][3],port1);
    sprintf(out2,"%d.%d.%d.%d:%d",ip[1][0],ip[1][1],ip[1][2],ip[1][3],port2);

    if(s[0]!=-1 && s[1]!=-1)
    {
      DBG_FPRINT2("[+]  Connect %s, Please Wait\n",out1);
      if(connect(s[0],(struct sockaddr*)&sa[0],sizeof(struct sockaddr))!=0)
      {
        DBG_FPRINT("[-]  Connect %s Failed,CutDown...",out2);
        closesocket(s[0]);
        closesocket(s[1]);
      }
      else
      {
        DBG_FPRINT2("[+]  Connect %s Successed,Now Connect %s\n",out1,out2);
        if(connect(s[1],(struct sockaddr*)&sa[1],sizeof(struct sockaddr))==0)
        {
          DBG_FPRINT2("[+]  Connect %s Successed,Transfering...\n",out2);
          in_createthread(in_data_tran,s);
        }
        else
        {
          DBG_FPRINT("[-]  Connect %s Failed,CutDown...",out2);
          closesocket(s[0]);
          closesocket(s[1]);
        }
      }
    }
    else
    {
      DBG_FPRINT("[-]  Create Socket Failed");
      return -1;
    }
    delay(1000);
  }
  return 0;
}

int lcx_listen(unsigned short port1,unsigned short port2)
{
  SOCKET s[2]={-1,-1};
  unsigned short p[2];
  p[0]=port1;
  p[1]=port2;

  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;
  int i;
  int flags = 0;
  for(i=0; i<2; ++i)
  {
    s[i] = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(s[i]!=-1)
    {
      DBG_FPRINT2("[+]  Create Socket %d Successed\n",i+1);
      sa.sin_port = htons(p[i]);

      int flag = 1;
      setsockopt(s[i], SOL_SOCKET, SO_REUSEADDR, (const void*)&flag, sizeof(flag));
      if(bind(s[i],(struct sockaddr*)&sa,sizeof(sa))==0)
      {
        DBG_FPRINT2("[+]  Bind On Port %u Success\n",p[i]);
        if(listen(s[i],SOMAXCONN)==0)
        {
          DBG_FPRINT2("[+]  Listen On Port %u Successed\n",p[i]);
          flags =  1;
        }
        else
        {
          DBG_FPRINT("[-]  Listen On Port %u Failed",p[i]);
          break;
        }
      }
      else
      {
        DBG_FPRINT("[-]  Bind On Port %u Failed",p[i]);
        break;
      }
    }
    else
    {
      DBG_FPRINT("[-]  Create Socket %d Failed",i+1);
      break;
    }
  }
  if(!flags)
  {
    closesocket(s[0]);
    closesocket(s[1]);
    return -1;
  }

  i = 0;
  SOCKET t[2];
  socklen_t sz = sizeof(sa);
  while(1)
  {
    DBG_FPRINT2("[+]  Waiting Connect On Port %u\n",p[i]);
    t[i] = accept(s[i],(struct sockaddr*)&sa,&sz);
    const unsigned char *ip = (unsigned char*)&sa.sin_addr.s_addr;
    if(t[i]!=-1)
    {
      DBG_FPRINT2("[+]  Connect From %d.%d.%d.%d:%d On Port %d\n",ip[0],ip[1],ip[2],ip[3],htons(sa.sin_port),p[i]);     
      if(i==1)
      {
        in_createthread(in_data_tran,t);
      }
      i = (i==0);
    }
    else
    {
      DBG_FPRINT("[-]  Accept Failed On Port %d",p[i]);
      i=0;
    }
  }
  return 0;
}

int lcx_tran(unsigned short port1,const char* ip2_str,unsigned short port2)
{
  SOCKET s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port1);
  sa.sin_addr.s_addr = INADDR_ANY;
  socklen_t flags =0;
  if(s!=-1)
  {
    int flag = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const void*)&flag, sizeof(flag));
    if(bind(s,(struct sockaddr*)&sa,sizeof(sa))==0)
    {
      if(listen(s,SOMAXCONN)==0)
      {
        flags = 1;
        DBG_FPRINT2("[+]  Listening On Port %d...\n",port1);
      }
      else
      {
        DBG_FPRINT("[-]  Listen Failed");
      }
    }
    else
    {
      DBG_FPRINT("[-]  Bind On Port %d Failed",port1);
    }
  }
  else
  {
    DBG_FPRINT("[-]  Create Socket Failed\n");
  }
  if(!flags)
  {
    closesocket(s);
    return -1;
  }
  SOCKET tt[2];
  SOCKET ac=-1;
  socklen_t sa_len = sizeof(sa);
  char out1[100],out2[100];
  while(1)
  {
    unsigned long ip2 = gethost(ip2_str);
    if(-1 == ip2)
    {
      DBG_FPRINT("[-]  Reslove Host %s Failed...",ip2_str);
      break;
    }
    DBG_FPRINT2("[+]  Waiting Connect On Port %d...\n",port1);
    if(ac=accept(s,(struct sockaddr*)&sa,&sa_len),ac==-1)
    {
      break;
    }
    unsigned char* ip =(unsigned char*)&sa.sin_addr.s_addr;
    sprintf(out1,"%d.%d.%d.%d:%d",ip[0],ip[1],ip[2],ip[3],htons(sa.sin_port));
    ip = (unsigned char*)&ip2;
    sprintf(out2,"%d.%d.%d.%d:%d",ip[0],ip[1],ip[2],ip[3],(port2));
    DBG_FPRINT2("[+]  Connect From %s, Now Connect to %s",out1,out2);
    sa.sin_port = htons(port2);
    sa.sin_addr.s_addr = ip2;
    SOCKET s2 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(connect(s2,(struct sockaddr*)&sa,sizeof(sa))==0)
    {
      tt[0]=ac;
      tt[1]=s2;
      DBG_FPRINT2("[+]  Connect %s Successed,Start Transfer...",out2);
      in_createthread(in_data_tran,tt);
    }
    else
    {
      DBG_FPRINT("[-]  Connect %s Failed...",out2);
      closesocket(s2);
      closesocket(ac);
    }
  }
  closesocket(s);
  closesocket(ac);
  return 0;
}

void help(const char* name)
{
  DBG_FPRINT2("Usage of Packet Transmit:");
  DBG_FPRINT2("  %s -<listen|tran|slave> <option>",name);
  DBG_FPRINT2("  %s -about",name);
  DBG_FPRINT2("[options:]");
  DBG_FPRINT2("  -listen <local port1>  <local port2>");
  DBG_FPRINT2("  -tran   <local port>   <remote host>  <remote port>");
  DBG_FPRINT2("  -slave  <remote host1> <remote port1> <remote host2> <remote port2>");
}

void about()
{
  DBG_FPRINT2("By:     Anonymous");
  DBG_FPRINT2("Email:  windworst@gmail.com\n");
}

long getport(const char *str)
{
  long port = EOF;
  port = atoi(str);
  if (port<=0||port>65535)
  {
    DBG_FPRINT("[-] %s: Wrong port number",str);
  }
  return port;
}

int main_func(int argc,char**argv)
{
  if (argc<2)
  {
    help(argv[0]);
    return 0;
  }
  const char* command[] = {"-about","-listen","-slave","-tran"};
  int32_t i,s = sizeof(command)/sizeof(*command);
  for (i=0; i<s; i++)
  {
    if (strcmp(command[i],argv[1])==0)
      break;
  }
  int32_t n = 2;
  const char * addr1=NULL, *addr2=NULL;
  int32_t port1=0,port2=0;
  switch (i)
  {
    case 0:
      about();
      break;
    case 1:
      if (argc<4)
      {
        help(argv[0]);
        return 0;
      }
      else
      {
        port1 = getport(argv[n]);
        port2 = getport(argv[++n]);
      }
      break;
    case 2:
      if (argc<6)
      {
        help(argv[0]);
        return 0;
      }
      else
      {
        addr1 = argv[n];
        port1 = getport(argv[++n]);
        addr2 = argv[++n];
        port2 = getport(argv[++n]);
      }
      break;
    case 3:
      if (argc<5)
      {
        help(argv[0]);
        return 0;
      }
      else
      {
        port1 = getport(argv[n]);
        addr2 = argv[++n];
        port2 = getport(argv[++n]);
      }
      break;
    default:
      {
        help(argv[0]);
        return 0;
      }
      break;
  }
  if(port1==-1 || port2==-1 )return 0;

  switch(i)
  {
    case 1:lcx_listen(port1,port2);break;
    case 2:lcx_slave(addr1,port1,addr2,port2);break;
    case 3:lcx_tran(port1,addr2,(uint16_t)port2);break;
    default:break;
  }
  return 0;
}

void creat_daemon()
{
    int i,fd;
    pid_t id;
    struct sigaction sa;
    umask(0);//第一步：调用umask将文件模式创建屏蔽字设置为0.
    if((id = fork()) < 0){
        DBG_FPRINT("[-] fork error!");
        return;
    }else if(id != 0){
        exit(0);//第二步：调用fork，父进程退出。保证子进程不是话首进程，从而保证后续不和其他终端关联。
    }

    setsid();//第三步：设置新会话。 

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGCHLD,&sa,NULL) < 0){
        //注册子进程退出忽略信号
        return;
    }

    if((id = fork()) < 0){
        DBG_FPRINT("[-] fork 2 error!");
        return;
    }else if(id != 0){
         exit(0);
    }
	
	//	守护进程空间
    if(chdir("/") < 0){
        //第四步：更改工作目录到根目录 
        DBG_FPRINT("[-] child dir error");
        return;
    }
    close(0);
    fd = open("/dev/null",O_RDWR);//关闭标准输入，重定向所有标准（输入输出错误）到/dev/NULL
    dup2(fd,1);
    dup2(fd,2);
}


int main(int argc,char** argv)
{
  DBG_FPRINT2("-----------------------------------------------------------------------\n");
  DBG_FPRINT2("Server up and running\n");
  creat_daemon();
  signal(SIGINT,ctrl_c);
  int ret = main_func(argc,argv);
  DBG_FPRINT2("!!!The process has been shut down\n");
  return ret;
}
