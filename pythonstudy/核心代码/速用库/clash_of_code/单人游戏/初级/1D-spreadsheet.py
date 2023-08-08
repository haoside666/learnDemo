import time

start=time.perf_counter()



n = 92
inputs=[
"SUB $33 $64",
"ADD $60 $60",
"ADD $61 $61",
"SUB $76 $80",
"SUB $25 $59",
"ADD $58 $28",
"ADD $88 $59",
"ADD $32 $32",
"ADD $83 $21",
"ADD $69 $39",
"ADD $57 $64",
"ADD $26 $26",
"ADD $1 $1",
"SUB $62 $68",
"ADD $73 $1",
"ADD $50 $27",
"SUB $24 $2",
"ADD $14 $12",
"ADD $10 $89",
"SUB $67 $35",
"ADD $58 $58",
"ADD $7 $7",
"SUB $0 $89",
"ADD $20 $20",
"SUB $43 $61",
"SUB $53 $11",
"ADD $37 $37",
"ADD $82 $47",
"ADD $90 $2",
"ADD $89 $89",
"ADD $85 $85",
"SUB $91 $47",
"ADD $69 $69",
"SUB $46 $86",
"SUB $42 $20",
"ADD $12 $12",
"ADD $56 $8",
"ADD $72 $72",
"ADD $9 $32",
"ADD $30 $77",
"ADD $80 $48",
"ADD $79 $81",
"SUB $16 $58",
"SUB $44 $56",
"SUB $63 $21",
"ADD $20 $5",
"SUB $49 $81",
"ADD $54 $54",
"ADD $29 $18",
"SUB $34 $23",
"ADD $47 $47",
"SUB $74 $32",
"SUB $17 $72",
"SUB $71 $26",
"ADD $59 $59",
"ADD $15 $68",
"ADD $21 $21",
"ADD $86 $41",
"ADD $2 $2",
"ADD $11 $11",
"ADD $80 $80",
"ADD $56 $56",
"SUB $31 $50",
"SUB $51 $7",
"ADD $86 $86",
"ADD $72 $35",
"SUB $75 $30",
"SUB $70 $12",
"ADD $50 $50",
"ADD $30 $30",
"SUB $84 $1",
"SUB $52 $37",
"VALUE 1 _",
"ADD $40 $60",
"SUB $66 $69",
"SUB $13 $85",
"SUB $22 $29",
"ADD $55 $85",
"ADD $37 $65",
"ADD $23 $45",
"ADD $29 $29",
"ADD $23 $23",
"ADD $54 $6",
"ADD $38 $7",
"SUB $3 $60",
"ADD $68 $68",
"ADD $81 $81",
"ADD $78 $26",
"ADD $87 $11",
"ADD $64 $64",
"ADD $61 $36",
"SUB $4 $54"
]

方法一:
import sys
n = int(input())

cnt=[]
matrix=[[] for i in range(n)]
l = [0 for i in range(n)]
lis=[i for i in range(n)]
temp=lis.copy()
o=[]
for i in range(n):
    s=input()
    cnt.append(s.count("$"))
    arr=s.split()
    if "$" in arr[1]:
        matrix[int(arr[1][1:])].append(i)
    if "$" in arr[2]:
        matrix[int(arr[2][1:])].append(i)
    o.append(arr)
number=n
print(n,o,file=sys.stderr)
while number:
    lis=temp.copy()
    for i in lis:
        oper_c=o[i]
        if int(cnt[i])==0:
            if "$" in oper_c[1]:
                arg1=l[int(oper_c[1][1:])]
            else:
                arg1=int(oper_c[1])
            if "$" in oper_c[2]:
                arg2=l[int(oper_c[2][1:])]
            elif oper_c[2]!="_":
                arg2=int(oper_c[2])
            else:
                arg2=10001

            if oper_c[0] == "VALUE":
                l[i]=arg1
            elif oper_c[0] == "ADD":
                l[i]=arg1+arg2
            elif oper_c[0] == "SUB":
                l[i]=arg1-arg2
            else:
                l[i]=arg1*arg2
            number-=1
            for j in matrix[i]:
                cnt[j]-=1
            matrix[i].clear()
            temp.remove(i)

for i in l:
    print(i)



所用时间:
0.0007263970328494906


方法二:===>更快
import sys

def calcV(i,oper_c):
    if "$" in oper_c[1]:
        arg1 = l[int(oper_c[1][1:])]
    else:
        arg1 = int(oper_c[1])
    if "$" in oper_c[2]:
        arg2 = l[int(oper_c[2][1:])]
    elif oper_c[2] != "_":
        arg2 = int(oper_c[2])
    else:
        arg2 = 0
    if oper_c[0] == "VALUE":
        l[i] = arg1
    elif oper_c[0] == "ADD":
        l[i] = arg1 + arg2
    elif oper_c[0] == "SUB":
        l[i] = arg1 - arg2
    else:
        l[i] = arg1 * arg2
    number[0] -= 1
    for j in matrix[i]:
        cnt[j] -= 1
        if cnt[j] == 0:
            calcV(j, o[j])
    matrix[i].clear()
    temp.remove(i)

n = int(input())

cnt=[]
matrix=[[] for i in range(n)]
l = [0 for i in range(n)]
lis=[i for i in range(n)]
temp=lis.copy()
o=[]
for i in range(n):
    s=input()
    print(s,file=sys.stderr)
    cnt.append(s.count("$"))
    arr=s.split()
    if "$" in arr[1]:
        matrix[int(arr[1][1:])].append(i)
    if "$" in arr[2]:
        matrix[int(arr[2][1:])].append(i)
    o.append(arr)
number=[n]

while number[0]:
    lis=temp.copy()
    for i in lis:
        if cnt[i]==0:
            calcV(i,o[i])
            break        

for i in l:
    print(i)

所用时间
0.0004910079878754914

print(time.perf_counter()-start)