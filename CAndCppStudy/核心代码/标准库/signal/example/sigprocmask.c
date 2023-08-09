#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void printsigset(sigset_t* set)
{
	for(int i=1;i<32;i++)
	{
		if (sigismember(set, i) == 1)
			putchar('1');
		else
			putchar('0');
		if(i%8==0)
			putchar(10);
	}
	printf("\n");
}
int main()
{
	sigset_t new_set,old_set;
	sigemptyset(&new_set);
	sigaddset(&new_set,SIGINT);
	printsigset(&new_set);
	sigprocmask(SIG_BLOCK, &new_set, NULL);
	while(1)
	{
		printf("*****************\n");
		sleep(1);
	}
	return 0;
}
