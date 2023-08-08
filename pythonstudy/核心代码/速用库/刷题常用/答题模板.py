# IMPORTS
import sys
import re
import numpy as np
from math import *
from itertools import *
from functools import *
from collections import *

# GENERAL
R = range
I = input
M = math.factorial
# PRINTS
def p(*args, **kwargs): print(*args, **kwargs)
def E(*args, **kwargs): print(*args, **kwargs, file=sys.stderr)
# PARSE
def LI(): return list(input().split())
def LII(): return list(map(int, input().split()))
def RI(n): return [input() for _ in range(n)]
def RII(n): return [int(input()) for _ in range(n)]
# MATH
def isp(n): return n > 1 and all(n%i for i in range(2, ceil(sqrt(n))))
def MergeL(l1,l2): l1.reverse(),l2.reverse();return [(lambda i: l1.pop() if (l1!=[] and (i%2==0 or l2==[])) else l2.pop())(i) for i in range(len(l1) + len(l2))]
def moveChar(s,n):return chr(65+(ord(s)-65+n)%26) if s.isupper() else chr(97+(ord(s)-97+n)%26) if s.islower() else s

def reverseChar(s):return chr(155-ord(s)) if s.isupper() else chr(219-ord(s)) if s.islower() else s

def reverseCharAndDigit(s):return chr(155-ord(s)) if s.isupper() else chr(219-ord(s)) if s.islower() else str(9-int(s)) if s.isdigit() else s

def reverseAllChar(i):a = 'abcdefghijklmnopqrstuvwxyz';A = a.upper();n = '0123456789';c = '[{()}]';return (a[-a.find(i) - 1] if i in a else n[-n.find(i) - 1] if i in n else c[-c.find(i) - 1] if i in c else A[-A.find(i) - 1] if i in A else i)


