#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h> 
#include <sys/stat.h> 
void handler(int sig)
{
	printf("sig=%d\n",sig);
	exit(EXIT_FAILURE);
}
int main(int argc,char *argv[])
{
	char buffer[50];
	memset(buffer,0,50);
	signal(SIGPIPE,handler);
	/*if((mkfifo("./FIFO",0766))==0)
	{
		printf("pipe FIFO create sucess!\n");
	}else
	{
		printf("error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}*/
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		int fd;
		fd=open("FIFO",O_RDONLY);
		int ret;
		ret=read(fd,buffer,50);
		printf("child ret=%d\nbuffer=%s\n",ret,buffer);
	}else
	{
		int fd;
		fd =open("FIFO",O_WRONLY);
		int ret;
		ret=write(fd,"helloworld",10);
		printf("parent ret=%d\n",ret);
		sleep(1);
	}
	
	return 0;
}
