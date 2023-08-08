import os,pickle,pprint
"""
open
模式	    r	r+	w	w+	a	a+
读	        +	+		+		+
写		        +	+	+	+	+
创建			    +	+	+	+
覆盖			    +	+
指针在开始	+	+	+	+
指针在结尾					+	+
"""

"""
open(file, mode='r', buffering=-1, encoding=None, errors=None, newline=None, closefd=True, opener=None)
参数说明:
file: 必需，文件路径（相对或者绝对路径）。
mode: 可选，文件打开模式
buffering: 设置缓冲
encoding: 一般使用utf8
errors: 报错级别
newline: 区分换行符
closefd: 传入的file参数类型
opener: 设置自定义开启器，开启器的返回值必须是一个打开的文件描述符。
"""
def fwrite(filename):
    # 打开一个文件
    f = open(filename, "w")
    f.write("Python 是一个非常好的语言。\n是的，的确非常好!!\n")
    # 关闭打开的文件
    f.close()
"""
    f.read(size), 这将读取一定数目的数据, 然后作为字符串或字节对象返回。
    size 是一个可选的数字类型的参数。 当 size 被忽略了或者为负, 那么该文件的所有内容都将被读取并且返回
"""
def fread(filename):
    f = open(filename, "r")
    print(f.read())
    f.close()


def test1():
    filename="./output.txt"
    if not os.access(filename, os.F_OK):
        fwrite(filename)
        print("write cusseed!!")
    else:
        fread(filename)
        print("read file cusseed!!")

def test2():
    filename="./bigfile.txt"
    fread(filename)
# f.readline() 会从文件中读取单独的一行。换行符为 '\n'。f.readline() 如果返回一个空字符串, 说明已经已经读取到最后一行。
def test3():
    filename="output.txt"
    f = open(filename, "r")
    print(f.readline())
    #打印当前文件指针位置
    print(f.tell())
    # 移回文件开头
    f.seek(0, 0)
    print(f.readlines())
    f.close()

def serialization():
    # 使用pickle模块将数据对象保存到文件
    data1 = {'a': [1, 2.0, 3, 4 + 6j],
             'b': ('string', u'Unicode string'),
             'c': None}
    selfref_list = [1, 2, 3]
    output = open('data.pkl', 'wb')
    # Pickle dictionary using protocol 0.
    pickle.dump(data1, output)
    # Pickle the list using the highest protocol available.
    pickle.dump(selfref_list, output, -1)
    output.close()

def reserialization():
    # 使用pickle模块从文件中重构python对象
    pkl_file = open('data.pkl', 'rb')
    data1 = pickle.load(pkl_file)
    print("data1", end=":")
    pprint.pprint(data1)
    data2 = pickle.load(pkl_file)
    print("data2", end=":")
    pprint.pprint(data2)
    pkl_file.close()

# python的pickle模块实现了基本的数据序列和反序列化。
def test4():
    serialization()
    reserialization()

if __name__=="__main__":
    # test1()
    # test2()
    # test3()
    test4()
