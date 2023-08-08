class MyClass:
    """一个简单的类实例"""
    i = 12345

    def f(self):
        return 'hello world'

# self代表类的实例，而非类
class Complex:
    def __init__(self, realpart, imagpart):
        self.r = realpart
        self.i = imagpart
    # self 代表的是类的实例，代表当前对象的地址
    # 类方法必须包含参数 self, 且为第一个参数
    def prt(self):
        print(self)
        print(self.__class__)

def test1():
    # 实例化类
    x = MyClass()
    # 访问类的属性和方法
    print("MyClass 类的属性 i 为：", x.i)
    print("MyClass 类的方法 f 输出为：", x.f())

def test2():
    x = Complex(3.0, -4.5)
    print(x.r, x.i)  # 输出结果：3.0 -4.5
    x.prt()

if __name__=="__main__":
    test1()
    print("----------------------class's init---------------------------")
    test2()