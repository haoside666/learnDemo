#include <iostream>
using namespace std;
//指针与引用
double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};
 
double& setValues(int i) {  
   double& ref = vals[i];    
   return ref;   // 返回第 i 个元素的引用，ref 是一个引用变量，ref 引用 vals[i]
}
void test1()
{
    int a = 10;
    int &b = a;
    int *p = &a;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "p=" << p << endl;
    cout << "*p=" << *p << endl;
    b = 2;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "p=" << p << endl;
    cout << "*p=" << *p << endl;
}

void test2()
{
    cout << "改变前的值" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }

    setValues(1) = 20.23; // 改变第 2 个元素
    setValues(3) = 70.8;  // 改变第 4 个元素

    cout << "改变后的值" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }
}

void test3()
{
    int i=10;
    int& ref=i;
    ref++;
    cout<<"i="<<i<<endl;
    cout<<"ref="<<ref<<endl;
    int j=20;
    ref=j;
    ref++;
    cout<<"i="<<i<<endl;
    cout<<"ref="<<ref<<endl;
    cout<<"j="<<j<<endl;
}
int main(int argc, char **argv)
{
    test3();
    return 0;
}