#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int fd;
	if(argc<2)
	{
		printf("./app filename\n");
		exit(EXIT_FAILURE);
	}
	fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
	lseek(fd,0x100000-1,SEEK_SET);
	write(fd,"",1);
	close(fd);
	return 0;
}
