#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char *argv[])
{
	int p[2];
	pipe(p);
	int fd=open("123",O_RDWR|O_CREAT|O_TRUNC,0777);
	printf("fd=%d\n",fd);	
	close(fd);
	
	return 0;
}
