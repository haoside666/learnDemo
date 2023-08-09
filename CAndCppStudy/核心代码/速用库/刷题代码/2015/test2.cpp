#include <iostream>
#include <vector>
using namespace std;



void QuickSort(vector<int> &v,int low,int high)
{
    if(low<high){
        int i=low,j=high;
        int pivot = v[low];    //将第一个元素作为枢轴
        //接下来进行第一次partition
        while(i<j){
            while(i<j && v[j]>=pivot)    //从右往左找到第一个小于枢轴的数
                j--;
            if(i<j){    //将该数移动到左指针的位置
                v[i] = v[j];
                i++;
            }
            while(i<j && v[i]<pivot)    //从左往右找到第一个大于等于枢轴的数
                i++;
            if(i<j){    //将该数移动到右指针的位置
                v[j] = v[i];
                j--;
            }
        }
        v[i] = pivot;    //循环退出时i == j即枢轴的位置
        //递归处理当前枢轴的左右两部分
        QuickSort(v,low,i-1);    
        QuickSort(v,i+1,high);
    }
}

int main()
{
    vector<int> v={1,2,3,2,1,3,2,1,3,2,3,2};
    QuickSort(v,0,v.size()-1);
    for(int i=0;i<v.size();i++)
    {
        cout<<v[i]<<"  ";
    }
    cout<<endl;
    return 0;
}

// void sortNum(int A[],int len)
// {
//     int num1,num2,num3;
//     num1=num2=num3=0;
//     for(int i=0;i<len;i++)
//     {
//         if(A[i]==1) num1++;
//         else if(A[i]==2) num2++;
//         else num3++;
//     }
//     for(int i=0;i<len;i++){
//         if(i<num1)
//             A[i]=1;
//         else if(i<num1+num2)
//             A[i]=2;
//         else
//             A[i]=3;
//     } 
// }