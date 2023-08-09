#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
void do_sig_child(int n)
{
	waitpid(0,NULL,WNOHANG);
}
int main(int argc,char *argv[])
{
	pid_t pid;
	int i;
	for(i=0;i<3;i++)
	{
		pid=fork();
		if(pid<0)
		{
			perror("fork");
			exit(1);
		}else if(pid==0)
			break;		
	}
	if(pid==0)
	{
		int n=8;
		while(n--)
		{
			printf("I am child %d--%d\n",getpid(),i);
			sleep(1);
		}
	}
	if(pid>0)
	{
		typedef void (*sighandler_t)(int);
		sighandler_t handler;
		handler=do_sig_child;
		signal(SIGCHLD,handler);
		while(1)
		{
			printf("I am parent\n");
			sleep(1);
		}
		
	}
	return 0;
}
