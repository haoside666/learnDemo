#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int deamonize()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		perror("fork:");
		exit(1);
	}else if(pid>0)
		exit(0);
	setsid();

	
	if(chdir("/")<0)
	{
		perror("chdir:");
		exit(1);
	}

	umask(0);

	close(0);
	open("/dev/null",O_RDWR);
	dup2(0,1);
	dup2(0,2);
	
}

int main(int argc,char*argv[])
{
	deamonize();
	while(1);
	return 0;
}
