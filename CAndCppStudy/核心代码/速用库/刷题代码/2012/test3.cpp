
#include <queue>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef int searchtree_ElemenType;
typedef struct seaechtreenode* BinTree;
typedef struct seaechtreenode
{
	searchtree_ElemenType data;
	BinTree left;
	BinTree right;
}SEARCHTREENODE;

BinTree insertData(BinTree root,searchtree_ElemenType data);
BinTree deleteData(BinTree root,searchtree_ElemenType data);
int findElePos(BinTree root, searchtree_ElemenType data);
BinTree find(BinTree root, searchtree_ElemenType data);
BinTree findmin(BinTree root);
BinTree findmax(BinTree root);
void LevelorderTraversal(BinTree root);
void freetree(BinTree root);

int main(int argc,char *argv[])
{
	BinTree root=NULL;	
	root=insertData(root,39);
	insertData(root,101);
	insertData(root,25);
	insertData(root,63);
	printf("cengxu:\n");
	LevelorderTraversal(root);
	printf("\n尝试删除数据5\n");
	deleteData(root,5);
	printf("cengxu:\n");
	LevelorderTraversal(root);
	printf("\nfind 63:\n");
	BinTree s=find(root,63);
	printf("%p %d\n",s,s->data);
	printf("63所在层数:%d\n",findElePos(root,63));
	//printf("MAX=%d\n",findmax(root)->data);
	//printf("MIN=%d\n",findmin(root)->data);
	freetree(root);
	return 0;
}


BinTree insertData(BinTree root, searchtree_ElemenType data)
{
	if (root == NULL)
	{
		root = (BinTree)malloc(sizeof(SEARCHTREENODE));
		root->data = data;
		root->left = root->right = NULL;
	}
	else
	{
		if (root->data > data)
		{
			root->left = insertData(root->left, data);
		}
		else if (root->data < data)
		{
			root->right = insertData(root->right, data);
		}
	}
	return root;
}
BinTree deleteData(BinTree root, searchtree_ElemenType data)
{
	BinTree temp;
	if (root == NULL)
		printf("not find\n");
	else if (root->data > data)
	{
		root->left = deleteData(root->left, data);
	}
	else if (root->data < data)
	{
		root->right = deleteData(root->right, data);
	}
	else
	{
		if (root->left != NULL && root->right != NULL)
		{
			temp = findmin(root->right);
			/*
			temp=findmin(root->right); 
			等价于
			temp=root->right;
			while(!temp->left) temp=temp->left;
			*/
			root->data = temp->data;
			root->right = deleteData(root->right, root->data);
		}
		else
		{
			temp = root;
			if (root->left != NULL)
				root = root->left;
			else if (root->right != NULL)
				root = root->right;
			free(temp);
		}
	}
	return root;
}

int findElePos(BinTree root, searchtree_ElemenType data)
{
	int index = 0;
	while (root)
	{
		index++;
		if (root->data > data)
		{
			if(root->left) root=root->left;
			else return 0;

		}else if (root->data < data)
		{
			if(root->right) root=root->right;
			else return 0;
		}else{
			break;
		}
	}
	return index;
}

BinTree find(BinTree root, searchtree_ElemenType data)
{
	if (root == NULL)
	{
		printf("not find\n");
	}
	else
	{
		if (root->data > data)
		{
			return find(root->left, data);
		}
		else if (root->data < data)
		{
			return find(root->right, data);
		}
		else
		{
			return root;
		}
	}
	return root;
}

BinTree findmin(BinTree root)
{
	if (root != NULL)
	{
		while (root->left != NULL)
			root = root->left;
	}
	return root;
}

BinTree findmax(BinTree root)
{
	if (root != NULL)
	{
		while (root->right != NULL)
			root = root->right;
	}
	return root;
}

void LevelorderTraversal(BinTree root)
{
	if (root == NULL)
		return;
	queue<BinTree> myqueue;
	myqueue.push(root);
	BinTree temp;
	while (!myqueue.empty())
	{
		temp = myqueue.front();
        myqueue.pop();
		printf("%d ", temp->data);
		if (temp->left)
		{
            myqueue.push(temp->left);
		}
		if (temp->right)
		{
            myqueue.push(temp->right);
        }
	}
	printf("\n");
}

void freetree(BinTree root)
{
	if (root->left)
		freetree(root->left);
	if (root->right)
		freetree(root->right);
	free(root);
}

