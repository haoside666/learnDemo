#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
typedef int ElementType;
typedef enum { push, pop, inject, eject, end } Operation;
typedef enum { false, true } bool;
typedef int Position;
typedef struct QNode *PtrToQNode;
struct QNode {
    ElementType *Data;      /* 存储元素的数组   */
    Position Front, Rear;   /* 队列的头、尾指针 */
    int MaxSize;            /* 队列最大容量     */
};
typedef PtrToQNode Deque; 

Deque CreateDeque( int MaxSize )
{   /* 注意：为区分空队列和满队列，需要多开辟一个空间 */
    Deque D = (Deque)malloc(sizeof(struct QNode));
    MaxSize++;
    D->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    D->Front = D->Rear = 0;
    D->MaxSize = MaxSize;
    return D;
}

bool Push( ElementType X, Deque D );
ElementType Pop( Deque D );
bool Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* 裁判实现，细节不表 */
void PrintDeque(Deque D ); /* 裁判实现，细节不表 */

int main()
{
    ElementType X;
    Deque D;
    int N, done = 0;

    scanf("%d", &N);
    D = CreateDeque(N);
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Deque is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            else printf("%d is out\n", X);
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Deque is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            else printf("%d is out\n", X);
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

Operation GetOp()
{
	fflush(stdin);
	char s[10];
	scanf("%s",s);
	if(strcmp(s,"Push")==0) return push;
	if(strcmp(s,"Pop")==0) return pop;
	if(strcmp(s,"Inject")==0)  return inject;
	if(strcmp(s,"Eject")==0) return eject;
	if(strcmp(s,"End")==0)  return end;
}

void PrintDeque(Deque D)
{
	printf("Inside Deque:");
	int data;
	while(1)
	{
		data=Pop(D);
		if(data==ERROR) break;
		else printf("%d ",data);
	}
	printf("\n");
}
/*push 往头指针前一个位置插入元素*/
bool Push( ElementType X, Deque D )
{
    int temp=(D->Front+D->MaxSize-1)%D->MaxSize;
    if(temp==D->Rear)
        return false;  
    D->Front=temp;
    D->Data[D->Front]=X;
    return true;
}
/*pop 返回头指针指向位置上的元素 头指针后移*/
ElementType Pop( Deque D )
{
    if(D->Front==D->Rear)
        return ERROR;
    int data=D->Data[D->Front];  
    D->Front=(D->Front+1)%(D->MaxSize); 
    return data;
}
/*Inject 往尾指针位置插入元素尾指针后移*/
bool Inject( ElementType X, Deque D )
{
    int temp=(D->Rear+1)%D->MaxSize;
    if(temp==D->Front)
        return false;
    D->Data[D->Rear]=X;  
    D->Rear=temp;   
    return true;
}
/*Eject 返回尾指针前一个位置的元素*/
ElementType Eject( Deque D )
{
    if(D->Front==D->Rear)
        return ERROR;   
    D->Rear=(D->Rear+D->MaxSize-1)%(D->MaxSize);
    int data=D->Data[D->Rear];
    return data;
}
