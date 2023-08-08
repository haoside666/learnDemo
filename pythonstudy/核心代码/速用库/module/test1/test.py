# 导入模块
import support
import sys

def fun1():
    # 现在可以调用模块里包含的函数了
    support.print_func("Runoob")

def fun2():
    print(sys.path)
    print(dir(support))
    print(dir("./"))

if __name__=="__main__":
    print("------------------------------fun1------------------------------")
    fun1()
    print("------------------------------fun2------------------------------")
    fun2()