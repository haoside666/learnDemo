#include <iostream>
using namespace std;
int main()
{
    int a=20,b=30;
    const int *p=&a;
    cout<<"---------------------const int *p----------------------"<<endl;
    cout<<"*p="<<*p<<endl;
    cout<<hex<<"p="<<p<<endl;

    p=&b;
    cout<<dec<<"*p="<<*p<<endl;
    cout<<hex<<"p="<<p<<endl;

    const int * const q=&a; 
    cout<<"---------------------const int * const p------------------W"<<endl;

    return 0;
}