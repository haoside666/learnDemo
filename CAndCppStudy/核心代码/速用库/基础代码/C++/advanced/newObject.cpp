#include <iostream>
using namespace std;

class Box
{
public:
    Box():id(++num)
    {
        cout << "调用构造函数"<<id<<endl<<endl;
    }
    ~Box()
    {
        cout << "调用析构函数"<<id<<endl<<endl;
    }

public:
    static int num;
    int id;
};

int Box::num=0;

int main()
{
    Box *myBoxArray = new Box[4];

    delete[] myBoxArray; // 删除数组
    return 0;
}