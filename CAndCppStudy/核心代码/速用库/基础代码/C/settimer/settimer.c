#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
void PrintMsg(int Num)
{
    printf("Hello World!\n");
    return;
}
int main(int argc,char *argv[])
{
	signal(SIGALRM, PrintMsg);

	struct itimerval setvalue;
	setvalue.it_interval.tv_sec=3;
	setvalue.it_interval.tv_usec=0;
	setvalue.it_value.tv_sec=10;
	setvalue.it_value.tv_usec=0;
	setitimer(ITIMER_REAL,&setvalue,NULL);
	while(1)
	{
		getitimer(ITIMER_REAL,&setvalue);
		printf("ITIMER_REAL:interval:%lds %ldms,value:%lds %ld ms\n",setvalue.it_interval.tv_sec,setvalue.it_interval.tv_usec,setvalue.it_value.tv_sec,setvalue.it_value.tv_usec);
		sleep(1);
	}
	while(1);
	return 0;
}
