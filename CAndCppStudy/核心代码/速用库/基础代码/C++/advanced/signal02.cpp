#include <iostream>
#include <csignal>

#ifdef __WINDDOWS__
#include <windows.h>  //windows以毫秒为单位
#else
#include <unistd.h> //sleep函数头文件 linux 系统 以秒为单位
#endif
using namespace std;

void signalHandler(int signum)
{
    static int time = 2;
    if(time==0)
        exit(signum);
    cout << "Interrupt signal (" << signum << ") received.\n";
    cout << time-- << endl;
    // 清理并关闭
    // 终止程序

}

int main()
{
    int i = 0;
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);

    while (++i)
    {
        cout << "Going to sleep...." << endl;
        if (i%3==0)
        {
            raise(SIGINT);
        }
        sleep(1);
    }

    return 0;
}