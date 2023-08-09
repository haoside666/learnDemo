#include "mystack.h"

void stack_init(Stack* pmystack)
{
	*pmystack=(Stack)malloc(sizeof(STACKNODE));
	(*pmystack)->next=NULL;
}

void stack_push(Stack mystack,stack_ElementType data)
{
	Stack temp=(Stack)malloc(sizeof(STACKNODE));
	temp->data=data;
	temp->next=mystack->next;
	mystack->next=temp;
}

stack_ElementType stack_pop(Stack mystack)
{
	stack_ElementType data;
	Stack p=mystack->next;
	mystack->next=mystack->next->next;
	data=p->data;
	free(p);
	return data;
}

stack_ElementType stack_top(Stack mystack)
{
	return mystack->next->data;
}

bool stack_isEmpty(Stack mystack)
{
	return mystack->next==NULL;
}
