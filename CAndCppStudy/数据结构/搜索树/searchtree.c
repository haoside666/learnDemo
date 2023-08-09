#include "searchtree.h"
#include "myqueue.h"
#include <stdlib.h>
#include <stdio.h>
BinTree insertData(BinTree root,searchtree_ElemenType data)
{
	if(root==NULL)
	{
		root=(BinTree)malloc(sizeof(SEARCHTREENODE));
		root->data=data;
		root->left=root->right=NULL;
	}else
	{
		if(root->data>data)
		{
			root->left=insertData(root->left,data);
		}else if(root->data<data)
		{
			root->right=insertData(root->right,data);
		}
	}
	return root;
}
BinTree deleteData(BinTree root,searchtree_ElemenType data)
{
	BinTree temp;
	if(root==NULL) printf("not find\n");
	else if(root->data>data)
	{
		root->left=deleteData(root->left,data);
	}else if(root->data<data)
	{
		root->right=deleteData(root->right,data);
	}else
	{
		if(root->left!=NULL&&root->right!=NULL)
		{
			temp=findmin(root->right);
			root->data=temp->data;
			root->right=deleteData(root->right,root->data);
		}else
		{
			temp=root;
			if(root->left!=NULL)
				root=root->left;
			else if(root->right!=NULL)
				root=root->right;
			free(temp);	
		}
	}
	return root;
}

BinTree find(BinTree root,searchtree_ElemenType data)
{
	if(root==NULL)
	{
		printf("not find\n");
	}else
	{
		printf("%d ",root->data);
		if(root->data>data)
		{
			return find(root->left,data);
		}else if(root->data<data)
		{
			return find(root->right,data);
		}
	}
	return root;
}

BinTree findmin(BinTree root)
{
	if(root!=NULL)
	{
		while(root->left!=NULL)
			root=root->left;
	}
	return root;
}

BinTree findmax(BinTree root)
{
	if(root!=NULL)
	{
		while(root->right!=NULL)
			root=root->right;
	}
	return root;
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
		printf("%d ",temp->data);
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

void freetree(BinTree root)
{
	if(root->left) freetree(root->left);
	if(root->right) freetree(root->right);
	free(root);
}

