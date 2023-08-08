import sys
import math
import re
# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
def p(*args, **kwargs): print(*args, **kwargs)
def E(*args, **kwargs): print(*args, **kwargs, file=sys.stderr)

l = input().split()
E(l)
for i in l:
    if i=="nl":
        print("")
    else:
        m=re.compile(r"[0-9]+")
        n=re.search(m,i).group(0)
        c=i[len(n):]
        if c=="":
            c=i[-1]
            n=i[:-1]
        len1=int(n)
        if c=="sp":print(" "*len1,end="")
        elif c=="bS":print("\\"*len1,end="")
        elif c=="sQ":print("'"*len1,end="")
        else:print(c*len1,end="")
