/*
本题要求实现一个对数组进行循环左移的简单函数：一个数组a中存有n（>0）个整数，在不允许使用另外数组的前提下，将每个整数循环向左移m（≥0）个位置，即将a中的数据由（a0a1⋯a​n−1变换为（am⋯an−1a0a1⋯am−1）（最前面的m个数循环移至最后面的m个位置）
*/

#include <stdio.h>
#define MAX 100

int main(int argc,char *argv[])
{
	int arr[MAX];
	int n,m,i,k;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	k=m%n;
	for(i=k;i<n+k-1;i++)
	{
		printf("%d ",arr[i%n]);
	}
	printf("%d",arr[i%n]);
	return 0;
}

/*
#include <stdio.h>

void change(int arr[],int len,int m);
#define MAX 200
int main(int argc,char *argv[])
{
	int arr[MAX];
	int n,m,i,k;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	k=m%n;
	if(k!=0)
		change(arr,n,k);
	for(i=0;i<n-1;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("%d",arr[n-1]);
	return 0;
}

void change(int arr[],int len,int m)
{
	for(int i=0;i<m;i++)
	{
		arr[100+i]=arr[i];
	}
	for(int i=m;i<len;i++)
	{
		arr[i-m]=arr[i];
	}
	for(int i=len-m;i<len;i++)
	{
		arr[i]=arr[i-(len-m)+100];
	}
}
*/
