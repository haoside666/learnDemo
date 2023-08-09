#include <iostream>
using namespace std;

enum color{red,green,blue,black};

void printColor(color c)
{
    switch(c)
    {
        case 0:
            cout<<"red"<<endl;
            break;
        case 1:
            cout<<"green"<<endl;
            break;
        case 2:
            cout<<"blue"<<endl;
            break;
        case 3:
            cout<<"black"<<endl;
            break;
    }
}
int main(int argc,char **argv)
{
    color c=green;
    printColor(c);
    return 0;
}