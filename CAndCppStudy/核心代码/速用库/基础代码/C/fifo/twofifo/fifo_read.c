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
	char buffer[1024];
	int ret;
	memset(buffer,0,sizeof(buffer));
	printf("process %d opening FIFO RDONLY!\n",getpid());
	pipe_fd=open(FIFO_NAME,O_RDONLY);
	printf("the pipe_file descriptor is %d!\n",pipe_fd);
	if(pipe_fd!=-1)
	{
		ret=read(pipe_fd,buffer,sizeof(buffer));
		printf("read data:%s,read data_len:%d\n",buffer,ret);
	}else
	{
		printf("pipe_file open fail!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
