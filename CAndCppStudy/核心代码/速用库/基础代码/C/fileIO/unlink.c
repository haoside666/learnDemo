#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc,char* argv[])
{
	int fd=open("123",O_CREAT,0666);
	getchar();
	getchar();
	unlink("123");
	getchar();
	close(fd);
	return 0;	
}
