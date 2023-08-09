/*
L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且题目保证传入的数据是递减有序的。函数Insert要将X插入Data[]中合适的位置，以保持结果依然有序（注意：元素从下标0开始存储）。但如果X已经在Data[]中了，就不要插入，返回失败的标记false；如果插入成功，则返回true。另外，因为Data[]中最多只能存MAXSIZE个元素，所以如果插入新元素之前已经满了，也不要插入，而是返回失败的标记false。
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
typedef enum {false, true} bool;
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标0开始存储 */
void PrintList(List L); /* 裁判实现，细节不表 */
bool Insert(List L,ElementType X );

int main()
{
    List L;
    ElementType X;

    L = ReadInput();
    scanf("%d", &X);
    if ( Insert( L, X ) == false )
        printf("Insertion failed.\n");
    PrintList(L);
	if(L!=NULL)
		free(L);
    return 0;
}
List ReadInput()
{
	List L=(List)malloc(sizeof(struct LNode));
	L->Last=-1;
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&L->Data[++L->Last]);	
	}
	return L;
}
void PrintList(List L)
{
	for(int i=0;i<=L->Last;i++)
	{
		printf("%d ",L->Data[i]);
	}
	printf("\n");
}

bool Insert(List L, ElementType X)
{
    int begin=0,end=L->Last,mid,j;
	if(L->Last==MAXSIZE-1) return false;
    while(begin<=end)
    {
        mid=(begin+end)/2;
        if(L->Data[mid]==X)
            return false;
        else if(L->Data[mid]>X)
            begin=mid+1;	
        else 
		    end=mid-1;
    }
    j=begin;
    for(int i=L->Last;i>=j;i--)
    {
        L->Data[i+1]=L->Data[i];
    }
    L->Data[j]=X;
    L->Last++;
    return true;
}
/*
int Search(ElementType Data[],int begin,int end,ElementType X)
{
	if(begin>end) return begin;
	int mid=(begin+end)/2;
	if(Data[mid]==X)
		return -1;
	else if(Data[mid]>X)
		return Search(Data,mid+1,end,X);	
	else 
		return Search(Data,begin,mid-1,X);	
}

bool Insert(List L, ElementType X)
{
	int j;
	if(L->Last==MAXSIZE-1) return false;
	if((j=Search(L->Data,0,L->Last,X))==-1)
		return false;
	else
	{
		for(int i=L->Last;i>=j;i--)
		{
			L->Data[i+1]=L->Data[i];
		}
		L->Data[j]=X;
		L->Last++;
		return true;
	}
}
*/
