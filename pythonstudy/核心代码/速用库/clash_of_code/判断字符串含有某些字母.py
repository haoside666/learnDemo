#判断名字中是否含有w i z a r d字母

import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())
for i in range(n):
    names = input()
    if all(c in names.lower() for c in 'wizard'):
        print('Is a wizard')
    else:
        print('Not a wizard')