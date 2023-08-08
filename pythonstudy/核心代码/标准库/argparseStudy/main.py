#
# 该模块使用主要分三步：
# 创建 ArgumentParser() 对象
# 调用 add_argument() 方法添加参数
# 使用 parse_args() 解析添加的参数
#

'''
# 每个参数的含义如下
# name or flags - 选项字符串的名字或者列表，例如 foo 或者 -f, --foo。
# action - 命令行遇到参数时的动作，默认值是 store。
#   store_const，表示赋值为const；
#   append，将遇到的值存储成列表，也就是如果参数重复则会保存多个值;
#   append_const，将参数规范中定义的一个值保存到一个列表；
#   count，存储遇到的次数；此外，也可以继承 argparse.Action 自定义参数解析；
# nargs - 应该读取的命令行参数个数，可以是具体的数字，或者是?号，当不指定值时对于 Positional argument 使用 default，对于 Optional argument 使用 const；或者是 * 号，表示 0 或多个参数；或者是 + 号表示 1 或多个参数。
# const - action 和 nargs 所需要的常量值。
# default - 不指定参数时的默认值。
# type - 命令行参数应该被转换成的类型。
# choices - 参数可允许的值的一个容器。
# required - 可选参数是否可以省略 (仅针对可选参数)。
# help - 参数的帮助信息，当指定为 argparse.SUPPRESS 时表示不显示该参数的帮助信息.
# metavar - 在 usage 说明中的参数名称，对于必选参数默认就是参数名称，对于可选参数默认是全大写的参数名称.
# dest - 解析后的参数名称，默认情况下，对于可选参数选取最长的名称，中划线转换为下划线.

# def add_argument(self,
#                  *name_or_flags: str,
#                  action: Literal["store", "store_const", "store_true", "store_false", "append", "append_const", "count", "help", "version", "extend"] | Type[Action] = ...,
#                  nargs: Literal["?", "*", "+", "...", "A...", "==SUPPRESS=="] | int | _SUPPRESS_T = ...,
#                  const: Any = ...,
#                  default: Any = ...,
#                  type: (str) -> _T | FileType = ...,
#                  choices: Iterable[_T] | None = ...,
#                  required: bool = ...,
#                  help: str | None = ...,
#                  metavar: str | tuple[str, ...] | None = ...,
#                  dest: str | None = ...,
#                  version: str = ...,
#                  **kwargs: Any)

'''
import argparse


def test():
    parser = argparse.ArgumentParser()
    parser.add_argument('integer', type=int, help='display an integer')
    args = parser.parse_args()
    print('the parameter is: ', args.integer)


# input: python argParseTest.py -i 1 2 4 -i 5 6 7
# output:the parameter is:  <class 'list'> [['1', '2', '4'], ['5', '6', '7']]

def test2():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input', action="append", nargs="+", type=str, help="Enter one or more parameters")
    args = parser.parse_args()

    a = vars(args)
    print('the parameter is: ', type(a), a)
    b = a['input']

    c = args.input
    print('the parameter is: ', type(b), b)
    print('the parameter is: ', type(c), c)


'''
$ python3 xxx.py 4 2
4^2 == 16
$ python3 xxx.py 4 2 -q
16
$ python3 xxx.py 4 2 -v
4 to the power 2 equals 16
$ python3 xxx.py 4 2 -vq
usage: xxx.py [-h] [-v | -q] x y
xxx.py: error: argument -q/--quiet: not allowed with argument -v/--verbose
$ python3 xxx.py 4 2 -v --quiet
usage: xxx.py [-h] [-v | -q] x y
xxx.py: error: argument -q/--quiet: not allowed with argument -v/--verbose

注意 [-v | -q]，它的意思是说我们可以使用 -v 或 -q，但不能同时使用两者
'''


def test3():
    parser = argparse.ArgumentParser(description="calculate X to the power of Y")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-v", "--verbose", action="store_true")
    group.add_argument("-q", "--quiet", action="store_true")
    parser.add_argument("x", type=int, help="the base")
    parser.add_argument("y", type=int, help="the exponent")
    args = parser.parse_args()
    answer = args.x ** args.y

    if args.quiet:
        print(answer)
    elif args.verbose:
        print("{} to the power {} equals {}".format(args.x, args.y, answer))
    else:
        print("{}^{} == {}".format(args.x, args.y, answer))


if __name__ == '__main__':
    # test()
    test2()
    # test3()