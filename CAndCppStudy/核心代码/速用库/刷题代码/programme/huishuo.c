/*
#include <stdio.h>
#define MAXSIZE 100
typedef struct node* stack;
typedef struct node
{
	int data[MAXSIZE];
	int top;
}NODE;
typedef enum{false,true} bool;
void init(stack mystack)
{
	mystack->top=-1;
}
void push(stack mystack,int data)
{
	mystack->data[++mystack->top]=data;
}
int pop(stack mystack)
{
	return mystack->data[mystack->top--];
}
bool isEmpty(stack mystack)
{
	return mystack->top==-1;
}
void huishuo(int i)
{
	if(i==100) return;
	printf("%d\n",i);
	huishuo(i+1);
	printf("%d\n",i);
}

void fun(int i)
{
	NODE mystack;	
	init(&mystack);
	push(&mystack,i);
	while(!isEmpty(&mystack))
	{
		if(i!=100)
		{		
			printf("%d\n",mystack.data[mystack.top]);
			i++;
			push(&mystack,i);
		}else
		{
			printf("%d\n",pop(&mystack));
		}
	}
}
int main()
{
	//huishuo(1);
	fun(1);
	return 0;
}

*/















#include <stdio.h>
#define MAXSIZE 10

typedef struct ndoe
{
	char arr[10];
	int id;
}NODE;
typedef NODE ElementType;

void swap2(ElementType output[],int first,int i)
{
	ElementType temp=output[i];
	for(int j=i;j>first;j--)
	{
		output[j]=output[j-1];
	}
	output[first]=temp;
}
void swap3(ElementType output[],int first,int i)
{
	ElementType temp=output[first];
	for(int j=first;j<i;j++)
	{
		output[j]=output[j+1];
	}
	output[i]=temp;
}
void print(ElementType output[],int len)
{	
	printf("***************************\n");
	for(int i=0;i<len;i++)
		printf("%s %d\n",output[i].arr,output[i].id);
	printf("***************************\n");
}
void backtrack(ElementType output[], int first, int len)
{ 
	if(first ==len)
    {
		print(output,len);
		return;
	}
    for (int i = first; i <len; i++) {
		swap2(output,first,i);
		backtrack(output,first + 1,len);
		swap3(output,first,i);
    }
}
void permute(ElementType arr[],int N) 
{
    backtrack(arr, 0, N);
}


int main(int argc,char *argv[])
{
	//int N;
	//scanf("%d",&N);
	//int arr[MAXSIZE];
	//for(int i=0;i<N;i++)
	//	arr[i]=i+1;
	int N=3;
	NODE arr[3]={
		{"老一",1},
		{"老二",2},
		{"老三",3},		
	};
	permute(arr,N);
}
