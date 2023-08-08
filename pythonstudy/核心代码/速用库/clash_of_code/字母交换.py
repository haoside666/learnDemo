a='abcdefghijklmnopqrstuvwxyz'
A=a.upper()
n='0123456789'
c='[{()}]'
t = input()
for i in t:
    if i in a:print(a[-a.find(i)-1],end='')
    elif i in n:print(n[-n.find(i)-1],end='')
    elif i in c:print(c[-c.find(i)-1],end='')
    elif i in A:print(A[-A.find(i)-1],end='')
    else:print(i,end='')