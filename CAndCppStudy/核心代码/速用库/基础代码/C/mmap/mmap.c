#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define LEN 5
int main(int argc,char *argv[])
{
	int fd;
	if(access("1.txt",F_OK)==-1)
	{
		fd=open("1.txt",O_CREAT|O_WRONLY|O_TRUNC,0664);
	}else
	{
		fd=open("1.txt",O_RDWR);
	}
	lseek(fd,LEN-1,SEEK_SET);
	write(fd,"a",1);
	char *p;
	p=(char *)mmap(NULL,LEN,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	close(fd);
	if(p==MAP_FAILED)
	{
		perror("mmap:");
		exit(1);
	}
	for(int i=0;i<LEN;i++)
	{
		*p=(i%10)+48;
		p++;
	}
	return 0;
}
