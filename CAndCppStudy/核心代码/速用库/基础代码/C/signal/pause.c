#include <unistd.h>
#include <signal.h>
#include <stdio.h>
void sig_alrm(int signo)
{
/* nothing to do */
}
/*
unsigned int mysleep(unsigned int nsecs)
{
	struct sigaction newact, oldact;
	unsigned int unslept;
	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);
	alarm(nsecs);
	pause();
	unslept = alarm(0);
	sigaction(SIGALRM, &oldact, NULL);
	return unslept;
}
*/
unsigned int mysleep(unsigned int nsecs)
{
	struct sigaction newact,oldact;
	sigset_t newmask,oldmask,suspmask;
	unsigned int unslept;
	/* set our handler, save previous information */
	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);
	/* block SIGALRM and save current signal mask */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	alarm(nsecs);
	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);/* make sure SIGALRM isn't blocked */
	sigsuspend(&suspmask);/* wait for any signal to be caught */
	/* some signal has been caught,SIGALRM is now blocked */
	unslept = alarm(0);
	sigaction(SIGALRM, &oldact, NULL);/* reset previous action */
	/* reset signal mask, which unblocks SIGALRM */
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return(unslept);
}
int main(void)
{
	while(1){
		mysleep(2);
		printf("Two seconds passed\n");
	}
	return 0;
}
