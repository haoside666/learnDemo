#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void printsigset(sigset_t *set)
{
	for(int i=1;i<32;i++)
	{
		if(sigismember(set,i))
		{
			putchar('1');
		}else
		{
			putchar('0');
		}
	}
	putchar(10);

}
int main(int argc,char*argv[])
{
	int i=0;
	sigset_t s,p,old;
	sigemptyset(&s);
	sigaddset(&s,SIGINT);
	sigaddset(&s,SIGQUIT);
	sigaddset(&s,SIGKILL);
	sigprocmask(SIG_BLOCK,&s,NULL);
	sigprocmask(SIG_BLOCK,NULL,&old);
	printf("\n");
	printsigset(&old);	
	printf("\n");
	while(1)
	{	
		sigpending(&p);
		printsigset(&p);
		if(i==10)
		{
			sigdelset(&s,SIGQUIT);
			sigprocmask(SIG_UNBLOCK,&s,NULL);
			sigprocmask(SIG_BLOCK,NULL,&old);
			printf("\n");
			printsigset(&old);	
			printf("\n");
		}
		sleep(1);
		i++;
	}
	return 0;
}
