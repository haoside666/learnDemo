#include <iostream>
using namespace std;

void fun();
int main()
{
//    int a = 21;
//    int b = 10;
//    int c;
//    c = a + b;
//    cout << "Line 1 - c 的值是 " << c << endl ;
//    c = a - b;
//    cout << "Line 2 - c 的值是 " << c << endl ;
//    c = a * b;
//    cout << "Line 3 - c 的值是 " << c << endl ;
//    c = a / b;
//    cout << "Line 4 - c 的值是 " << c << endl ;
//    c = a % b;
//    cout << "Line 5 - c 的值是 " << c << endl ;
//    int d = 10;   //  测试自增、自减
//    c = d++;
//    cout << "Line 6 - c 的值是 " << c << endl ;
//    d = 10;    // 重新赋值
//    c = d--;
//    cout << "Line 7 - c 的值是 " << c << endl ;
    fun();
    int a=(3,4,5);
    cout<<"a="<<a<<endl;
   return 0;
}

void fun()
{
   unsigned int a = 60;      // 60 = 0011 1100  
   unsigned int b = 13;      // 13 = 0000 1101
   int c = 0;           
 
   c = a & b;             // 12 = 0000 1100
   cout << "Line 1 - c 的值是 " << c << endl ;
 
   c = a | b;             // 61 = 0011 1101
   cout << "Line 2 - c 的值是 " << c << endl ;
 
   c = a ^ b;             // 49 = 0011 0001
   cout << "Line 3 - c 的值是 " << c << endl ;
 
   c = ~a;                // -61 = 1100 0011
   cout << "Line 4 - c 的值是 " << c << endl ;
 
   c = a << 2;            // 240 = 1111 0000
   cout << "Line 5 - c 的值是 " << c << endl ;
 
   c = a >> 2;            // 15 = 0000 1111
   cout << "Line 6 - c 的值是 " << c << endl ;
}