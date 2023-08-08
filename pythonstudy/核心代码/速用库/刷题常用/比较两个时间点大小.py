第一行输入约定时间
第二行输入到达时间
到达时间比约定时间小==>打印EARLY,晚打印DELAYED,刚好打印ON TIME

import sys
import math


t = input().replace(":","")
l = input().replace(":","")
if t == l:
    print("ON TIME")
elif int(t)>int(l):
    print("EARLY")
else:print("DELAYED")