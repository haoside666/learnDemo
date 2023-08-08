import numpy as np


def fun():
    arr = np.array([
        [[1, 2, 3], [4, 5, 6]],
        [[7, 8, 9], [10, 11, 12]]]
    )
    a = np.array([1, 2, 3, 4, 5, 6, 7])
    b = np.array([1, 2, 3, 4, 5, 6, 7])
    print("{:.0f}".format(12345678.40))
    print(a[-3:-1])
    print(b[1:5:2])
    print(arr[0, 1, 2])


# numpy 数组副本 vs 视图
def test():
    arr = np.array([1, 2, 3, 4, 5])
    x = arr.copy()
    arr[0] = 61
    print(arr)
    print(x)

    arr1 = np.array([1, 2, 3, 4, 5])
    x1 = arr.view()
    arr1[0] = 61
    print(arr1)
    print(x1)


def test2():
    x, y = [int(i) for i in input().split()]
    l = np.zeros((2 * x + 1, 2 * y + 1), "U")
    for i in range(2 * x + 1):
        for j in range(2 * y + 1):
            if i == j or i + j == 2 * y:
                l[i][j] = "*"
            else:
                l[i][j] = " "

    for i in range(2 * x + 1):
        s = "".join([j for j in l[i]])
        print(s.rstrip())


def test3():
    arr = np.full((2, 2), " ")
    print(arr)
    print(np.arange(9).reshape((3, 3)))
    print(np.arange(8).reshape(2, 4, 1))
    #squeeze--->这是一个主要用来降维的函数
    print(np.arange(8).reshape(2, 4, 1).squeeze())
    arr1 = np.arange(12).reshape(2, 6, 1)
    print(arr1.shape,arr1.transpose(1, 2, 0).shape)
    print(arr1,arr1.transpose(1, 2, 0))

def test4():
    arr=np.array([2,5,3,6,8,1,9,7,4])
    print(arr.min())
    print(arr.argmin())
    print('{:.0f}'.format(arr.mean()))


if __name__ == "__main__":
    a = np.array([[6, 3, 7, 4, 6], [9, 2, 6, 7, 4], [3, 7, 7, 2, 5], [4, 1, 7, 5, 1]])
    print(np.max(a, axis=0))
    print(np.max(a, axis=1))

