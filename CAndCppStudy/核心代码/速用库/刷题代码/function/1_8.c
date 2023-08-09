#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);
	if(L!=NULL)
		free(L);
    return 0;
}
List ReadInput()
{
	List L;
	int N;
	L=(List)malloc(sizeof(struct LNode));
	L->Last=0;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&L->Data[++L->Last]);
	}
	return L;
}

Position BinarySearch(List L,ElementType X)
{
    int begin=1;
    int end=L->Last;
    int mid;
    while(begin<=end)
    {
        mid=(begin+end)/2;
        if(L->Data[mid]==X)
            return mid;
        else if(L->Data[mid]<X)
            begin=mid+1;	
        else 
		    end=mid-1;	
    }
	return NotFound;
}

/*
Position Search(ElementType Data[],int begin,int end,ElementType X)
{
	if(begin>end) return NotFound;
	int mid=(begin+end)/2;
	if(Data[mid]==X)
		return mid;
	else if(Data[mid]<X)
		return Search(Data,mid+1,end,X);	
	else 
		return Search(Data,begin,mid-1,X);	
}

Position BinarySearch(List L,ElementType X)
{
	return Search(L->Data,1,L->Last,X);
}
*/
