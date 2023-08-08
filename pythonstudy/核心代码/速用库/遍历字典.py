#v使用 del 语句可以从一个列表中根据索引来删除一个元素，而不是值来删除元素。这与使用 pop() 返回一个值不同。
# 可以用 del 语句从列表中删除一个切割，或清空整个列表（我们以前介绍的方法是给该切割赋一个空列表）。
def fun1():
    a = [-1, 1, 66.25, 333, 333, 1234.5]
    del a[0]
    print(a)
    del a[2:4]  #[1, 66.25, 1234.5]
    print(a)
    del a[:]
    print(a)

# 遍历技巧
def fun2():
    # 遍历dictionary
    knights = {'gallahad': 'the pure', 'robin': 'the brave'}
    for k, v in knights.items():
        print(k, v)
    # 索引位置和对应值可以使用 enumerate() 函数同时得到
    for i,v in enumerate(['tic', 'tac', 'toe']):
        print(i,v)
    # 同时遍历两个或更多的序列，可以使用 zip() 组合
    questions = ['name', 'quest', 'favorite color']
    answers = ['lancelot', 'the holy grail', 'blue']
    for q, a in zip(questions, answers):
        print('What is your {0}?  It is {1}.'.format(q, a))
    # 使用 sorted() 函数返回一个已排序的序列，并不修改原值
    basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
    for f in sorted(set(basket)):
        print(f)
    print(basket)

if __name__ == "__main__":
    print("------------------------------fun1------------------------------")
    fun1()
    print("------------------------------fun2------------------------------")
    fun2()