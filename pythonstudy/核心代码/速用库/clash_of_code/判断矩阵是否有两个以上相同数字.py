先行后列，没有输出ok
案例一
input:
1 1 0 0 1 0 0 0 1 1  ---->第一行有三个0
1 0 1 0 1 0 1 0 1 0
1 1 0 0 1 1 0 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
output:
1 1 0 0 1 0 0 0 1 1
案例二
input:
1 1 0 0 1 1 0 0 1 0
1 0 1 0 1 0 1 0 1 0
1 1 0 0 1 1 0 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
output:
1 1 1 1 1 1 1 1 1 1
案例三
input:
1 0 1 0 1 0 1 0 1 0
0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0
0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0
0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0
0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0
0 1 0 1 0 1 0 1 0 1
output:
ok

import numpy as np

l = []
for i in range(10):
    row = list(map(int, input().split()))
    l.append(row)

a = np.array(l)

flags=0
for i in range(20):
    if i > 9:
        lis = a[:, i - 10]
    else:
        lis = a[i]
    s = str(lis)
    if "0 0 0" in s or "1 1 1" in s:
        print(*lis)
        flags=1
        break

if flags==0:
    print("ok")