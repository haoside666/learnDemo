#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//冒泡排序
void BobSort(vector<int> &v)
{
    int temp;
    bool flags;
    for(int i=0;i<v.size()-1;i++)
    {
        flags=true;
        for(int j=0;j<v.size()-1-i;j++)
        {
            if(v[j]>v[j+1])
            {
                temp=v[j];
                v[j]=v[j+1];
                v[j+1]=temp;
                flags=false;
            }
        }
        if(flags) return;
    }
}

//插入排序
void InsertSort(vector<int> &v)
{
    int temp,j;
    for(int i=1;i<v.size();i++)
    {
        temp=v[i];
        j=i;
        while(j>0&&v[j-1]>temp)
        {
            v[j]=v[j-1];
            j--;
        }
        v[j]=temp;
    }
}

//选择排序
void SelectSort(vector<int>&v)
{
	for (int i = 0; i < v.size(); i++)
	{
		int min = i;
		for (int j = i + 1; j < v.size(); ++j)
		{
			if (v[min] > v[j])
			{
				min = j;
			}
		}
		swap(v[min], v[i]);
	}
}

/*归并算法
	left 左边下标
	mid 拆分的中间点
	right 右边下标
*/ 
void myMerge(vector<int>& v, int left, int mid, int right)
{
	vector<int>t(v.begin()+left,v.begin()+right+1);
	int lk = left,rk = mid+1;
	for (int i=left;i<=right;i++)
	{
		if (lk>mid)  //说明前一组已并入
		{
			v[i] = t[rk - left];
			rk++;
		}
		else if(rk> right) //说明后一组已并入
		{
			v[i] = t[lk - left];
			lk++;
		}
		else if (t[lk-left]<t[rk-left]) //升序排序 小的在前
		{
			v[i] = t[lk-left];
			lk++;
		}
		else  
		{
			v[i] = t[rk-left];
			rk++; 
		}
	}
}
/*分解数组
 *left 左边下标
 *right 右边下标
*/
void resolve(vector<int>& v, int left, int right)
{
	if (left < right)
	{
		int mid = (left+right)/2;  //取中间下标
		resolve(v, left, mid);
		resolve(v, mid + 1, right);
		myMerge(v, left, mid, right);
	}
}

void mergeSort(vector<int>& v)
{
	resolve(v,0, v.size() - 1);
}

//快速排序
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


/*
    基数排序
    n表示进行n趟基数排序
*/
void XSort(vector<int>& v,int n)
{
    queue<int> b[10];
    int i,j;
    int k=1,index,num;
    for(i=0;i<n;i++)
    {
        for(j=0;j<v.size();j++)
        {
            num=v[j]/k%10;
            b[num].push(v[j]);
        }
        index=0;
        for(j=0;j<10;j++)
        {
            while(!b[j].empty())
            {
                v[index++]=b[j].front();
                b[j].pop();
            }
        }
        k*=10;
    }
}


ostream& operator<<(ostream &os,const vector<int>&v)
{
    for(int i=0;i<v.size();i++)
    {
        os<<v[i]<<" ";
    }
    os<<endl;
    return os;
}
int main(int argc,char*argv[])
{
    vector<int> v1={9,8,7,6,5,4,3,2,1};
    vector<int> v2={29,38,7,126,235,1094,2333,212,9};
    vector<int> v(v1);
    cout<<v;
    BobSort(v);
    cout<<v;
    v=v1;
    InsertSort(v);
    cout<<v;

    v=v1;
    SelectSort(v);
    cout<<v;

    v=v1;
    mergeSort(v);
    cout<<v;

    v=v1;
    QuickSort(v,0,v.size()-1);
    cout<<v;

    v=v2;
    QuickSort(v,0,v.size()-1);
    cout<<v;

    v=v2;
    XSort(v,4);
    cout<<v;
    return 0;
}