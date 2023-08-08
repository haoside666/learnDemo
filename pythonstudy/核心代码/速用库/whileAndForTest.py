
# Fibonacci series: 斐波纳契数列
def fun1():
    a, b = 0, 1
    while b < 10:
        print(b)
        a, b = b, a+b

def fun2():
    a, b = 0, 1
    while b < 1000:
        print(b, end=',')
        a, b = b, a + b
    print()

def fun3():
    var1 = 100
    if var1:
        print("1 - if 表达式条件为 true")
        print(var1)

# if elif else
def fun4():
    number = 7
    guess = -1
    print("数字猜谜游戏!")
    while guess != number:
        guess = int(input("请输入你猜的数字："))

        if guess == number:
            print("恭喜，你猜对了！")
        elif guess < number:
            print("猜的数字小了...")
        elif guess > number:
            print("猜的数字大了...")

#  Python 中没有 do..while 循环
# while
def fun5():
    count = 0
    while count < 5:
        print(count, " 小于 5")
        count = count + 1
    else:
        print(count, " 大于或等于 5")

# for
def fun6():
    sites = ["Baidu", "Google", "Runoob", "Taobao"]
    for site in sites:
        if site == "Runoob":
            print("菜鸟教程!")
            break
        print("循环数据 " + site)
    else:
        print("没有循环数据!")
    print("完成循环!")

# pass是空语句，是为了保持程序结构的完整性
def fun7():
    for i in range(5):
        print(i)
    for letter in 'Runoob':
        if letter == 'o':
            pass
            print('执行 pass 块')
        print('当前字母 :', letter)

if __name__ == "__main__":
    # print("------------------------------fun1------------------------------")
    # fun1()
    # print("------------------------------fun2------------------------------")
    # fun2()
    # print("------------------------------fun3------------------------------")
    # fun3()
    # print("------------------------------fun4------------------------------")
    # fun4()
    print("------------------------------fun5------------------------------")
    fun5()
    print("------------------------------fun6------------------------------")
    fun6()
    print("------------------------------fun7------------------------------")
    fun7()
