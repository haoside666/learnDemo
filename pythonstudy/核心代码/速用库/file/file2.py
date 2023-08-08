import re


def AddLasterTag(filename):
    list = []
    with open(filename, "r") as f:
        for line in f:
            if (":" not in line):
                line.strip()
                line += ":latest"
            list.append(line)
    with open(filename, "w") as f:
        for list1 in list:
            f.write("{}\n".format(list1))


# 去除空行
def clearBlankLines(filename):
    f = open(filename, "r+")
    list1 = []
    for line in f:
        if (len(line.strip()) != 0):
            list1.append(line.strip() + '\n')
    f.close()
    f = open(filename, "w")
    for item in list1:
        f.writelines(item)
    f.close()


# 数字后面加.
def adddot(filename):
    f = open(filename, "r+")
    list1 = []
    for line in f:
        if (re.search('^[0-9]+$', line) != None):
            # list1.append(re.search('^[0-9]+$', line).group(0)+'.\n')
            list1.append(re.search('^[0-9]+$', line).group(0) + ',')
        else:
            list1.append(line)
    f.close()
    f = open(filename, "w")
    for item in list1:
        f.writelines(item)
    f.close()


# 清除所有换行符
def clearAllLn(filename):
    f = open(filename, "r+")
    str = f.read()
    str = str.replace("-\n", "")
    str = str.replace("\n", " ")
    str = str.replace("  "," ")
    str = str.replace("\t", "\n\n")
    f.close()
    f = open(filename, "w")
    f.write("{}\n".format(str))
    f.close()


# 清除类型[1,2,3]的注释模式
def clearAnnotation(in_filename, out_filename):
    f = open(in_filename, "r+")
    str = f.read()
    s = ""
    while re.search("\[[0-9,\x20]+\]", str) != None:
        tuple1 = re.search("\[[0-9,\x20]+\]", str).span()
        s += str[0:tuple1[0]]
        str = str[tuple1[1]:]
    s += str
    f.close()
    f = open(out_filename, "w")
    f.write("{}\n".format(s))
    f.close()


def test1():
    in_filename = "input.txt"
    out_filename = "output.txt"
    # clearBlankLines(in_filename)
    # adddot(filename)
    clearAllLn(in_filename)
    clearAnnotation(in_filename, out_filename)
    # adddot(in_filename)

if __name__ == "__main__":
    test1()
