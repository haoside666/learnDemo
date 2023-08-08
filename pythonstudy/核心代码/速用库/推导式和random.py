# python comprehension 推导式
import random

def fun01():
    # list comprehension
    names = ['Bob', 'Tom', 'alice', 'Jerry', 'Wendy', 'Smith']
    new_names = [name.upper() for name in names if len(name) > 3]
    print(new_names)

    # tuple comprehension
    a = (x for x in range(1, 10))  # 返回的是生成器对象
    print(tuple(a))

    # dict comprehension
    dict1 = {x: x ** 2 for x in (2, 4, 6)}
    print(dict1)

    # set comprehension
    setnew = {i ** 2 for i in (1, 2, 3)}
    print(setnew)

def fun02():
    a = 20
    b = 20
    # is 与 == 区别： is 用于判断两个变量引用对象是否为同一个， == 用于判断引用变量的值是否相等。
    if (a is b):
        print("1 - a 和 b 有相同的标识")
    else:
        print("1 - a 和 b 没有相同的标识")
    # id()函数用于获取对象内存地址。
    if (id(a) is id(b)):
        print("2 - a 和 b 地址有相同的标识")
    else:
        print("2 - a 和 b 地址没有相同的标识")
    print(id(a), id(b)) # 相同常量同一个地址
    # 修改变量 b 的值
    b = 30
    if (a is b):
        print("3 - a 和 b 有相同的标识")
    else:
        print("3 - a 和 b 没有相同的标识")

    if (id(a) is not id(b)):
        print("4 - a 和 b 地址没有相同的标识")
    else:
        print("4 - a 和 b 地址有相同的标识")

# random function
'''
choice(seq)	从序列的元素中随机挑选一个元素，比如random.choice(range(10))，从0到9中随机挑选一个整数。
randrange ([start,] stop [,step])	从指定范围内，按指定基数递增的集合中获取一个随机数，基数默认值为 1
random()	随机生成下一个实数，它在[0,1)范围内。
seed([x])	改变随机数生成器的种子seed。如果你不了解其原理，你不必特别去设定seed，Python会帮你选择seed。
shuffle(lst)	将序列的所有元素随机排序
uniform(x, y)	随机生成下一个实数，它在[x,y]范围内。
'''
def fun03():
    random.seed()
    a = random.random()
    print(a)
    b = random.choice(range(10))
    print(b)
    c = random.randrange(1,100,2)
    print(c)
    d = random.uniform(1, 10)
    print(d)
    list1=[1,2,3,4,5,6,7]
    print(list1)
    random.shuffle(list1)
    print(list1)

# 嵌套列表解析
def fun04():
    matrix = [ [1, 2, 3, 4],
               [5, 6, 7, 8],
               [9, 10, 11, 12]
             ]
    print(matrix)
    print([[row[i] for row in matrix] for i in range(4)])
"""  上述的推导式等价于如下
    for i in range(4):
        transposed_row = []
        for row in matrix:
            transposed_row.append(row[i])
        transposed.append(transposed_row)
"""
if __name__ == "__main__":
    print("------------------------------fun01------------------------------")
    fun01()
    print("------------------------------fun02------------------------------")
    fun02()
    print("------------------------------fun03------------------------------")
    fun03()
    print("------------------------------fun04------------------------------")
    fun04()