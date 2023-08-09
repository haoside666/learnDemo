#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void* do_pthread(void *arg)
{
	printf("helloworld\n");
}
int main(int argc,char* argv[])
{
	pthread_t tid;
	pthread_create(&tid,NULL,do_pthread,NULL);
	pthread_join(tid,NULL);
	printf("wocao\n");
	return 0;
}
