#include<stdio.h>
#include<pthread.h>

void* thread1(void* arg)
{
    printf("i am thread1,my tid is %u\n",pthread_self());
	int i=0;
	int result=0;
	for(;i<100;i++)
	{
		result += i;
	}
	printf("thread1 result = %d\n",result);
    return NULL;
}

void* thread2(void* arg)
{
    printf("i am thread2,my tid is %u\n",pthread_self());
	int i=0;
	int result=0;
	for(;i<100;i++)
	{
		result ^= i;
	}
	printf("thread2 result = %d\n",result);
    return NULL;
}

int main()
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,thread1,NULL);
    pthread_create(&tid2,NULL,thread2,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL); 

    return 0;
}