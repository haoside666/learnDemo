#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100000

struct Node
{
	char addr[17];
	int data;
	char nextaddr[17];
}arr[MAXSIZE];
void swap(struct Node arr[],int i,int j);
int buildlist(struct Node arr[],char beginaddr[],int N);
void reverse(struct Node arr[],int N,int k);
void printlist(struct Node arr[],int N);
int main(int argc,char *argv[])
{
	int N,K;
	char beginaddr[17];
	scanf("%s %d %d",beginaddr,&N,&K);
	for(int i=0;i<N;i++)
	{
		scanf("%s %d %s",arr[i].addr,&arr[i].data,arr[i].nextaddr);
	}
	N=buildlist(arr,beginaddr,N);
	//printf("---------------------------\n");
	//printlist(arr,N);
	//printf("---------------------------\n");
	reverse(arr,N,K);
	printlist(arr,N);
	return 0;
}

void swap(struct Node arr[],int i,int j)
{
	struct Node temp;
	temp=arr[j];
	arr[j]=arr[i];
	arr[i]=temp;
}
int buildlist(struct Node arr[],char beginaddr[],int N)
{

	char findaddr[17];
	strcpy(findaddr,beginaddr);
	int i,j;
	for(i=0;i<N-1;i++)
	{		
		for(j=i;strcmp(arr[j].addr,findaddr)!=0;j++);
		swap(arr,i,j);
		strcpy(findaddr,arr[i].nextaddr);
		if(strcmp("-1",findaddr)==0)
			break;
		
	}
	return i+1;
}

void reverse(struct Node arr[],int N,int k)
{
	int cnt=N/k;
	int mid,i,j;
	mid=k/2;
	for(i=0;i<cnt;i++)
	{				
		for(j=0;j<mid;j++)
		{
			swap(arr,j+i*k,(i+1)*k-1-j);
		}	
	}
	for(i=0;i<cnt*k&&i!=N-1;i++)
		strcpy(arr[i].nextaddr,arr[i+1].addr);
	strcpy(arr[N-1].nextaddr,"-1");
}
void printlist(struct Node arr[],int N)
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("%s %d %s\n",arr[i].addr,arr[i].data,arr[i].nextaddr);
	}
}
