#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void cleanup()
{
	printf("cleanup\n");
}
void cleanup1()
{
	printf("cleanup1\n");
}
void cleanup2()
{
	printf("cleanup2\n");
}
void *test_cancel(void)
{
	pthread_cleanup_push(cleanup,NULL);
	pthread_cleanup_push(cleanup2,NULL);
	pthread_cleanup_push(cleanup1,NULL);
  	printf("test_cancel\n");
	while(1)
	{
		printf("test message\n");
		sleep(1);
	}
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(2);
}

int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,(void *)test_cancel,NULL);
	sleep(2);
	pthread_cancel(tid);
	pthread_join(tid,NULL);
}
