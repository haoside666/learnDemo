#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define FIFO_NAME "./TESTFIFO"
int main(int argc,char*argv[])
{
	int pipe_fd;
	char buffer[1024]="helloworld";
	int ret;
	if(access(FIFO_NAME,F_OK)==-1)//
	{
		if(mkfifo(FIFO_NAME,0666)==-1)
		{
			printf("FIFO create fail!\n");			
			exit(EXIT_FAILURE);
		}
	}
	printf("process %d opening FIFO WRONLY!\n",getpid());
	pipe_fd=open(FIFO_NAME,O_WRONLY);
	printf("the pipe_file descriptor is %d!\n",pipe_fd);
	if(pipe_fd!=-1)
	{
		ret=write(pipe_fd,buffer,sizeof(buffer));
		printf("write data:%s,write data_len:%d\n",buffer,ret);
	}else
	{
		printf("pipe_file open fail!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
