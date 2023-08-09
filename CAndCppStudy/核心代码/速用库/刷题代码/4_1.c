#include <stdio.h>
#define MAXSIZE 30
int arr[MAXSIZE],brr[MAXSIZE],crr[MAXSIZE];
void solve(int pre_index,int in_index,int post_index,int len);
int main(int argc,char *argv[])
{ 
    int N;
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        scanf("%d",&crr[i]);
    }
    for(int i=0;i<N;i++)
    {
        scanf("%d",&brr[i]);
    }
    solve(0,0,0,N);
    printf("Preorder:");
    for(int i=0;i<N;i++)
    {
        printf(" %d",arr[i]);
    }
    return 0;
}
/*
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7

Preorder: 4 1 3 2 6 5 7
*/
//0 0 0 7
//1 0 0 3
//2 0 0 1
void solve(int pre_index,int in_index,int post_index,int len)
{
    if(len==0) return;
    if(len==1)
    {
        arr[pre_index]=crr[post_index];
        return;
    }
    int odd,i;
    arr[pre_index]=crr[post_index+len-1];
    for(i=0;i<len;i++)
    {
        if(brr[i+in_index]==arr[pre_index]) break;
    }
    odd=len-i-1;
    solve(pre_index+1,in_index,post_index,i);
    solve(pre_index+1+i,in_index+1+i,post_index+i,odd);
}
