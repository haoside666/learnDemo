#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	int *arr;
	int length;
	int maxsize;
}List;


void init(List* lis)
{
	lis->arr=NULL;
	lis->length=lis->maxsize=0;
}
void insertData(List* lis,int i,int data)
{
	if(lis->length==lis->maxsize)
	{
		if(lis->arr==NULL)
		{
			lis->maxsize=512;
			lis->arr=(int *)malloc(sizeof(int)*lis->maxsize);
		}else
		{
			if(lis->maxsize<=8192)
			{
				lis->maxsize+=512;
			}else
			{	
				lis->maxsize*=2;
			}				
			lis->arr=(int *)realloc(lis->arr,sizeof(int)*lis->maxsize);
		}
	}
	if(i<1||i>lis->length+1)
	{
		fprintf(stderr,"insert fail!\n");
		return;
	}
	for(int j=lis->length-1;j>=i-1;j--)
	{
		lis->arr[j + 1] = lis->arr[j];
	}
	lis->arr[i-1]=data;
	lis->length++;
}
void deleteData(List *lis,int i)
{
	if(i<1||i>lis->length)
	{
		fprintf(stderr,"delete fail!\n");
		return;
	}
	for(int j=i;i<lis->length;i++)
	{
		lis->arr[j-1]=lis->arr[j];
	}
	lis->length--;
}
int findData(List *lis,int data)
{
	for(int i=0;i<lis->length;i++)
	{
		if(lis->arr[i]==data)
			return i+1;
	}
	return -1;
}
void printlist(List *lis)
{
	for(int i=0;i<lis->length;i++)
	{
		printf("%d ",lis->arr[i]);
	}
	printf("\n");
}
void deletelist(List *lis)
{
	if(lis->arr!=NULL)
		free(lis->arr);
	lis->arr=NULL;
	lis->length=lis->maxsize=0;
}
int main(int argc,char *argv[])
{
	List mylist;
	init(&mylist);
	insertData(&mylist,1,1);
	printlist(&mylist);
	insertData(&mylist,2,2);
	insertData(&mylist,3,3);
	printlist(&mylist);
	deleteData(&mylist,2);
	printlist(&mylist);
	deletelist(&mylist);
}
