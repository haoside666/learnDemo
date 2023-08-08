例题一:
input:
4
++--
output:
-1

两个相邻的符号相同值为-1,不同为+1,结果为字符串所有符号生成值之和

input()
w=input()
print(sum(-1 if w[i]==w[i+1]else 1 for i in range(len(w)-1)))



例题二:
input:
m=Hello World
k=HeloWrd  --->eloWrdH
将m中的H换成e e换成l依次类推
output:
ellow rWdoH


m = input()
k = input()
s=k[1:len(k)]+k[0]
# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)
dic=dict(zip(k,s))
s1=""
for c in m:
    if c in dic:
        c=dic[c]
    s1+=c
print(s1)