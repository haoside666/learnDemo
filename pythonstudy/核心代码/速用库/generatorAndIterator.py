import sys  # 引入 sys 模块

class MyNumbers:
    def __iter__(self):
        self.a = 1
        return self

    def __next__(self):
        x = self.a
        self.a += 1
        return x


class MyNumbers2:
    def __iter__(self):
        self.a = 1
        return self

    def __next__(self):
        if self.a <= 20:
            x = self.a
            self.a += 1
            return x
        else:
            raise StopIteration

#迭代器有两个基本的方法：iter() 和 next()
def fun1():
    list = [1, 2, 3, 4]
    it = iter(list)  # 创建迭代器对象
    while True:
        try:
            print(next(it))
        except StopIteration:
            sys.exit()

def fun2():
    myclass = MyNumbers()
    myiter = iter(myclass)

    print(next(myiter))
    print(next(myiter))
    print(next(myiter))
    print(next(myiter))
    print(next(myiter))

# StopIteration 异常用于标识迭代的完成，防止出现无限循环的情况，在 __next__() 方法中我们可以设置在完成指定循环次数后触发 StopIteration 异常来结束迭代。
def fun3():
    myclass = MyNumbers2()
    myiter = iter(myclass)
    for x in myiter:
        print(x)
"""
在 Python 中，使用了 yield 的函数被称为生成器（generator）。
跟普通函数不同的是，生成器是一个返回迭代器的函数，只能用于迭代操作，更简单点理解生成器就是一个迭代器。
在调用生成器运行的过程中，每次遇到 yield 时函数会暂停并保存当前所有的运行信息，返回 yield 的值, 并在下一次执行 next() 方法时从当前位置继续运行。
调用一个生成器函数，返回的是一个迭代器对象。
"""


def fibonacci(n):  # 生成器函数 - 斐波那契
    a, b, counter = 0, 1, 0
    while True:
        if (counter > n):
            return
        yield a
        a, b = b, a + b
        counter += 1

def fun4():
    f = fibonacci(10)  # f 是一个迭代器，由生成器返回生成
    while True:
        try:
            print(next(f), end=" ")
        except StopIteration:
            sys.exit()

if __name__ == "__main__":
    # print("------------------------------fun1------------------------------")
    # fun1()
    print("------------------------------fun2------------------------------")
    fun2()
    print("------------------------------fun3------------------------------")
    fun3()
    print("------------------------------fun4------------------------------")
    fun4()
