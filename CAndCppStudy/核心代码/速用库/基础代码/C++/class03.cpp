#include <iostream>
using namespace std;
/*
    类的构造,析构,拷贝构造函数
*/

class A{
public:
    A(){cout<<"无参构造函数"<<endl;}
    A(int data):id(cnt++),data(data){cout<<"有参构造函数"<<endl;}
    A(const A& other):id(cnt++),data(other.data){cout<<"拷贝构造函数"<<endl;}
    ~A(){cout<<"A被析构了,id为"<<id<<endl;}
    int getData(){return data;}
    int getid(){return id;};
    static int cnt;
private:
    int data;
    int id;
};
int A::cnt=1;
int main(int argc,char *argv[])
{
    A a(222);
    A a1(a);
    cout<<"id:"<<a.getid()<<",data:"<<a.getData()<<endl;
    cout<<"id:"<<a1.getid()<<",data:"<<a1.getData()<<endl;
    return 0;
}