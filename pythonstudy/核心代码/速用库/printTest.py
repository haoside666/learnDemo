# This is a sample Python script.
def print_hi():
    counter = 100  # 整型变量
    miles = 1000.0  # 浮点型变量
    name = "runoob"  # 字符串
    print(counter)
    print(miles)
    print(name)
    str = 'Runoob'
    print (str)          # 输出字符串
    print (str[0:-1])    # 输出第一个到倒数第二个的所有字符
    print (str[0])       # 输出字符串第一个字符
    print (str[2:5])     # 输出从第三个开始到第五个的字符
    print (str[2:])      # 输出从第三个开始的后的所有字符
    print (str * 2)      # 输出字符串两次，也可以写成 print (2 * str)
    print (str + "TEST") # 连接字符串

def fun01():
    list = ['abcd', 786, 2.23, 'runoob', 70.2]
    tinylist = [123, 'runoob']
    print(list)  # 输出完整列表
    print(list[0])  # 输出列表第一个元素
    print(list[1:3])  # 从第二个开始输出到第三个元素
    print(list[2:])  # 输出从第三个元素开始的所有元素
    print(tinylist * 2)  # 输出两次列表
    print(list + tinylist)  # 连接列表
    
# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # print_hi()
    fun01()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
