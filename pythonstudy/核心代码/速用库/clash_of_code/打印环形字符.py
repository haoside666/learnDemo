input:
ABC
output:
AAAAA
ABBBA
ABCBA
ABBBA
AAAAA


------------------------------------------------------
import sys
import math
import itertools

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

s = input()
n = len(s)
#print(range(n), range(n-2,-1,-1))
for i in itertools.chain(range(n), range(n-2,-1,-1)):
    print(s[:i]+s[i]*(2*n-2*i-1)+s[:i][::-1])
    # print(i,2*n-2*i-1)
    # print(s[:i])
    # print(s[i]*(2*n-2*i-1))
    # print(s[:i][::-1])