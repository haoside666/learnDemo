#ifndef __UNION__
#define __UNION__

typedef struct TreeNode* haffmantree;
struct TreeNode
{
	int weight;
	haffmantree left;
	haffmantree right;
};

typedef haffmantree ElementType;
#ifndef __BOOOL__
#define __BOOL__
typedef enum{false,true} bool;
#endif
typedef struct HeapNode* MinHeap;
struct HeapNode
{
	ElementType* data;
	int size;
	int capacity;
};



haffmantree buildhuffmantree(MinHeap h);


MinHeap create(int maxsize);
void insert(MinHeap h,ElementType data);
ElementType DeleteMin(MinHeap h);
bool isfull(MinHeap h);
bool isEmpty(MinHeap h);
void freeheap(MinHeap h);
void PercDown(MinHeap H, int p);
void BuildHeap(MinHeap H);
void LevelorderTraversal(haffmantree h);
void freehaffmantree(haffmantree h);
#endif
