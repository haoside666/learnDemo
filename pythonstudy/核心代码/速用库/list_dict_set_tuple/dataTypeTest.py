

# list and tuple
def fun01():
    list = ['abcd', 786, 2.23, 'runoob', 70.2]
    print(list)  # 输出完整列表
    tuple = ('abcd', 786, 2.23, 'runoob', 70.2)
    print(tuple)  # 输出完整元组
    list[0]='1'
    print(list)  # 输出完整列表
    #tuple[0]='1' 修改元组元素的操作是非法的


# set
def fun02():
    sites = {'Google', 'Taobao', 'Runoob', 'Facebook', 'Zhihu', 'Baidu'}
    print(sites)  # 输出集合，重复的元素被自动去掉
    # 成员测试
    if 'Runoob' in sites:
        print('Runoob 在集合中')
    else:
        print('Runoob 不在集合中')
    # set可以进行集合运算
    a = set('abracadabra')
    b = set('alacazam')
    print(a)
    print(b)
    print("a-b:", a - b)  # a 和 b 的差集
    print(a | b)  # a 和 b 的并集
    print(a & b)  # a 和 b 的交集
    print(a ^ b)  # a 和 b 中不同时存在的元素


# dictionary
def fun03():
    dict = {}
    dict['one'] = "1 - 菜鸟教程"
    dict[2] = "2 - 菜鸟工具"
    tinydict = {'name': 'runoob', 'code': 1, 'site': 'www.runoob.com'}
    print(dict['one'])  # 输出键为 'one' 的值
    print(dict[2])  # 输出键为 2 的值
    print(tinydict)  # 输出完整的字典
    print(tinydict.keys())  # 输出所有键
    print(tinydict.values())  # 输出所有值


def typeChange():
    x = int(2.8)  # x 输出结果为 2
    y = float("3")  # y 输出结果为 3.0
    z = str(3.0)  # z 输出结果为 '3.0'
    # eval() 函数用来执行一个字符串表达式，并返回表达式的值。
    print(eval('3 * x'))
    # list tuple dictionary
    list1 = ['Google', 'Taobao', 'Runoob', 'Baidu']
    tuple1 = tuple(list1)
    print(tuple1)
    list2=list(tuple1)
    print(list2)
    # dict(d) 创建一个字典。d必须是一个(key, value) 元组序列
    dict1=dict([('one', 1), ('two', 2), ('three', 3)])
    print(dict1)
    # 整数转化为字符
    print(chr(0x41))

if __name__ == "__main__":
    print("------------------------------fun01------------------------------")
    fun01()
    print("------------------------------fun02------------------------------")
    fun02()
    print("------------------------------fun03------------------------------")
    fun03()
    print("------------------------------typeChange------------------------------")
    typeChange()
