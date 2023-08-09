#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void do_sig(int num)
{
	printf("I am do_sig\n");
	printf("num=%d\n",num);
}


int main(int argc,char *argv[])
{
	struct sigaction act;
	act.sa_handler=do_sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGINT,&act,NULL);
	
	while(1)
	{
		printf("*****************\n");
		sleep(1);
	}
	
	return 0;	
}
