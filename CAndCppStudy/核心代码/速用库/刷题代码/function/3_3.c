#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 20
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标0开始存储 */
void PrintList( List L ); /* 裁判实现，细节不表 */
List Delete( List L, ElementType minD, ElementType maxD );

int main()
{
    List L;
    ElementType minD, maxD;
    int i;

    L = ReadInput();
    scanf("%d %d", &minD, &maxD);
    L = Delete( L, minD, maxD );
    PrintList( L );

    return 0;
}
List ReadInput()
{
	List L=(List)malloc(sizeof(struct LNode));
	L->Last=-1;
	int N,number;
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
/*
List Delete(List L, ElementType minD, ElementType maxD )
{
    int i,j;
    for(i=0;i<=L->Last;i++)
    {
        if(L->Data[i]>minD&&L->Data[i]<maxD)
        {
            for(j=i;j<L->Last;j++)
            {
                L->Data[j]=L->Data[j+1];
            }
			L->Last--;
			i--;
        }
    }
    return L;
}
*/
List Delete(List L, ElementType minD, ElementType maxD )
{
    int i,j,k=0,m;
	int arr[MAXSIZE];
	int last=-1,flags;
	memset(arr,0,MAXSIZE);
	//标记所有要删除的位置
    for(i=L->Last;i>=0;i--)
    {
        if(L->Data[i]>minD&&L->Data[i]<maxD)
        {
			arr[++last]=i;
        }
    }
	//k表示要删除元素的个数
	L->Last-=(1+last);
	k=last+1;

	//m表示第一个要删除元素的位置
	m=arr[last];
	for(i=0;i<k;i++)
	{
		flags=last;
		for(j=arr[last];j==arr[flags];j++,flags--);
		L->Data[m++]=L->Data[j];
		while(1)
		{
			if(j<arr[last]||last==-1)
			{
				arr[++last]=j;
				break;
			}			
			else
			{
				last--;
			}
		}
	}
	
    return L;
}
