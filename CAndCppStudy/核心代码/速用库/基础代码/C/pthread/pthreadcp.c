#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int seat=0,s_seat=0,readlen=0;
char *p1,*p2;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
int getrwx(const char * pathname)
{
	struct stat buf;
	int temp=0;
	int arr[16],k=15;
	if(stat(pathname,&buf)==-1)
	{
		perror("stat:");
		exit(1);
	}
	memset(arr,0,sizeof(int)*16);
	while(buf.st_mode!=0)
	{
		arr[k--]=buf.st_mode%2;
		buf.st_mode/=2;		
	}
	for(int i=7;i<16;i++)
	{
		if(arr[i]!=0) 
		{
			switch(i%3)
			{
				case 0: temp+=1; break;
				case 1:	temp+=4; break;
				case 2:	temp+=2; break;
			}
		}
		if(i%3==0&&i!=15)
		{
			temp*=8;
		}		
	}
	
	return temp;
}
void* th_fun(void * arg)
{
	char *pp1=p1+seat*(int)arg;
	char *pp2=p2+seat*(int)arg;
	char *pp3=p1+seat*((int)arg+1);
	while(pp1!=pp3)
	{
		*pp2=*pp1;
		pp1++;
		pp2++;
		pthread_mutex_lock(&counter_mutex);
		readlen++;
		pthread_mutex_unlock(&counter_mutex);
	}
}	
void* th_fun2(void * arg)
{
	char *pp1=p1+seat*(int)arg;
	char *pp2=p2+seat*(int)arg;
	int length=0;	
	while(length!=s_seat)
	{
		*pp2=*pp1;
		pp1++;
		pp2++;
		length++;
		pthread_mutex_lock(&counter_mutex);
		readlen++;
		pthread_mutex_unlock(&counter_mutex);
	}
	
}
int main(int argc,char *argv[])
{
	if(argc<3)
	{
		printf("./app src dest (pthread_number)\n");
		exit(1);
	}
	int pth_number=5;
	int err;
	
	if(argc==4)
	{
		pth_number=atoi(argv[3]);
	}
		
	int fd1,fd2,mode;
	off_t len;
	pthread_t tid;
	pthread_attr_t attr;

	fd1=open(argv[1],O_RDONLY);
	len=lseek(fd1,0,SEEK_END);
	
	if(access(argv[2],F_OK)==-1)
	{
		mode=getrwx(argv[1]);
		umask(0);
		fd2=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,mode);
		lseek(fd2,len-1,SEEK_SET);
		write(fd2,"\0",1);
	}else
	{
		fd2=open(argv[2],O_RDWR);		
	}
	
	p1=(char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd1,0);
	if(p1==MAP_FAILED)
	{
		perror("p1 mmap:");
		exit(1);
	}
	close(fd1);
	p2=(char *)mmap(NULL,len,PROT_WRITE,MAP_SHARED,fd2,0);
	if(p2==MAP_FAILED)
	{
		perror("p2 mmap:");
		exit(1);
	}
	close(fd2);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	seat=len/pth_number;
	if(len%pth_number!=0) seat++;
		s_seat=len-seat*(pth_number-1);
	printf("len=%d\n",len);
	printf("seat=%d\n",seat);
	printf("s_seat=%d\n",s_seat);
	sleep(1);
	for(int i=0;i<pth_number-1;i++)
	{
		err=pthread_create(&tid,&attr,th_fun,(void *)i);
		if(err!=0)
		{
			fprintf(stderr,"create pthread fail:%s\n",strerror(err));
			exit(1);
		}
	}
	pthread_create(&tid,&attr,th_fun2,(void *)(pth_number-1));
	while(readlen!=len)
	{
		printf("%f%%  readlen=%d len=%d\n",(100.0)*readlen/len,readlen,len);
		usleep(100000);
	}
	printf("%f%%\n",(100.0)*readlen/len);
	munmap(p1,len);
	munmap(p2,len);
	
	return 0;
}
