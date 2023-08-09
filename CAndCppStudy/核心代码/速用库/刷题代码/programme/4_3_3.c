#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 1000
int arr[MAXSIZE],T[MAXSIZE];
int compare(const void*a, const void*b);
int GetLeftLength(int n);
void solve( int ALeft, int ARight, int TRoot);
int main(int argc,char *argv[])
{
    int N;
	scanf("%d",&N);    
    for(int i=0;i<N;i++)
    {
        scanf("%d",&arr[i]);
    }
    qsort(arr,N,sizeof(int),compare);
    solve(0,N-1,0);
    for(int i=0;i<N;i++)
    {
        printf("%d%c",T[i],i==N-1?'\n':' ');
    }
    return 0;
}
int compare(const void*a, const void*b)
{
    return *(int*)a-*(int*)b;
}
int GetLeftLength(int n)
{
    int H,X,L;
    H = (int)(floor(log(n+1)/log(2)));
    X=n-pow(2,H)+1;
	X=X>pow(2,H-1)?pow(2,H-1):X;
    L=X+pow(2,H-1)-1;
    return L;
}
void solve( int ALeft, int ARight, int TRoot)
{  
    int n,L,LeftTRoot,RightTRoot;
    n = ARight-ALeft+1;
    if (n==0) return;
    L = GetLeftLength(n); /* 计算出n个结点的树其左子树有多少个结点 */
    T[TRoot] = arr[ALeft + L];
    LeftTRoot = TRoot * 2 + 1;
    RightTRoot = LeftTRoot + 1;
    solve(ALeft, ALeft+L-1, LeftTRoot);
    solve(ALeft+L+1, ARight, RightTRoot);
}
