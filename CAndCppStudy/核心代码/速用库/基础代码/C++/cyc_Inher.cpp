#include <iostream>
/*
    环状继之虚继承
*/
using namespace std;
//基类

class D
{
public:
    D(){cout<<"D()"<<endl;}
    ~D(){cout<<"~D()"<<endl;}
protected:
    int d;
};

class B:virtual public D
{
public:
    B(){cout<<"B()"<<endl;}
    ~B(){cout<<"~B()"<<endl;}
protected:
    int b;
};

class A:virtual public D
{
public:
    A(){cout<<"A()"<<endl;}
    ~A(){cout<<"~A()"<<endl;}
protected:
    int a;
};

class C:public B, public A
{
public:
    C(){cout<<"C()"<<endl;}
    ~C(){cout<<"~C()"<<endl;}
protected:
    int c;
};

int main()
{
    D d;
    cout<<endl;
    B b;
    cout<<endl;
    A a;
    cout<<endl;
    C c;   //D, B, A ,C
    cout<<endl;
    cout << "Hello World!" << endl;
    cout<<"sizeof(int):"<<sizeof(int)<<endl;//4
    cout<<"sizeof(d):"<<sizeof(d)<<endl;//4
    cout<<"sizeof(b):"<<sizeof(b)<<endl;//4+4+8
    cout<<"sizeof(a):"<<sizeof(a)<<endl;//4+4+8
    cout<<"sizeof(c):"<<sizeof(c)<<endl;//4+4+8+4+8+4+8   //三个虚指针
    return 0;
}