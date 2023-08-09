#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int fd[2]={0,0};
	int ret=socketpair(AF_UNIX,SOCK_STREAM,0,fd);
	if(ret<0){
		perror("socketpair");
		return 1;
	}
	
	pid_t id =fork();
	if(id<0){
		perror("fork");
		return 2;
	}else if(id==0)
	{
		close(fd[1]);

		char *msg_c="i know";
		char buf[256];
		while(1)
		{
			//write
			write(fd[0],msg_c,strlen(msg_c));
			//read
			ssize_t sz=read(fd[0],buf,sizeof(buf)-1);
			buf[sz]='\0';

			//printf
			printf("child recv:%d,%s\n",getpid(),buf);
			sleep(1);
		}
	}else
	{
		close(fd[0]);

		char *msg_f="i am your father";
		char buf[256];
		while(1)
		{
			//read
			read(fd[1],buf,sizeof(buf)-1);
			//write
			write(fd[1],msg_f,strlen(msg_f));
			//printf
			printf("parent recv:%d,%s\n",getpid(),buf);
			sleep(1);
		}
	}
	
}
