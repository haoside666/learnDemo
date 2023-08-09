#include <iostream>
#include <vector>
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
	cout << "选择排序:";
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
		if (lk>mid)
		{
			v[i] = t[rk - left];
			rk++;
		}
		else if(rk> right)
		{
			v[i] = t[lk - left];
			lk++;
		}
		else if (t[lk-left]<t[rk-left])  //两组元素进行比较
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
	cout << "归并排序";
	resolve(v,0, v.size() - 1);
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
    return 0;
}