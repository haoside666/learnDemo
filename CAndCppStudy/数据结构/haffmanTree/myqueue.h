#ifndef __MYQUEUE__
#define __MYQUEUE__

#include "union.h"

typedef haffmantree queue_ElementType;

typedef struct queuenode* pnode;
typedef struct queuenode
{
	queue_ElementType data;
	pnode next;
}QUEUENODE;

typedef struct QNode* Queue;
typedef struct QNode
{
	pnode front;
	pnode rear;
}QNODE;
#ifndef __BOOL__
#define __BOOL__
typedef enum{false,true}bool;
#endif

void queue_init(Queue* pmyqueue);

void queue_addQ(Queue myqueue,queue_ElementType data);

queue_ElementType queue_deleteQ(Queue myqueue);

bool queue_isEmpty(Queue myqueue);
#endif
