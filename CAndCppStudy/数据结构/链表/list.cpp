#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int id;
	struct node* next;
}NODE;
typedef NODE* List;

int length(List head)
{
	List p=head;
	int i=0;
	while(p)
	{
		i++;
		p=p->next;
	}																																																																																																																	
	return i;
}
void insertData(List* phead,int i,int data)
{
	List temp=(List)malloc(sizeof(NODE));
	temp->id=data;
	temp->next=NULL;
	List p=*phead;
	if(i==1)
	{
		if(*phead==NULL)
			*phead=temp;
		else
		{
			temp->next=*phead;
			*phead=temp;
		}
	}
	else 
	{
		if(i<1||i>length(p)+1)
		{
			fprintf(stderr,"insert fail\n");
			return;
		}else
		{
			int j=2;
			while(j<i)
			{
				p=p->next;
				j++;
			}
			temp->next=p->next;
			p->next=temp;
		}		
	}
}

void deleteData(List* head,int i)
{
	List p=*head;
	List q=*head;
	int j=2;
	if(i<1||i>length(p))
	{
		fprintf(stderr,"delete fail\n");
		return;
	}
	else if(i==1)
	{
		p=p->next;
		free(q);
		*head=p;
	}else
	{
		while(j<i)
		{
			p=p->next;
			j++;
		}
		q=p->next;
		p->next=p->next->next;
		free(q);
	}
}

int findData(List head,int data)
{
	List p=head;
	int i=1;
	while(p)
	{
		if(p->id==data)
			return i;
		p=p->next;
	}
	return -1;
}
void printList(List head)
{
	List p=head;
	while(p)
	{
		printf("%d ",p->id);
		p=p->next;
	}
	printf("\n");
}
void deleteList(List head)
{
	List p,q;
	p=q=head;
	while(p)
	{
		q=q->next;
		free(p);
		p=q;
	}
}


void DeleteKeys(NODE** first,int key)
{
	NODE *p=*first;
	while((*first)->id==key&&(*first)!=NULL)
	{
		(*first)=(*first)->next;
		delete p;
		p=*first;
	}
	if(first==NULL) return;
	NODE *q=p->next;
	while(q!=NULL)
	{
		if(q->id==key)
		{
			q=q->next;
			delete p->next;
			p->next=q;
		}else{
			q=q->next;
			p=p->next;
		}
	}
}

int main(int argc,char *argv[])
{
	List head=NULL;

	insertData(&head,1,45);
	insertData(&head,2,6);
	insertData(&head,3,45);
	insertData(&head,4,17);
	insertData(&head,5,23);
	insertData(&head,6,38);
	insertData(&head,7,45);
	insertData(&head,8,7);
	printList(head);
	DeleteKeys(&head,45);
	printList(head);


	return 0;
}
