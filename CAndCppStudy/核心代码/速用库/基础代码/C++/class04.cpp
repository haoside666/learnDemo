#include <iostream>
using namespace std;
/*
    类的友元与内联函数

    友元函数的使用
    因为友元函数没有this指针，则参数要有三种情况： 
        要访问非static成员时，需要对象做参数；
        要访问static成员或全局变量时，则不需要对象做参数；
        如果做参数的对象是全局对象，则不需要对象做参数.
        可以直接调用友元函数，不需要通过对象或指针
*/
//类声明
class Box;
class Box2;

//类定义
class Box
{
protected:
    double width;

public:
    friend void print(Box box,Box2 Box2);
    friend void printWidth(Box box);
    friend class Box3;
    void setWidth(double wid) { width = wid; };
};
class Box2
{
protected:
    double width2;

public:
    friend void print(Box box,Box2 Box2);
    friend void printWidth(Box2 Box2);
    void setWidth(double wid) { width2 = wid; };
};

class Box3{
public:
    void printBoxWidth(Box& box){cout << "Width of box(in box3) : " << box.width << endl;};
};
// 请注意：printWidth() 不是任何类的成员函数
void printWidth(Box box)
{
    cout<<"printWidth(Box)"<<endl;
    /* 因为 printWidth() 是 Box 的友元，它可以直接访问该类的任何成员 */
    cout << "Width of box : " << box.width << endl;
}
void printWidth(Box2 box2)
{
    cout<<"printWidth(Box2)"<<endl;
    /* 因为 printWidth() 是 Box 的友元，它可以直接访问该类的任何成员 */
    cout << "Width2 of box2 : " << box2.width2 << endl;
}
void print(Box box,Box2 box2)
{
    cout<<"print"<<endl;
    cout << "Width of box : " << box.width << endl;
    cout << "Width2 of box2 : " << box2.width2 << endl;
}

// 程序的主函数
int main()
{
    Box box;
    Box2 box2;
    Box3 box3;
    // 使用成员函数设置宽度
    box.setWidth(10.0);
    box2.setWidth(20.0);
    // 使用友元函数输出宽度
    printWidth(box);
    printWidth(box2);
    print(box,box2);
    box3.printBoxWidth(box);
    return 0;
}