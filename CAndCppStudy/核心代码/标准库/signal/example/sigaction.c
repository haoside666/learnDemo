#include <unistd.h>
#include <signal.h>
#include <stdio.h>
void sig_alrm(int signo)
{
	/* nothing to do */
}
unsigned int mysleep(unsigned int nsecs)
{
	struct sigaction newact, oldact;
	unsigned int unslept;

	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);//oldact --->The original action of the signal
	alarm(nsecs);
	pause();
	unslept = alarm(0);
	sigaction(SIGALRM, &oldact, NULL);
	return unslept;
}
int main(void)
{
	while(1){
		int ret=mysleep(2);
		printf("Two seconds passed %d\n",ret);
	}
	return 0;
}
