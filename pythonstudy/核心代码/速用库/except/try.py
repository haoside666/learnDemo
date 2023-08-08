import sys

def test1():
    try:
        a=1/0
        print(a)
    except ZeroDivisionError as str:
        print("0 is not divisible!!\n", "error information is:", str)
    except (RuntimeError, TypeError, NameError):
        pass

def test2():
    while True:
        try:
            x = int(input("请输入一个数字: "))
            break
        except ValueError:
            print("您输入的不是数字，请再次尝试输入！")
        except KeyboardInterrupt:
            print("user termination")
            exit(0)

def raiseExcept():
    try:
        # f = open('myfile.txt')
        # s = f.readline()
        # i = int(s.strip())
        i=1/0
        print(i)
    except OSError as err:
        print("OS error: {0}".format(err))
    except ValueError:
        print("Could not convert data to an integer.")
    except:
        print("Unexpected error:", sys.exc_info()[0])
        raise

def test3():
    try:
        raiseExcept()
    except:
        print("Received thrown exception")

def runoob():
    pass

def test4():
    try:
        runoob()
    except:
        print("error information:", sys.exc_info()[0])
    else:
        try:
            with open('file.log') as file:
                read_data = file.read()
        except FileNotFoundError as fnf_error:
            print(fnf_error)
    finally:
        print('这句话，无论异常是否发生都会执行。')

class MyError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)


def test5():
    try:
        raise MyError(2 * 2)
    except MyError as e:
        print('My exception occurred, value:', e.value)

# 使用 with 关键字系统会自动调用 f.close() 方法
def test6():
    with open("myfile.txt") as f:
        for line in f:
            print(line, end="")

if __name__=="__main__":
    # test1()
    # test2()
    # test3()
    # test4()
    test5()