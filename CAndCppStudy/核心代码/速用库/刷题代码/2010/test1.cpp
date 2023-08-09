#include <iostream>

using namespace std;
/*
    一个一维整数数组A[m]中有n个非空整数，他们相继存放与数组的前端并已按非递减的顺序排序，请针对下列两种情况，分别编写相应的函数
    1.在数组A[]中插入整数x,插入后的数组仍保持非递减有序，若有与x值相等的元素，则x插在该元素后面
            void Insert(int A[],int m,int n,int x)
    2.利用原数组空间将数组中的元素全部反转，形成数组中元素按非递增的顺序排列
            void reverse(int A[],int n)
*/
#define M 10

void Insert(int A[],int m,int n,int x)
{
    if(n==m)
    {
        cout<<"insert fail"<<endl;
        return;
    }
    for(int i=n-1;i>=0;i--)
    {
        if(x>=A[i])
        {
            A[i+1]=x;
            return;
        }
        A[i+1]=A[i];
    }
    A[0]=x;
}

void reverse(int A[],int n)
{
    int revindex,temp;
    for(int i=0;i<n/2;i++)
    {
        revindex=n-1-i;
        temp=A[i];
        A[i]=A[revindex];
        A[revindex]=temp;
    }

}
void print(int A[],int size){
    cout<<"数组的元素为:"<<endl;
    for(int i=0;i<size;i++)
        cout<<A[i]<<" ";
    cout<<endl;
}
int main()
{
    int A[]={2,4,6,8,10};
    // print(A,5);
    Insert(A,M,5,4);
    // print(A,6);
    Insert(A,M,6,3);
    // print(A,7);
    Insert(A,M,7,5);
    // print(A,8);
    Insert(A,M,8,11);
    // print(A,9);
    Insert(A,M,9,2);
    Insert(A,M,10,2);
    print(A,10);
    reverse(A,10);
    print(A,10);
    return 0;
}