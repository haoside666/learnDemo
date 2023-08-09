#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>

#define BUF_LEN 8192
#define OPEN_MAX 1024

#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include<sys/epoll.h>


typedef int SOCKET;
#define ThreadReturn void*

#define delay(x) usleep(x*1000)
#define closesocket(x) close(x)

typedef ThreadReturn (*Func)(void*);

FILE* lcx_log = NULL;
FILE* lcx_hex = NULL;
FILE* lcx_text = NULL;
int total_connect = 0;

int main_func(int argc,char**argv);

void ctrl_c(int32_t i)
{
  fprintf(stdout,"\n[-] Receive: Ctrl+C..I'll quit..\n");
  fprintf(stdout,"\n[+] Let me exit....\n");
  fprintf(stdout,"[+] All Right!\n\n");
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
    fprintf(stdout,"\n[-] Get Remote Host Failed\n");
    if(lcx_log)fprintf(lcx_log,"\n[-] Get Remote Host Failed\n"),fflush(lcx_log);
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
    fprintf(stdout,"\n[+]epoll_create Fail\n\n");fflush(stdout);
    closesocket(t[0]);
    closesocket(t[1]);
    exit(EXIT_FAILURE);
  }
  
  struct epoll_event ep_ev;
  ep_ev.events = EPOLLIN;//数据的读取
  ep_ev.data.fd = t[0];
  //添加关心的事件
  if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,t[0],&ep_ev) < 0){
    fprintf(stdout,"\n[+]file %d epoll_ctl Fail\n\n",t[0]);fflush(stdout);
    closesocket(t[0]);
    exit(EXIT_FAILURE);
  }
  ep_ev.events = EPOLLIN;//数据的读取
  ep_ev.data.fd = t[1];
  //添加关心的事件
  if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,t[1],&ep_ev) < 0){
    fprintf(stdout,"\n[+]file %d epoll_ctl Fail\n\n",t[1]);fflush(stdout);
    closesocket(t[1]);
    exit(EXIT_FAILURE);
  }

  struct epoll_event ready_ev[OPEN_MAX];//申请空间来放就绪的事件。
  int timeout = -1;//设置超时时间，若为-1，则永久阻塞等待。
  
  unsigned char buf[BUF_LEN];
  int total_byte = 0,ret;
  ++total_connect;
  int OK=1;
  while(OK)
  {
    switch(ret = epoll_wait(epoll_fd,ready_ev,OPEN_MAX,timeout)){
      case -1:
        perror("epoll_wait");
        break;
      case 0:
        printf("\n[+] time out...\n");
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
              sprintf(out,"\n[+]  Send <Total %d>: %d.%d.%d.%d:%d -> %d.%d.%d.%d:%d,  %d Bytes\n",
                  total_connect,ip[index][0],ip[index][1],ip[index][2],ip[index][3],port[index],ip[!index][0],ip[!index][1],ip[!index][2],ip[!index][3],port[!index],len);
              fprintf(stdout,"%s",out);fflush(stdout);
              if(lcx_log)fprintf(lcx_log,"%s",out),fflush(lcx_log);
              if(lcx_text)
              {
                fprintf(lcx_text,"\n%s\n",out);
                fwrite(buf,1,len,lcx_text);
                fflush(lcx_text);
              }
              if(lcx_hex)
              {
                fprintf(lcx_hex,"\n%s",out);
                int i;
                for(i=0;i<len;++i)
                {
                  if(i%16==0)fprintf(lcx_hex,"\n");
                  fprintf(lcx_hex,"%02X ",buf[i]);
                }
                fflush(lcx_hex);
              }
            }
            else
            {
              OK=0;
              fprintf(stdout,"\n[+]  Connection <Total %d> Cutdown, Total : %d Bytes\n\n",total_connect,total_byte);fflush(stdout);
              if(lcx_log)fprintf(lcx_log,"\n[+]  Connection <Total %d> Cutdown, Total : %d Bytes\n\n",total_connect,total_byte),fflush(lcx_log);
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
  fprintf(stdout,"\nERROR: %s: Wrong host address\n\n",name);
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
      fprintf(stdout,"\n[-]  Reslove Host %s Failed...\n",ip1_str),fflush(stdout);
      break;
    }
    unsigned long ip2 = gethost(ip2_str);
    if(-1 == ip2)
    {
      fprintf(stdout,"\n[-]  Reslove Host %s Failed...\n",ip2_str),fflush(stdout);
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
      fprintf(stdout,"\n[+]  Connect %s, Please Wait\n",out1);fflush(stdout);
      if(lcx_log)fprintf(lcx_log,"\n[+]  Connect %s, Please Wait\n",out1),fflush(lcx_log);
      if(connect(s[0],(struct sockaddr*)&sa[0],sizeof(struct sockaddr))!=0)
      {
        fprintf(stdout,"\n[-]  Connect %s Failed,CutDown...\n",out2);
        if(lcx_log)fprintf(lcx_log,"\n[-]  Connect %s Failed,CutDown...\n",out2),fflush(lcx_log);
        closesocket(s[0]);
        closesocket(s[1]);
      }
      else
      {
        fprintf(stdout,"\n[+]  Connect %s Successed,Now Connect %s\n",out1,out2);fflush(stdout);
        if(lcx_log)fprintf(lcx_log,"\n[+]  Connect %s Successed,Now Connect %s\n",out1,out2),fflush(lcx_log);
        if(connect(s[1],(struct sockaddr*)&sa[1],sizeof(struct sockaddr))==0)
        {
          fprintf(stdout,"\n[+]  Connect %s Successed,Transfering...\n",out2);fflush(stdout);
          if(lcx_log)fprintf(lcx_log,"\n[+]  Connect %s Successed,Transfering...\n",out2),fflush(lcx_log);
          in_createthread(in_data_tran,s);
        }
        else
        {
          fprintf(stdout,"\n[-]  Connect %s Failed,CutDown...\n",out2);
          if(lcx_log)fprintf(lcx_log,"\n[-]  Connect %s Failed,CutDown...\n",out2),fflush(lcx_log);
          closesocket(s[0]);
          closesocket(s[1]);
        }
      }
    }
    else
    {
      fprintf(stdout,"\n[-]  Create Socket Failed\n");
      if(lcx_log)fprintf(lcx_log,"\n[-]  Create Socket Failed\n"),fflush(lcx_log);
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
  int OK = 0;
  for(i=0; i<2; ++i)
  {
    s[i] = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(s[i]!=-1)
    {
      fprintf(stdout,"\n[+]  Create Socket %d Successed\n",i+1);fflush(stdout);
      if(lcx_log)fprintf(lcx_log,"\n[+]  Create Socket %d Successed\n",i+1),fflush(lcx_log);
      sa.sin_port = htons(p[i]);

      int flag = 1;
      setsockopt(s[i], SOL_SOCKET, SO_REUSEADDR, (const void*)&flag, sizeof(flag));
      if(bind(s[i],(struct sockaddr*)&sa,sizeof(sa))==0)
      {
        fprintf(stdout,"\n[+]  Bind On Port %u Success\n",p[i]);fflush(stdout);
        if(lcx_log)fprintf(lcx_log,"\n[+]  Bind On Port %u Success\n",p[i]),fflush(lcx_log);
        if(listen(s[i],SOMAXCONN)==0)
        {
          fprintf(stdout,"\n[+]  Listen On Port %u Successed\n",p[i]);fflush(stdout);
          if(lcx_log)fprintf(lcx_log,"\n[+]  Listen On Port %u Successed\n",p[i]),fflush(lcx_log);
          OK =  1;
        }
        else
        {
          fprintf(stdout,"\n[-]  Listen On Port %u Failed\n",p[i]);
          if(lcx_log)fprintf(lcx_log,"\n[-]  Listen On Port %u Failed\n",p[i]),fflush(lcx_log);
          break;
        }
      }
      else
      {
        fprintf(stdout,"\n[-]  Bind On Port %u Failed\n",p[i]);
        if(lcx_log)fprintf(lcx_log,"\n[-]  Bind On Port %u Failed\n",p[i]),fflush(lcx_log);
        break;
      }
    }
    else
    {
      fprintf(stdout,"\n[-]  Create Socket %d Failed\n",i+1);
      if(lcx_log)fprintf(lcx_log,"\n[-]  Create Socket %d Failed\n",i+1),fflush(lcx_log);
      break;
    }
  }
  if(!OK)
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
    fprintf(stdout,"\n[+]  Waiting Connect On Port %u\n",p[i]);fflush(stdout);
    if(lcx_log)fprintf(lcx_log,"\n[+]  Waiting Connect On Port %u\n",p[i]),fflush(lcx_log);
    t[i] = accept(s[i],(struct sockaddr*)&sa,&sz);
    const unsigned char *ip = (unsigned char*)&sa.sin_addr.s_addr;
    if(t[i]!=-1)
    {
      fprintf(stdout,"\n[+]  Connect From %d.%d.%d.%d:%d On Port %d\n",ip[0],ip[1],ip[2],ip[3],htons(sa.sin_port),p[i]);fflush(stdout);
      if(lcx_log)fprintf(lcx_log,"\n[+]  Connect From %d.%d.%d.%d:%d On Port %d\n",ip[0],ip[1],ip[2],ip[3],htons(sa.sin_port),p[i]),fflush(lcx_log);
      if(i==1)
      {
        in_createthread(in_data_tran,t);
      }
      i = (i==0);
    }
    else
    {
      fprintf(stdout,"\n[-]  Accept Failed On Port %d\n",p[i]);
      if(lcx_log)fprintf(lcx_log,"\n[-]  Accept Failed On Port %d\n",p[i]),fflush(lcx_log);
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
  socklen_t ok =0;
  if(s!=-1)
  {
    int flag = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const void*)&flag, sizeof(flag));
    if(bind(s,(struct sockaddr*)&sa,sizeof(sa))==0)
    {
      if(listen(s,SOMAXCONN)==0)
      {
        ok = 1;
        fprintf(stdout,"\n[+]  Listening On Port %d...\n",port1);fflush(stdout);
        if(lcx_log)fprintf(lcx_log,"\n[+]  Listening On Port %d...\n",port1),fflush(lcx_log);
      }
      else
      {
        fprintf(stdout,"\n[-]  Listen Failed\n");
        if(lcx_log)fprintf(lcx_log,"\n[-]  Listen Failed\n"),fflush(lcx_log);
      }
    }
    else
    {
      fprintf(stdout,"\n[-]  Bind On Port %d Failed\n",port1);
      if(lcx_log)fprintf(lcx_log,"\n[-]  Bind On Port %d Failed\n",port1),fflush(lcx_log);
    }
  }
  else
  {
    fprintf(stdout,"\n[-]  Create Socket Failed\n");
    if(lcx_log)fprintf(lcx_log,"\n[-]  Create Socket Failed\n"),fflush(lcx_log);
  }
  if(!ok)
  {
    closesocket(s);
    return -1;
  }
  SOCKET tt[2];
  SOCKET ac=-1;
  ok = sizeof(sa);
  char out1[100],out2[100];
  while(1)
  {
    unsigned long ip2 = gethost(ip2_str);
    if(-1 == ip2)
    {
      fprintf(stdout,"\n[-]  Reslove Host %s Failed...\n",ip2_str),fflush(stdout);
      break;
    }
    fprintf(stdout,"\n[+]  Waiting Connect On Port %d...\n",port1);fflush(stdout);
    if(lcx_log)fprintf(lcx_log,"\n[+]  Waiting Connect On Port %d...\n",port1),fflush(lcx_log);
    if(ac=accept(s,(struct sockaddr*)&sa,&ok),ac==-1)
    {
      break;
    }
    unsigned char* ip =(unsigned char*)&sa.sin_addr.s_addr;
    sprintf(out1,"%d.%d.%d.%d:%d",ip[0],ip[1],ip[2],ip[3],htons(sa.sin_port));
    ip = (unsigned char*)&ip2;
    sprintf(out2,"%d.%d.%d.%d:%d",ip[0],ip[1],ip[2],ip[3],(port2));
    fprintf(stdout,"\n[+]  Connect From %s, Now Connect to %s\n",out1,out2);fflush(stdout);
    if(lcx_log)fprintf(lcx_log,"\n[+]  Connect From %s, Now Connect to %s\n",out1,out2),fflush(lcx_log);
    sa.sin_port = htons(port2);
    sa.sin_addr.s_addr = ip2;
    SOCKET s2 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(connect(s2,(struct sockaddr*)&sa,sizeof(sa))==0)
    {
      tt[0]=ac;
      tt[1]=s2;
      fprintf(stdout,"\n[+]  Connect %s Successed,Start Transfer...\n",out2);fflush(stdout);
      if(lcx_log)fprintf(lcx_log,"\n[+]  Connect %s Successed,Start Transfer...\n",out2),fflush(lcx_log);
      in_createthread(in_data_tran,tt);
    }
    else
    {
      fprintf(stdout,"\n[-]  Connect %s Failed...\n",out2),fflush(stdout);
      if(lcx_log)fprintf(lcx_log,"\n[-]  Connect %s Failed...\n",out2),fflush(lcx_log);
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
  fprintf(stdout,"\nUsage of Packet Transmit:\n");
  fprintf(stdout,"  %s -<listen|tran|slave> <option> [<-log|-hex|-text> file] \n",name);
  fprintf(stdout,"  %s -about\n\n",name);
  fprintf(stdout,"[options:]\n");
  fprintf(stdout,"  -listen <local port1>  <local port2>\n");
  fprintf(stdout,"  -tran   <local port>   <remote host>  <remote port>\n");
  fprintf(stdout,"  -slave  <remote host1> <remote port1> <remote host2> <remote port2>\n\n");
  fprintf(stdout,"  -hex   : hex mode data dump\n");
  fprintf(stdout,"  -text  : text mode data dump\n");
  fprintf(stdout,"  -log   : save transfer log\n\n");
}

void about()
{
  fprintf(stdout,"\nBy:     Anonymous\n");
  fprintf(stdout,"Email:  windworst@gmail.com\n\n");
}

long getport(const char *str)
{
  long port = EOF;
  port = atoi(str);
  if (port<=0||port>65535)
  {
    fprintf(stdout,"\nERROR: %s: Wrong port number\n\n",str);
  }
  return port;
}

void setfile(FILE** fp,const char*file)
{
  *fp = fopen(file,"w");
  if (*fp==NULL)
  {
    fprintf(stdout,"\nERROR: Can not Write to File: %s\n\n",file);
  }
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
  const char* logpath=NULL,*hexpath=NULL,*textpath=NULL;
  while (++n<argc)
  {
    if (strcmp(argv[n],"-hex")==0)
    {
      if (argc-1<++n)
      {
        fprintf(stdout,"\n[-] ERROR: -hex Must supply file name.\n\n");
        return 0;
      }
      hexpath = argv[n];
    }
    else if (strcmp(argv[n],"-text")==0)
    {
      if (argc-1<++n)
      {
        fprintf(stdout,"\n[-] ERROR: -text Must supply file name.\n\n");
        return 0;
      }
      textpath = argv[n];
    }
    else if (strcmp(argv[n],"-log")==0)
    {
      if (argc-1<++n)
      {
        fprintf(stdout,"\n[-] ERROR: -log Must supply file name.\n\n");
        return 0;
      }
      logpath = argv[n];
    }
    else
    {
      fprintf(stdout,"\n[-] ERROR:  %s  Undefined.\n\n",argv[n]);
      return 0;
    }
  }

  if (logpath)
  {
    setfile(&lcx_log,logpath);
    if(lcx_log==NULL)return 0;
  }
  if (hexpath)
  {
    setfile(&lcx_hex,hexpath);
    if(lcx_hex==NULL)return 0;
  }
  if (textpath)
  {
    setfile(&lcx_text,textpath);
    if(lcx_text==NULL)return 0;
  }

  switch(i)
  {
    case 1:lcx_listen(port1,port2);break;
    case 2:lcx_slave(addr1,port1,addr2,port2);break;
    case 3:lcx_tran(port1,addr2,(uint16_t)port2);break;
    default:break;
  }
  return 0;
}

int main(int argc,char** argv)
{
  signal(SIGINT,ctrl_c);
  int ret = main_func(argc,argv);
  return ret;
}
