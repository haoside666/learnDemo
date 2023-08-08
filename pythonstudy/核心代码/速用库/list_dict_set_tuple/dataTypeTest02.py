# list tuple dictionary set

import operator

def fun1():
    list = ['red', 'green', 'blue', 'yellow', 'white', 'black']
    print(list[-1])
    print(list[-2])
    print(list[-3])
    # append
    list1 = ['Google', 'Runoob', 'Taobao']
    list1.append('Baidu')
    print("更新后的列表 : ", list1)
    # delete
    list2 = ['Google', 'Runoob', 1997, 2000]
    print("原始列表 : ", list2)
    del list2[2]
    print("删除第三个元素 : ", list2)
    # compare
    a = [1, 2]
    b = [2, 3]
    c = [2, 3]
    print("operator.eq(a,b): ", operator.eq(a,b))
    print("operator.eq(c,b): ", operator.eq(c,b))

"""
1.list.append(obj)
在列表末尾添加新的对象
2	list.count(obj)
统计某个元素在列表中出现的次数
3	list.extend(seq)
在列表末尾一次性追加另一个序列中的多个值（用新列表扩展原来的列表）
4	list.index(obj)
从列表中找出某个值第一个匹配项的索引位置
5	list.insert(index, obj)
将对象插入列表
6	list.pop([index=-1])
移除列表中的一个元素（默认最后一个元素），并且返回该元素的值
7	list.remove(obj)
移除列表中某个值的第一个匹配项
8	list.reverse()
反向列表中元素
9	list.sort( key=None, reverse=False)
对原列表进行排序
10	list.clear()
清空列表
11	list.copy()
复制列表
"""

def fun2():
    tup1 = (50)
    print(type(tup1))  # 不加逗号，类型为整型
    tup1 = (50,)
    print(type(tup1))  # 加上逗号，类型为元组

    # 元组元素不能进行修改但可以删除整个元组
    tup = ('Google', 'Runoob', 1997, 2000)
    print(tup)
    del tup
    print("删除后的元组 tup : ")
    # print(tup)

"""
1	len(tuple)
计算元组元素个数。	
2	max(tuple)
返回元组中元素最大值。	
3	min(tuple)
返回元组中元素最小值。	
4	tuple(iterable)
将可迭代系列转换为元组。	
"""

# 一对大括号创建一个空的字典：{}
def fun3():
    tinydict = {'Name': 'Runoob', 'Age': 7, 'Class': 'First'}
    print("tinydict['Name']: ", tinydict['Name'])
    print("tinydict['Age']: ", tinydict['Age'])
    print(tinydict.items())
    print(tinydict.keys())
    print(tinydict.values())
    del tinydict['Name']  # 删除键 'Name'
    print(tinydict)
    tinydict.clear()  # 清空字典
    print(tinydict)
    del tinydict  # 删除字典

"""
1	dict.clear()
删除字典内所有元素
2	dict.copy()
返回一个字典的浅复制
3	dict.fromkeys()
创建一个新字典，以序列seq中元素做字典的键，val为字典所有键对应的初始值
4	dict.get(key, default=None)
返回指定键的值，如果键不在字典中返回 default 设置的默认值
5	key in dict
如果键在字典dict里返回true，否则返回false
6	dict.items()
以列表返回一个视图对象
7	dict.keys()
返回一个视图对象
8	dict.setdefault(key, default=None)
和get()类似, 但如果键不存在于字典中，将会添加键并将值设为default
9	dict.update(dict2)
把字典dict2的键/值对更新到dict里
10	dict.values()
返回一个视图对象
11	pop(key[,default])
删除字典 key（键）所对应的值，返回被删除的值。
12	popitem()
返回并删除字典中的最后一对键和值。
"""

# set() 创建一个空的集合
# 集合（set）是一个无序的不重复元素序列。
def fun4():
    # add
    thisset = set(("Google", "Runoob", "Taobao"))
    thisset.add("Facebook")
    print(thisset)
    #remove
    thisset.remove("Google")
    print(thisset)
    thisset.discard("NotExist")  # 不存在不会发生错误
    print(len(thisset))
    # clear
    thisset.clear()
    print(len(thisset))

"""
add()	为集合添加元素
clear()	移除集合中的所有元素
copy()	拷贝一个集合
difference()	返回多个集合的差集
difference_update()	移除集合中的元素，该元素在指定的集合也存在。
discard()	删除集合中指定的元素
intersection()	返回集合的交集
intersection_update()	返回集合的交集。
isdisjoint()	判断两个集合是否包含相同的元素，如果没有返回 True，否则返回 False。
issubset()	判断指定集合是否为该方法参数集合的子集。
issuperset()	判断该方法的参数集合是否为指定集合的子集
pop()	随机移除元素
remove()	移除指定元素
symmetric_difference()	返回两个集合中不重复的元素集合。
symmetric_difference_update()	移除当前集合中在另外一个指定集合相同的元素，并将另外一个指定集合中不同的元素插入到当前集合中。
union()	返回两个集合的并集
update()	给集合添加元素
"""


if __name__ == "__main__":
    print("------------------------------fun1------------------------------")
    fun1()
    print("------------------------------fun2------------------------------")
    fun2()
    print("------------------------------fun3------------------------------")
    fun3()
    print("------------------------------fun4------------------------------")
    fun4()