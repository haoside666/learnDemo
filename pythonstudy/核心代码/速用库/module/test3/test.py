from mybag.eat.apple import *
from mybag.sleep.cat import *


def fun1():
    print("test")
    eat()
    sleep()

def fun2():
    from mybag.eat import apple
    from mybag.sleep import cat
    print("test2")
    apple.eat()
    cat.sleep()


if __name__=="__main__":
    fun1()
    print("--------------------------------------------")
    fun2()
