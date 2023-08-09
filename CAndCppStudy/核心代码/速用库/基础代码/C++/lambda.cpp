#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;
    auto c = [=]() -> int
    {
        return a + b;
    };
    cout << c() << endl;
    int d = 5;

    cout<<"按引用捕获变量"<<endl;
    cout << "d=" << d << endl;
    auto f = [&]()
    { return d *= 5; }; //取消常量性
    cout << f() << endl;
    cout << "d=" << d << endl;

    cout<<"按值捕获变量(mutable)"<<endl;
    int e = 5;
    cout << "e=" << e << endl;
    auto f1 = [e]() mutable
    { return e *= 5; }; //取消常量性
    cout << f1() << endl;
    cout << "e=" << e << endl;

    return 0;
}
