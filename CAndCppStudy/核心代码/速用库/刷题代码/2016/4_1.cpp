#include <iostream>
using namespace std;

int M(int x)
{
    int y;
    if(x>100) return x-10;
    else{
        y=M(x+11);
        return (M(y));
    }
}


int main()
{
    for(int i=0;i<200;i++)
    {
        cout<<M(i)<<"  ";
        if((i+1)%10==0) cout<<endl;
    }
    return 0;
}