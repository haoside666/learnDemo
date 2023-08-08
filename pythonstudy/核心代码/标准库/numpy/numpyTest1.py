import numpy as np


def test1():
    myarray = np.array([[1, 2, 3], [2, 3, 4]])
    print(myarray)
    print(myarray.shape)  # 获得张量的形状  (2, 3)


def test2():
    print(np.ones(3))  # 创建全1向量（1维）
    print(np.zeros(3))  # 创建全0向量
    print(np.random.random(3))  # 创建全随机数字向量
    print(np.arange(1, 8, 2))  # 创建从1到8（不包含）间隔为2的数字向量
    print(np.zeros((3, 3)))  # 创建全0矩阵（2维）


def test3():
    myarray = np.array([[1, 2, 3], [2, 3, 4], [3, 4, 5]])
    print(myarray[0])
    print(myarray[-1])
    print(myarray[0:3, 1:])  # 访问前三项从第二个元素开始的序列
    print(myarray[1, 2])   # or print(myarray[1][2])



def test4():
    myarray1 = np.arange(12)
    myarray2 = myarray1.reshape(3, 4)
    myarray3 = myarray2.reshape(4, 3)
    myarray4 = myarray3.T
    print(myarray1)
    print(myarray2)
    print(myarray3)
    print(myarray4)


def test5():
    myarray1 = np.array([[1, 2, 3], [2, 3, 4], [3, 4, 5]])
    myarray2 = np.array([[11, 21, 31], [21, 31, 41], [31, 41, 51]])
    print(myarray1 + myarray2)
    print(myarray1 * myarray2)


def test6():
    a = np.array([[1, 2], [3, 4]])
    b = np.array([[11, 12], [13, 14]])
    print(a)
    print(b)
    print("matrix a and matrix b product:\n", np.dot(a, b))


# calc方差
def test7():
    labels = np.array([1, 2, 3])
    predictions = np.array([2, 4, 1])
    error = (np.sum(np.square(predictions - labels))) / len(labels)
    print(error)


if __name__ == '__main__':
    test1()
    print("----------------------------------------------------------")
    test2()
    print("----------------------------------------------------------")
    test3()
    print("----------------------------------------------------------")
    test4()
    print("----------------------------------------------------------")
    test5()
    print("----------------------------------------------------------")
    test6()
    print("----------------------------------------------------------")
    test7()
