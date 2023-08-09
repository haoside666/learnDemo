#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void do_sig(int num)
{
	sleep(1);
	static int n=0;
	printf("I am parent %d\n",n);
	n+=2;
}
void do_sig2(int num)
{
	sleep(1);
	static int n=1;
	printf("I am child %d\n",n);
	n+=2;
}
int main(int argc,char *argv[])
{
	//struct sigaction act;
	typedef void (*sighandler_t)(int);
	sighandler_t handler;
	int pid=fork();
	if(pid<0)
	{
		perror("fork:");
		exit(EXIT_FAILURE);	
	}else if(pid==0)
	{
		/*act.sa_handler=do_sig;
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;		
		sigaction(SIGUSR2,&act,NULL);*/
		handler=do_sig;
		signal(SIGUSR2,handler);
		while(1)
		{
			sleep(2);
			kill(getppid(),SIGUSR1);			
		}
	}else
	{
		/*act.sa_handler=do_sig2;
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;
		sigaction(SIGUSR1,&act,NULL);*/
		handler=do_sig2;
		signal(SIGUSR1,handler);
		while(1)
		{
			sleep(2);
			kill(pid,SIGUSR2);		
		}
	}
	return 0;
}
