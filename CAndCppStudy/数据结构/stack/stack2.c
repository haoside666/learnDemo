/* 线性栈
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
typedef struct stack
{
	int arr[MAXSIZE];
	int top;
}Stack;
typedef enum{true=1,false=0}bool;
void init(Stack* mystack)
{
	memset(mystack->arr,0,MAXSIZE);
	mystack->top=-1;
}
void push(Stack* mystack,int data)
{
	if(mystack->top==MAXSIZE-1)
	{
		fprintf(stderr,"stack overflow\n");
		return;
	}
	mystack->arr[++mystack->top]=data;
}
int pop(Stack* mystack)
{
	return mystack->arr[mystack->top--];
}

bool isEmpty(Stack* mystack)
{
	return mystack->top==-1;
}

int main(int argc,char *argv[])
{
	Stack mystack;
	init(&mystack);
	for(int i=0;i<3;i++)
	{
		push(&mystack,i+1);
	}
	for(int i=0;i<4;i++)
	{
		if(isEmpty(&mystack)==false)
			printf("%d ",pop(&mystack));
		else
			printf("NULL ");
	}
	printf("\n");
	return 0;
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node* Stack;
typedef struct node
{
	int data;           
	Stack next;   
}NODE;
typedef enum{true=1,false=0}bool;
void init(Stack* pmystack)
{
	*pmystack=(Stack)malloc(sizeof(NODE));
	(*pmystack)->data=0;
	(*pmystack)->next=NULL;
}

void push(Stack mystack,int data)
{
	Stack temp=(Stack)malloc(sizeof(NODE));
	temp->data=data;
	temp->next=mystack->next;
	mystack->next=temp;
	mystack->data++;
}

int pop(Stack mystack)
{
	int data;
	Stack p=mystack->next;
	mystack->next=mystack->next->next;
	mystack->data--;
	data=p->data;
	free(p);
	return data;
}

bool isEmpty(Stack mystack)
{
	return mystack->data==0;
}

int main(int argc,char*argv[])
{
	Stack mystack;
	init(&mystack);
	for(int i=0;i<3;i++)
	{
		push(mystack,i+1);
	}
	for(int i=0;i<4;i++)
	{
		if(isEmpty(mystack)==false)
		{
			printf("%d\n",pop(mystack));
		}else
		{
			fprintf(stderr,"stack empty\n");
		}
	}
	return 0;
}


