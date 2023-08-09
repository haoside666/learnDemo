#include "mytree.h"
#include "mystack.h"
#include "myqueue.h"
void InsertNode(BinTree* root, Element x)
{
	BinTree temp=(BinTree)malloc(sizeof(TREENODE));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
	*root=temp;
}

void DeleteNode(BinTree* root)
{
	if(*root!=NULL)
		free(*root);
	*root=NULL;
}

int IsEmpty(BinTree root)
{
	return (root==NULL);
}

void PreorderTraversal(BinTree root)
{
	if(root==NULL) return;
	printf("%d ",root->data.age);
	PreorderTraversal(root->left);
	PreorderTraversal(root->right);
}

void InorderTraversal(BinTree root)
{
	if(root==NULL) return;
	InorderTraversal(root->left);
	printf("%d ",root->data.age);
	InorderTraversal(root->right);
}

void PostorderTraversal(BinTree root)
{
	if(root==NULL) return;
	PostorderTraversal(root->left);
	PostorderTraversal(root->right);
	printf("%d ",root->data.age);
}

void Preorder2(BinTree root)
{
	Stack mystack;
	stack_init(&mystack);
	BinTree temp=root;
	while(temp||!stack_isEmpty(mystack))
	{
		while(temp)
		{
			stack_push(mystack,temp);
			printf("%d ",temp->data.age);
			temp=temp->left;
		}
		if(!stack_isEmpty(mystack))
		{
			temp=stack_pop(mystack);			
			temp=temp->right;
		}
	}
	if(mystack!=NULL)
		free(mystack);
}

void Inorder2(BinTree root)
{
	Stack mystack;
	stack_init(&mystack);
	BinTree temp=root;
	while(temp||!stack_isEmpty(mystack))
	{
		while(temp)
		{
			stack_push(mystack,temp);
			temp=temp->left;
		}
		if(!stack_isEmpty(mystack))
		{
			temp=stack_pop(mystack);
			printf("%d ",temp->data.age);
			temp=temp->right;
		}
	}
	if(mystack!=NULL)
		free(mystack);
}

void Postorder2(BinTree root)
{
	Stack mystack;
	Stack remystack;
	stack_init(&mystack);
	stack_init(&remystack);
	BinTree temp=root;
	while(temp||!stack_isEmpty(mystack))
	{
		while(temp)
		{
			stack_push(mystack,temp);
			stack_push(remystack,temp);
			temp=temp->right;
		}
		if(!stack_isEmpty(mystack))
		{
			temp=stack_pop(mystack);			
			temp=temp->left;
		}
	}
	while(!stack_isEmpty(remystack))
	{
		printf("%d ",stack_pop(remystack)->data.age);
	}
	if(mystack!=NULL)
		free(mystack);
	if(remystack!=NULL)
		free(remystack);
}

void LevelorderTraversal(BinTree root)
{
	if(root==NULL) return;
	Queue myqueue;
	queue_init(&myqueue);
	queue_addQ(myqueue,root);
	BinTree temp;
	while(!queue_isEmpty(myqueue))
	{
		temp=queue_deleteQ(myqueue);
		printf("%d ",temp->data.age);
		if(temp->left)
		{
			queue_addQ(myqueue,temp->left);
		}
		if(temp->right)
		{
			queue_addQ(myqueue,temp->right);
		}
	}
}


