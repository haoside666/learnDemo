#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>


int main(int argc,char *argv[])
{
	int fd=open("abc",O_WRONLY);
	if(fd<0)
	{
		printf("%s\n",strerror(errno));
		perror("zhangyide");
	}
	printf("fd=%d\n",fd);
	return 0;
}


