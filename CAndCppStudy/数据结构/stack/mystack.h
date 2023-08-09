#ifndef __MYSTACK__
#define __MYSTACK__
#include <stdlib.h>
#include "mytree.h"
typedef BinTree stack_ElementType;

typedef struct stacknode* Stack;
typedef struct stacknode
{
	stack_ElementType data;           
	Stack next;   
}STACKNODE;
#ifndef __BOOL__
#define __BOOL__
typedef enum{false,true}bool;
#endif
void stack_init(Stack* pmystack);

void stack_push(Stack mystack,stack_ElementType data);

stack_ElementType stack_pop(Stack mystack);

stack_ElementType stack_top(Stack mystack);

bool stack_isEmpty(Stack mystack);

#endif
