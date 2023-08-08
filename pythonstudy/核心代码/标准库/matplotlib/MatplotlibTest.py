import numpy as np
import matplotlib.pyplot as plt


# 绘制曲线图
def test1():
    X = np.linspace(-np.pi, np.pi, 256, endpoint=True)
    C, S = np.cos(X), np.sin(X)
    # plt.plot(X, C)
    plt.plot(X, S)
    plt.show()

# 绘制散点图
def test2():
    n = 1024
    X = np.random.normal(0, 1, n)
    Y = np.random.normal(0, 1, n)
    plt.scatter(X, Y)
    plt.show()

def test3():
    n = 12
    X = np.arange(n)
    Y = (1 - X / float(n)) * np.random.uniform(0.5, 1.0, n)
    plt.bar(X, Y)
    plt.xlabel('Xaxis')
    plt.ylabel('Yaxis')
    plt.show()


if __name__ == '__main__':
    # test1()
    # print("----------------------------------------------------------")
    test2()
    # test3()