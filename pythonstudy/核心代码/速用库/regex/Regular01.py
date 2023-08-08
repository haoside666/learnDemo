import re


def clearPrefix2(filename):
    list = []
    with open(filename, "r") as file:
        for line in file:
            flags=0
            for list1 in list:
                if line.find(list1) != -1:
                    flags=1
                    break
            if flags==0:
                list.append(line.strip())
    with open(filename, "w") as f:
        for list1 in list:
            f.write("{}\n".format(list1))


# re.match 尝试从字符串的起始位置匹配一个模式，如果不是起始位置匹配成功的话，match()就返回none。
# re.search 扫描整个字符串并返回第一个成功的匹配。
def test1():
    print(re.match('www', 'www.runoob.com').span())  # 在起始位置匹配
    print(re.match('com', 'www.runoob.com'))
    str = "google runoob taobao[1],ok"
    print(re.search("[a-z]+", str))  # search[a-z]中的所有字符一次或多次
    print(re.search("[^a-z]", str))  # search除了 [a-z] 中字符的所有字符
    print(re.search("\[[0-9]+\]", str))
    print(type(re.search("\[[0-9]+\]", str).span()))


def test2():
    s = ""
    str = "google runoob taobao[1],ok[2],no[3,4],exit"
    while re.search("\[[0-9,]+\]", str) != None:
        tuple1 = re.search("\[[0-9,]+\]", str).span()
        s += str[0:tuple1[0]]
        str = str[tuple1[1]:]
    s += str
    print(s)


if __name__ == "__main__":
    # test1()
    test2()
    str = "google runoob taobao[1, 2,3, 4],ok,no,exit"
    print(re.search("\[[0-9,\x20]+\]", str))
