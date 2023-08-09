#include <stdio.h>
#include <stdlib.h>
typedef struct node* stack;
typedef struct data
{
	int N;
	char src,mid,dest;
}DATA;
typedef struct node
{
	DATA data;
	stack next;
}NODE;
typedef enum{false,true} bool;
void init(stack* pmystack)
{
	*pmystack=(stack)malloc(sizeof(NODE));
	(*pmystack)->next=NULL;
}

void push(stack mystack,DATA data)
{
	stack temp=(stack)malloc(sizeof(NODE));
	temp->data=data;
	temp->next=mystack->next;
	mystack->next=temp;
}

DATA pop(stack mystack)
{
	stack p=mystack->next;
	DATA data= p->data;
	mystack->next=p->next;
	free(p);
	return data;
}

bool isEmpty(stack mystack)
{
	return mystack->next==NULL;
}

void hanoi(int n, char x, char y, char z)
{
	DATA index,temp;
	stack mystack;
	init(&mystack);
	temp.N=n;
	temp.src=x;
	temp.mid=y;
	temp.dest=z;
	push(mystack,temp);
	
	while(!isEmpty(mystack))
	{
		index=pop(mystack);//n,a,b,c
		if(index.N>1)
		{			
			temp = index;
            temp.N--;
            temp.src = index.mid;
            temp.mid = index.src;
            push(mystack, temp); //n-1,b,a,c  回溯 先进后出

            temp = index;
            temp.N = 1;
            push(mystack, temp); //1,a,b,c

            temp =index;
            temp.N--;
            temp.mid = index.dest;
            temp.dest = index.mid;
            push(mystack, temp); //n-1,a,c,b  
		}else
		{
			printf("%c -> %c\n",index.src,index.dest);
		}
	}
	free(mystack);
}

void hanoi2(int n, char x, char y, char z)
{
	hanoi(n-1,x,z,y);
	if(n==1) printf("%c->%c\n",x,z);
	hanoi(n-1,y,x,z);
}

int main()
{
	int n;
	scanf("%d",&n);
	hanoi2(n,'a','b','c');
	return 0;
}
