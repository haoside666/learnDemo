#ifndef __MYTREE__
#define __MYTREE__
#include <stdio.h>
typedef struct
{
	int age;
}Element;

typedef struct TreeNode* BinTree;
struct TreeNode
{
	Element data;
	BinTree left;
	BinTree right;
}TREENODE;

void InsertNode(BinTree* root,Element x);
void DeleteNode(BinTree* root);
int IsEmpty(BinTree root);

void PreorderTraversal(BinTree root);
void InorderTraversal(BinTree root);
void PostorderTraversal(BinTree root);
void LevelorderTraversal(BinTree root);

void Preorder2(BinTree root);
void Inorder2(BinTree root);
void Postorder2(BinTree root);
void Levelorder2(BinTree root);

#endif



