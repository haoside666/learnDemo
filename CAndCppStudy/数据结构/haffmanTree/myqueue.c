#include "myqueue.h"
#include <stdlib.h>
void queue_init(Queue* pmyqueue)
{
	(*pmyqueue)=(Queue)malloc(sizeof(QNODE));
	(*pmyqueue)->front=NULL;
	(*pmyqueue)->rear=NULL;
}

void queue_addQ(Queue myqueue,queue_ElementType data)
{
	pnode temp=(pnode)malloc(sizeof(QUEUENODE));
	temp->data=data;
	if(myqueue->front==NULL)
	{
		myqueue->front=myqueue->rear=temp;
	}else
	{
		myqueue->rear->next=temp;
		myqueue->rear=temp;
	}	
}

queue_ElementType queue_deleteQ(Queue myqueue)
{
	if(myqueue->front==myqueue->rear&&myqueue->front!=NULL)
	{
		queue_ElementType data=myqueue->front->data;
		free(myqueue->front);
		myqueue->front=myqueue->rear=NULL;
		return data;
	}
	pnode p=myqueue->front;
	queue_ElementType data=p->data;
	myqueue->front=p->next;
	free(p);
	return data;
}

bool queue_isEmpty(Queue myqueue)
{
	return myqueue->front==NULL;
}
