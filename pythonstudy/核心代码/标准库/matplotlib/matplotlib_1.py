from pylab import *

def test():
    # 调用math.pi方法弧度转为角度
    x = arange(0, pi * 2, 0.05)
    y = sin(x)
    plot(x, y)
    xlabel("angle")
    ylabel("sine")
    title('sine wave')
    # 使用show展示图像
    show()

def test2():
    x = linspace(-3,3,50)
    print(x)
    y = x ** 2
    plot(x, y,"r:.")
    show()


def test3():
    x = linspace(-3, 3, 50)
    plot(x, np.sin(x))
    plot(x, np.cos(x), 'r-')
    plot(x, -np.sin(x), 'g--')
    show()

if __name__=="__main__":
    test3()