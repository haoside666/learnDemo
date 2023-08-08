l = input().split()

number = []
stack = []
num = 0
for i in l:
    if i.isdigit() or i[1:].isdigit():
        number.append(i)
    else:
        stack.append(i)
    while len(stack) > 0 and len(number) > 1:
        num = eval(number[-2] + stack.pop() + number[-1])
        number.pop()
        number.pop()
        number.append(str(num))
print(number[0])