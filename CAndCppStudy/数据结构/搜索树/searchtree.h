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

BinTree find();

BinTree findmin();

BinTree findmax();

void LevelorderTraversal(BinTree root);

void freetree(BinTree root);
#endif
