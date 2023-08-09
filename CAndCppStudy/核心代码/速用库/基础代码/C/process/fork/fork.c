#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0){
		perror("fork:");
		exit(EXIT_FAILURE);
	}else if(pid==0)
	{
		printf("the is child!\n");
	}else
	{
		printf("the is parent!\n");
	}
	return 0;
}
