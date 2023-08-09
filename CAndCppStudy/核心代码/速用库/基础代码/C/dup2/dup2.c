#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
int main(int argc,char*argv[])
{
	char buffer[20];
	int p[2];
	memset(buffer,0,20);
	pipe(p);
	printf("hello");
	dup2(p[1],STDOUT_FILENO);
	printf("world");
	close(p[1]);
	read(p[0],buffer,15);
	int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0300);
	write(fd,buffer,15);
	close(fd);
	return 0;
}
