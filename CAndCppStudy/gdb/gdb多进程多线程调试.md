gdb安装

git clone https://github.com/gatieme/GdbPlugins.git ~/GdbPlugins  从git上面下载一些插件

对应启动命令：
echo "source ~/GdbPlugins/peda/peda.py" > ~/.gdbinit 
echo "source ~/GdbPlugins/gef/gef.py" > ~/.gdbinit 
echo "source ~/GdbPlugins/gdbinit/gdbinit" > ~/.gdbinit  



有问题重新安装一下gdb(记得换源)

## 多进程调试

1.确定gdb中进程跟踪模式

show follow-fork-mode  决定跟那个进程

show detach-on-fork 



set follow-fork-mode parent跟父进程

set follow-fork-mode child跟子进程

set detach-on-fork on 分离

set detach-on-fork off 不分离

2.进程间的切换

info inferiors

inferiors num



## 多线程编程

gcc -g -o thread thread.c -lpthread



b thread1 直接b到该线程里面去



set scheduler-locking off|on

off 不锁定任何线程

on锁定其他线程,只有当前线程执行

2.线程间的切换

info threads

thread num