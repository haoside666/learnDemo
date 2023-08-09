#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAXSIZE 100001

int main(int argc,char*argv[])
{
	int N,len,start,max=-1,maxbegin;
	int i;
	int arr[MAXSIZE];
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&arr[i]);
	}
	arr[N]=INT_MIN;
	i=0,len=1;
	while(i<N)
	{
		start=i;
		if(arr[i+1]>arr[i])
		{
			while(arr[i+1]>arr[i])
			{
				i++;
				len++;
			}			
		}else
		{
			i++;
		}
		if(len>max)
		{
			max=len;
			maxbegin=start;
		}
		len=1;
	}
	int end=maxbegin+max-1;
	for(int i=maxbegin;i<end;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("%d",arr[end]);
	return 0;
}
/*
#include<stdio.h>
#define For(i,a,b) for(i=a;i<=b;i++)
#define max(a,b) a>b?a:b;
int main()
{
    int n,i;
    int nums[100005];
    scanf("%d",&n);
    For(i,0,n-1)scanf("%d",&nums[i]);
    int l=1,start=0,tmp=1;
    for(int i=1;i<n;i++)
    {
        if(nums[i]>nums[i-1])tmp++;
        else
        {
            if(tmp>l)
            {
                start=i-tmp;
                l=tmp;
            }
            tmp=1;
        }
    }
    if(tmp>l)
    {
        start=i-tmp;
        l=tmp;
    }

    For(i,start,start+l-1)
    {
        char c;
        if(i==start+l-1)c='\n';
        else c=' ';
        printf("%d%c",nums[i],c);
    }
    return 0;
}
*/
