#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

pthread_key_t key;
void *thread_one()
{
	printf("thread_one:int %d main process,the tid=%lu,pid=%ld\n",getpid(),pthread_self(),syscall(SYS_gettid));
}


void *thread_two()
{
	printf("thread_two:int %d main process,the tid=%lu,pid=%ld\n",getpid(),pthread_self(),syscall(SYS_gettid));
}

void *helloworld(char *argc)
{
	int *p;
	p=(int *)malloc(10*sizeof(int));
	printf("the message is %s\n",argc);
	printf("the child id is %lu\n",pthread_self());
	memset(p,'c',10);
	printf("p=%p\n",p);
	pthread_exit(p);
}

//pthread_setcancelstate
void *thread_function(void *arg) 
{
    int i, res, j;
    sleep(1);
    res = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    if (res != 0) 
	{
        perror("Thread pthread_setcancelstate failed");
        exit(EXIT_FAILURE);
    }
    printf("thread cancle type is disable,can't cancle this thread\n");
    for(i = 0; i <3; i++) 
	{
        printf("Thread is running (%d)...\n", i);
        sleep(1);
    }

    res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (res != 0) 
	{
        perror("Thread pthread_setcancelstate failed");
        exit(EXIT_FAILURE);
    }
	else
		printf("Now change ths canclestate is ENABLE\n");
	sleep(200); 
   pthread_exit(0);
}
 
void echomsg(void *t) 
{ 
	printf("destructor excuted in thread %u,param=%u\n",pthread_self(),((int *)t)); 
} 

void * child1(void *arg) 
{ 
	int i=10;
	int tid=pthread_self(); 
	printf("\nset key value %d in thread %u\n",i,tid); 
	pthread_setspecific(key,&i); 
	printf("thread one sleep 2 until thread two finish\n");
	sleep(2); 
	printf("\nthread %u returns %d,add is %u\n",tid,*((int *)pthread_getspecific(key)),(int *)pthread_getspecific(key)); 
} 

void * child2(void *arg) 
{ 
	int temp=20;
	int tid=pthread_self(); 
	printf("\nset key value %d in thread %u\n",temp,tid); 
	pthread_setspecific(key,&temp); 
	sleep(1); 
	printf("thread %u returns %d,add is %u\n",tid,*((int *)pthread_getspecific(key)),(int *)pthread_getspecific(key)); 
} 
//pthread_creat and pthread_join
void test1()
{
	pid_t pid;
	pthread_t tid_one,tid_two;
	if((pid=fork())==-1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0)
	{
		pthread_create(&tid_one,NULL,(void *)thread_one,NULL);
		pthread_join(tid_one,NULL);
	}

	else
	{
		pthread_create(&tid_two,NULL,(void *)thread_two,NULL);
		pthread_join(tid_two,NULL);
	}
	wait(NULL);
}

//pthread_exit
void test2()
{
	int error;
	int *temptr;
	
	pthread_t thread_id;
	
	pthread_create(&thread_id,NULL,(void *)*helloworld,"helloworld");
	printf("*p=%x,p=%x\n",*helloworld,helloworld);
	if(error=pthread_join(thread_id,(void **)&temptr))
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);	
	}
	printf("temp=%p,*temp=%c\n",temptr,*temptr);
	*temptr='d';
	printf("%c\n",*temptr);
	free(temptr);
	return;
}

//pthread_cancel
void test3()
{
	int res;
    pthread_t a_thread;
    void *thread_result;

    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (res != 0) 
	{
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Cancelling thread...\n");
    sleep(2);	
    res = pthread_cancel(a_thread);
    if (res != 0) 
	{
        perror("Thread cancelation failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) 
	{
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
//pthread_key_create
int test4() 
{ 
	pthread_t tid1,tid2; 
	pthread_key_create(&key,echomsg); 
	pthread_create(&tid1,NULL,(void *)child1,NULL); 
	pthread_create(&tid2,NULL,(void *)child2,NULL); 
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_key_delete(key); 
	return 0; 
} 
int main(int argc,char *agrv[])
{
	test1();
	//test2()
}
