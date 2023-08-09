#include "union.h"
#include <stdlib.h>
#include <stdio.h>
#include "myqueue.h"
haffmantree buildhuffmantree(MinHeap h)
{
	int i;
	haffmantree T;
	int len=h->size;
	for(i=1;i<len;i++)
	{
		T=malloc(sizeof(struct TreeNode));
		
		T->left=DeleteMin(h);
		T->right=DeleteMin(h);
		T->weight=T->left->weight+T->right->weight;
		insert(h,T);
	}
	T=DeleteMin(h);
	return T;
}

void LevelorderTraversal(haffmantree h)
{
	if(h==NULL) return;
	Queue myqueue;
	queue_init(&myqueue);
	queue_addQ(myqueue,h);
	haffmantree temp;
	while(!queue_isEmpty(myqueue))
	{
		temp=queue_deleteQ(myqueue);
		printf("%d ",temp->weight);
		if(temp->left)
		{
			queue_addQ(myqueue,temp->left);
		}
		if(temp->right)
		{
			queue_addQ(myqueue,temp->right);
		}
	}
	printf("\n");
	if(myqueue!=NULL)
		free(myqueue);
}

void freehaffmantree(haffmantree h)
{
	if(h->left)	freehaffmantree(h->left);
	if(h->right) freehaffmantree(h->right);
	free(h);
}
