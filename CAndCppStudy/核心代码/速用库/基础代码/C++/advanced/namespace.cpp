#include <iostream>
using namespace std;
 
#include <iostream>
using namespace std;
namespace A
{
    int a = 100;
    namespace B            //嵌套一个命名空间B
    {
        int a =20;
    }
}

int a = 200;//定义一个全局变量


int main(int argc, char *argv[])
{
    cout <<"A::a ="<< A::a << endl;
    cout <<"A::B::a ="<<A::B::a << endl;
    cout <<"a ="<<a << endl;
    cout <<"::a ="<<::a << endl;//全局变量a

    int a = 30;
    cout <<"a ="<<a << endl;   //局部变量a
    cout <<"::a ="<<::a << endl;

    return 0;
}

// // 第一个命名空间
// namespace first_space{
//    void func(){
//       cout << "Inside first_space" << endl;
//    }
//    // 第二个命名空间
//    namespace second_space{
//       void func(){
//          cout << "Inside second_space" << endl;
//       }
//    }
// }
// using namespace first_space::second_space;
// int main ()
// {
//    first_space::func();
//    // 调用第二个命名空间中的函数
//    func();
//    return 0;
// }