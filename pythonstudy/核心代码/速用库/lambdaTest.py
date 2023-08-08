

#lambda 表达式
def fun():
    # 可写函数说明
    sum = lambda arg1, arg2: arg1 + arg2
    # 调用sum函数
    print("相加后的值为 : ", sum(10, 20))
    print("相加后的值为 : ", sum(20, 20))


def myfunc(n):
    return lambda a: a * n

def fun2():
    mydoubler = myfunc(2)
    mytripler = myfunc(3)
    print(mydoubler(11))
    print(mytripler(11))

if __name__ == "__main__":
    print("------------------------------fun1------------------------------")
    fun1()
    print("------------------------------fun2------------------------------")
    fun2()
