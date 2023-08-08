# string
def fun1():
    a = "Hello"
    b = "Python"

    print("a + b 输出结果：", a + b)
    print("a * 2 输出结果：", a * 2)
    print("a[1] 输出结果：", a[1])
    print("a[1:4] 输出结果：", a[1:4])

    if ("H" in a):
        print("H 在变量 a 中")
    else:
        print("H 不在变量 a 中")

    if ("M" not in a):
        print("M 不在变量 a 中")
    else:
        print("M 在变量 a 中")

    print(r'\n')
    print(R'\n')

def fun2():
    # 字符串格式化
    print("我叫 %s 今年 %d 岁!" % ('小明', 10))

    para_str = """这是一个多行字符串的实例
    多行字符串可以使用制表符
    TAB ( \t )。
    也可以使用换行符 [ \n ]。
    """
    print(para_str)
    errHTML = '''
    <HTML><HEAD><TITLE>
    Friends CGI Demo</TITLE></HEAD>
    <BODY><H3>ERROR</H3>
    <B>%s</B><P>
    <FORM><INPUT TYPE=button VALUE=Back
    ONCLICK="window.history.back()"></FORM>
    </BODY></HTML>
    '''
    print(errHTML)


# f-string
# f-string 格式化字符串以 f 开头，后面跟着字符串，字符串中的表达式用大括号 {} 包起来，它会将变量或表达式计算后的值替换进去
def fun3():
    name = 'Runoob'
    print(f'Hello {name}')  # 替换变量
    print(f'{1 + 2}')
    w = {'name': 'Runoob', 'url': 'www.runoob.com'}
    print(f'{w["name"]}: {w["url"]}')

"""
1.capitalize()
将字符串的第一个字符转换为大写

2.count(str, beg= 0,end=len(string))
返回 str 在 string 里面出现的次数，如果 beg 或者 end 指定则返回指定范围内 str 出现的次数


3.expandtabs(tabsize=8)
把字符串 string 中的 tab 符号转为空格，tab 符号默认的空格数是 8 。

4.find(str, beg=0, end=len(string))
检测 str 是否包含在字符串中，如果指定范围 beg 和 end ，则检查是否包含在指定范围内，如果包含返回开始的索引值，否则返回-1

5.isalnum()
如果字符串至少有一个字符并且所有字符都是字母或数字则返 回 True，否则返回 False

6.isalpha()
如果字符串至少有一个字符并且所有字符都是字母或中文字则返回 True, 否则返回 False

7.isdigit()
如果字符串只包含数字则返回 True 否则返回 False..

8.islower()
如果字符串中包含至少一个区分大小写的字符，并且所有这些(区分大小写的)字符都是小写，则返回 True，否则返回 False

9.isnumeric()
如果字符串中只包含数字字符，则返回 True，否则返回 False

10.isspace()
如果字符串中只包含空白，则返回 True，否则返回 False.

11.istitle()
如果字符串是标题化的(见 title())则返回 True，否则返回 False

12.isupper()
如果字符串中包含至少一个区分大小写的字符，并且所有这些(区分大小写的)字符都是大写，则返回 True，否则返回 False

13.len(string)
返回字符串长度

14.lower()
转换字符串中所有大写字符为小写.

15.lstrip()
截掉字符串左边的空格或指定字符。

16.max(str)
返回字符串 str 中最大的字母。

17.min(str)
返回字符串 str 中最小的字母。

18.replace(old, new [, max])
把 将字符串中的 old 替换成 new,如果 max 指定，则替换不超过 max 次。

19.rstrip()
删除字符串末尾的空格或指定字符。

20.split(str="", num=string.count(str))
以 str 为分隔符截取字符串，如果 num 有指定值，则仅截取 num+1 个子字符串

21.strip([chars])
在字符串上执行 lstrip()和 rstrip()

"""
def fun4():
    str="       hello world      "
    print(str, len(str))
    print(str.lstrip(), len(str.lstrip()))
    print(str.rstrip(), len(str.rstrip()))
    print(str.strip(), len(str.strip()))
    str1="I like the apple on the table"
    print(str1.split(" "))


if __name__ == "__main__":
    print("------------------------------fun01------------------------------")
    fun1()
    print("------------------------------fun02------------------------------")
    fun2()
    print("------------------------------fun03------------------------------")
    fun3()
    print("------------------------------fun04------------------------------")
    fun4()