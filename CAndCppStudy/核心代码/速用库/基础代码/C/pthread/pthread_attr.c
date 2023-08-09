#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
void* th_fun(void* arg)
{
	int n=10;
	while(n--)
	{
		printf("%u %d\n",(unsigned int)pthread_self(),n);
		sleep(1);
	}
	return (void *)1;
}

int main(int argc,char *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	int err;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_create(&tid,&attr,th_fun,(void *)0);
	err=pthread_join(tid,NULL);
	while(1)
	{		
		if(err!=0)
		{
			printf("%s\n",strerror(err));
			sleep(10);
			pthread_exit(NULL);
		}
		
	}

	return 0;
}
