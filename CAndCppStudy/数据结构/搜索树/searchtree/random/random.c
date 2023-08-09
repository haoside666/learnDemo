#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define MAXSIZE (15+1)
int main(int argc,char *argv)
{
	int fd=open("1.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
	int save_fd;
	if(fd<0)
	{
		perror("open:");
		exit(1);
	}
	int arr[MAXSIZE],brr[MAXSIZE],data;
	arr[0]=MAXSIZE-1;
	memset(brr,0,sizeof(int)*MAXSIZE);
	srand((unsigned)time(NULL));
	for(int i=1;i<MAXSIZE;i++)
	{
		while(1)
		{
			data=rand()%(MAXSIZE-1)+1;
			if(brr[data]==0) break;
		}
		arr[i]=data;
		brr[data]=1;
	}
	save_fd=dup(STDOUT_FILENO);
	dup2(fd,STDOUT_FILENO);
	for(int i=0;i<MAXSIZE-1;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("%d\n",arr[MAXSIZE-1]);
	fflush(stdout);
	dup2(save_fd,STDOUT_FILENO);
	close(fd);
	close(save_fd);
	return 0;
}
