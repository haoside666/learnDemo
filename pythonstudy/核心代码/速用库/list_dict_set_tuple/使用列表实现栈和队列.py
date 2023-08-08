# stack queue
from collections import deque

# 使用列表实现栈
def fun1():
    stack=[1,2,3,4,5]
    print(stack)
    # append
    stack.append(6)
    print(stack)
    # pop
    stack.pop()
    print(stack)
    # top
    print(stack.pop())
    print(stack)

# 将列表当作队列使用
def fun2():
    queue = deque(["Eric", "John", "Michael"])
    print(queue)
    queue.appendleft("1")
    print(queue)
    print(queue.popleft())
    print(queue.pop())
    print(queue)



if __name__=="__main__":
    print("------------------------------fun1------------------------------")
    fun1()
    print("------------------------------fun2------------------------------")
    fun2()
