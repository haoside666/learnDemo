import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

w = int(input())
h = int(input())
t = input()
l=[]
for i in range(h):
    row = input()
    l.append(row)

index=[]
for i in t.upper():
    if i.isalpha():
        index.append(ord(i)-65)
    else:
        index.append(26)

for j in range(h):
    for i in range(len(index)):
        begin=index[i]*w
        end=(index[i]+1)*w
        print(l[j][begin:end],end="")
    print("")