#include <iostream>
using namespace std;
int main(int argc,char **argv)
{
    cout<<"hello world"<<endl;
    cout<<hex<<(0xf700&0x1301)<<endl;//按位与
    return 0;
}