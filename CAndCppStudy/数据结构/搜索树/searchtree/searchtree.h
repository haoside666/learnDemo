#ifndef __SEARCHTREE__
#define __SEARCHTREE__
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
#endif
