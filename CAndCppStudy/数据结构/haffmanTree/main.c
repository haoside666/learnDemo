#include <stdio.h>
#include <stdlib.h>
#include "union.h"
#include <mcheck.h>
int main(int argc,char*argv[])
{
	mtrace();
	MinHeap h=create(10);
	haffmantree T;
	for(int i=0;i<5;i++)
	{
		T=malloc(sizeof(struct TreeNode));
		T->weight=i+1;
		T->left=T->right=NULL;
		insert(h,T);
	}
	haffmantree myhaffmantree=buildhuffmantree(h);
	LevelorderTraversal(myhaffmantree);
	freeheap(h);
	muntrace();
	freehaffmantree(myhaffmantree);
	return 0;
}
