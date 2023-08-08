方法一:
import datetime
t1="2002-03-14"
date1=datetime.datetime.strptime(t1,"%Y-%m-%d")
t2="2022-06-18"
date2=datetime.datetime.strptime(t2,"%Y-%m-%d")
d=data2-data1
print(d.days)

方法二
from datetime import *
print((date(2022,6,18)-date(2002,3,14)).days)