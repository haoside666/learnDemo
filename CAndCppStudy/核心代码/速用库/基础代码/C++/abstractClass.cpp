#include <iostream>

using namespace std;

// 基类
class Shape
{
public:
    // 提供接口框架的纯虚函数
    virtual int getArea() = 0;
    void setWidth(int w)
    {
        width = w;
    }
    void setHeight(int h)
    {
        height = h;
    }

protected:
    int width;
    int height;
};

// 派生类
class Rectangle : public Shape
{
public:
    int getArea()
    {
        return (width * height);
    }
};
class Triangle : public Shape
{
public:
    int getArea()
    {
        return (width * height) / 2;
    }
};

int main(void)
{
    Shape* rect=new Rectangle;
    Shape* Tri=new Triangle;
    rect->setWidth(5);
    rect->setHeight(7);
    // 输出对象的面积
    cout << "Total Rectangle area: " << rect->getArea() << endl;

    Tri->setWidth(5);
    Tri->setHeight(7);
    // 输出对象的面积
    cout << "Total Triangle area: " << Tri->getArea() << endl;
    delete rect;
    delete Tri;

    return 0;
}