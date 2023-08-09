#include <iostream>
using namespace std;
class A{
public:
    A(){cout<<"--construct A--"<<endl;}
    ~A(){cout<<"--destory A--"<<endl;}
private:
    int a;
};

class B:public A
{

};

int main()
{
    A arr[10];
    return 0;
}