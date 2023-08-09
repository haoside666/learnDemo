#include <stdio.h>
#include "searchtree.h"
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


