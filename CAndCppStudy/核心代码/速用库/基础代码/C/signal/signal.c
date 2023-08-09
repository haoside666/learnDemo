#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int output(sigset_t set);

int main(int argc,char *argv[])
{
	sigset_t set;
	printf("sizeof(set)=%lu\n",sizeof(set));
	printf("after empty the set:\n");
	sigemptyset(&set);
	output(set);

	printf("after add signo=2:\n");
	sigaddset(&set,2);
	output(set);

	printf("after add signo=10:\n");
	sigaddset(&set,10);
	output(set);

	printf("after fill all:\n");
	sigfillset(&set);
	output(set);
	return 0;
}

int output(sigset_t set)
{
	int i;
	for(i=1;i<32;i++)
	{
		printf("%d ",(sigismember(&set,i)==1)?1:0);
		if((i+1)%8==0)
			printf("\n");
	}

}
