#include<iostream>
#include <queue>
using namespace std;
//函数声明
void test1();
void test2();
//方法1
struct tmp1 //运算符重载<
{
    int x;
    tmp1(int a) {x = a;}
    bool operator<(const tmp1& a) const
    {
        return x < a.x; //大顶堆
    }
};

//方法2
struct tmp2 //重写仿函数
{
    bool operator() (tmp1 a, tmp1 b) 
    {
        return a.x < b.x; //大顶堆  升序
    }
};
bool compare(tmp1 a, tmp1 b) 
{
    return a.x < b.x; //大顶堆
}

class smallComparater03{
public:
	bool operator()(int o1,int o2){
		return o1<o2;
	}
};

int lessMoney(int arr[],int sz)
{
	priority_queue<int,vector<int>,smallComparater03 > q;
    int currentSum=0;
	for(int i=0;i<sz;i++)
    {
        currentSum+=arr[i];
		q.push(arr[i]);
    }
	int sum=0,cur=0;
	do{
        sum+=currentSum;
		cur=q.top(); 
		q.pop();
		currentSum=currentSum-cur;
	}while(q.size()!=1);
	return sum;
}

int main() 
{
    int arr[]={10,20,30,40};
    cout<<lessMoney(arr,4);
}


void test1()
{
    //对于基础类型 默认是大顶堆
    priority_queue<int> a; 
    //等同于 priority_queue<int, vector<int>, less<int> > a;
    
  
    priority_queue<int, vector<int>, greater<int> > c;  //这样就是小顶堆   降序小顶堆 升序大顶堆
    priority_queue<string> b;

    for (int i = 0; i < 5; i++) 
    {
        a.push(i);
        c.push(i);
    }
    while (!a.empty()) 
    {
        cout << a.top() << ' ';
        a.pop();
    } 
    cout << endl;

    while (!c.empty()) 
    {
        cout << c.top() << ' ';
        c.pop();
    }
    cout << endl;

    b.push("abc");
    b.push("abcd");
    b.push("cbd");
    while (!b.empty()) 
    {
        cout << b.top() << ' ';
        b.pop();
    } 
    cout << endl;
}

void test2()
{
    test1();
    cout<<"-------------------------------------------------"<<endl;
    tmp1 a(1);
    tmp1 b(2);
    tmp1 c(3);
    priority_queue<tmp1> d;
    d.push(b);
    d.push(c);
    d.push(a);
    while (!d.empty()) 
    {
        cout << d.top().x << '\n';
        d.pop();
    }
    cout << endl;

    priority_queue<tmp1, vector<tmp1>, tmp2 > f;
    f.push(c);
    f.push(b);
    f.push(a);
    while (!f.empty()) 
    {
        cout << f.top().x << '\n';
        f.pop();
    }
}