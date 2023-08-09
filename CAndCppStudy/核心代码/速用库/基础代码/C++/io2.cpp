#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[])
{
    //showbase
    int data = 0xffff;
    cout << hex << showbase << data << endl;   //输出0xffff
    cout << hex << noshowbase << data << endl; //输出ffff
    //showpoint
    double a = 30;
    double b = 10000.0;
    double pi = 3.1416;
    std::cout.precision(5);
    std::cout << std::showpoint << a << '\t' << b << '\t' << pi << endl;
    std::cout << std::noshowpoint << a << '\t' << b << '\t' << pi << endl; //未设置时，仅对小数部分不为零的数字写入小数点
    //showpos
    /*When the showpos format flag is set,a plus sign (+) precedes every 
        non-negative numerical value inserted into the stream (including zeros).*/
    cout<<dec;
    int p = 1;
    int z = 0;
    int n = -1;
    std::cout << std::showpos << p << '\t' << z << '\t' << n << endl;//+1 0 -1
    std::cout << std::noshowpos << p << '\t' << z << '\t' << n << endl;//
    return 0;
}