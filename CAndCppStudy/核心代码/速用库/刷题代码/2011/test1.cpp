#include <iostream>
using namespace std;
using DataType=int;

typedef struct node
{
	DataType val;
	struct node* next;
}NODE;
typedef NODE* LinkList;
typedef NODE* PNode;

int SearchPN_link(LinkList list,DataType x,PNode *pPrev,PNode *pNext)
{
    PNode head=list;
    PNode p=list->next;
    while(p)
    {
        if(p->val==x)
        {
            *pPrev=head;
            *pNext=p->next;
            return 0;
        }
        head=p;
        p=p->next;
    }
    *pPrev=*pNext=nullptr;
    return 0;
}

int main()
{
    return 0;
}