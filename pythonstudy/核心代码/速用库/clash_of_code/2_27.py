input: 
   7 1 4
   9 4 2
output:
   (1,2),(4,4),(7,9)  

I=input
s=sorted
I(str([*zip( s(map(int,I().split())) , s(map(int,I().split())) )])[1:-1])


计算两个日期相隔的天数
import datetime
t1="2002-03-14"
date1=datetime.datetime.strptime(t1,"%Y-%m-%d")
t2="2022-06-18"
date2=datetime.datetime.strptime(t2,"%Y-%m-%d")
d=data2-data1
print(d.days)


input:
  3

  2
  1
  3
output:
  3 2 1

原始方案:
l=[]
n = int(input())
for i in range(n):
    x = int(input())
    l.append(x)
print(str(sorted(l,reverse=True)).replace(",","")[1:-1])

改进:
n = int(input())
a=sorted([int(input()) for i in range(n)], reverse=True)
print(str(a).replace(",","")[1:-1])

更进一步:
n = int(input())
print(*sorted([int(input()) for i in range(n)], reverse=True))

