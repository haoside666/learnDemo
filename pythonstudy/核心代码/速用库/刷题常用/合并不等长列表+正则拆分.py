# input:
# l
# hello world
# output:
# he2o wor1d
# 
# input:
# a
# aabbccddaabbccddaa
# output:
# 2bbccdd2bbccdd2
#
# input:
# a
# bababaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabb
# output:
# b1b1b56bb
#
# input:
# 8
# zqaazza888123288a
# output:
# zqaazza312322a

import sys
import math
import re
#合并不等长列表l1和l2
def MergeL(l1,l2): l1.reverse(),l2.reverse();return [(lambda i: l1.pop() if (l1!=[] and (i%2==0 or l2==[])) else l2.pop())(i) for i in range(len(l1) + len(l2))]
#合并等长列表
#print([x for y in zip([1,2,3],[4,5,6]) for x in y])

n = input()
t = input()
#拆分
l1 = re.split("[" + n + "]+", t)
l2 = re.split("[^" + n + "]+", t)
#过滤空串
l1 = list(filter(lambda x: x != "", l1))
l2 = list(filter(lambda x: x != "", l2))
#转化为长度
l2 = [*map(lambda x: str(len(x)), l2)]
s = ""
if t[0]==n:
    l3=MerL(l2,l1)
else:
    l3=MerL(l1,l2)

for i in l3:
    s+=i
print(s)
