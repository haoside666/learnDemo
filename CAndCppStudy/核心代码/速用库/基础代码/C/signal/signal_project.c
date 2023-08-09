#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void do_sig(int num)
{

}

int main(int argc,char *argv[])
{
	int length;
	scanf("%d",&length);
	signal(SIGUSR2,do_sig);
	signal(SIGUSR2,do_sig);
	return 0;
}
