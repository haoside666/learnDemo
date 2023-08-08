import sys
import math

n = int(input())  # the number of temperatures to analyse
l=list(map(int,input().split()))
if len(l)==0:
    print(0)
else:
    t=sys.maxsize
    for i in l:
        if abs(i)==abs(t):
            t=max(i,t)
        elif abs(i)<abs(t):
            t=i
    print(t)
