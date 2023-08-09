#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

void deleteList(List L);
int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
	Print(L1);
	Print(L2);
    L = Merge(L1, L2);	
	printf("--------------------------------\n");
    Print(L);
    Print(L1);
    Print(L2);
	deleteList(L);
    return 0;
}

void deleteList(List L)
{
	List p,q;
	p=q=L;
	while(p)
	{
		q=q->Next;
		free(p);
		p=q;
	}
}
void insertData(List head,int data)
{
	List temp=(List)malloc(sizeof(struct Node));
	temp->Data=data;
	temp->Next=NULL;
	List p=head;
	while(p->Next!=NULL)
		p=p->Next;
	temp->Next=p->Next;
	p->Next=temp;
}

List Read()
{
	List L=(List)malloc(sizeof(struct Node));
	L->Next=NULL;
	int N,number;
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&number);
		insertData(L,number);
	}
	return L;
}
void Print(List L)
{
	List p=L->Next;
	if(p==NULL) printf("NULL");
	while(p)
	{
		printf("%d ",p->Data);
		p=p->Next;
	}
	printf("\n");
}
List Merge(List L1,List L2)
{
	List p,p1,p2;
    List L=(List)malloc(sizeof(struct Node));
	L->Next=NULL;
	p=L;
	p1=L1->Next;
	p2=L2->Next;
    while(p1!=NULL&&p2!=NULL)
    {		
        if(p1->Data>p2->Data)
		{
			p->Next=p2;
			p2=p2->Next;
		}else if(p1->Data<p2->Data)
		{
			p->Next=p1;
			p1=p1->Next;
		}else
		{
			p->Next=p1;
			p1=p1->Next;
			p=p->Next;
			p->Next=p2;		
			p2=p2->Next;
		}
		p=p->Next;
    }
    if(p1!=NULL)
    {        
    	p->Next=p1;
		
    }
    if(p2!=NULL)
    {
        p->Next=p2;
    }
	L1->Next=NULL;
	L2->Next=NULL;
    return L;
}
