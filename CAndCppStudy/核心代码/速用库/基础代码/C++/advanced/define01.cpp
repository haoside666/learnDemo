#include <iostream>
using namespace std;


#ifndef __OK__
    #define __OK__
    void ok()
    {
        cout<<"i am ok now"<<endl;
    }
#elif
    void ok()
    {
        cout<<"i am ok"<<endl;
    } 
#endif
#define MKSTR( x ) #x
#define concat(a, b) a##b 
 
int main ()
{
    ok();
    cout << MKSTR(HELLO C++) << endl;   //等价于"cout<<HELLO C++"<<endl;
    int xy=20;
    cout<<concat(x,y)<<endl;   //等价于cout<<xy<<endl;

    cout << "Value of __LINE__ : " << __LINE__ << endl;
    cout << "Value of __FILE__ : " << __FILE__ << endl;
    cout << "Value of __DATE__ : " << __DATE__ << endl;
    cout << "Value of __TIME__ : " << __TIME__ << endl;
    return 0;
}