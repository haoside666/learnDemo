l=[]
n = int(input())
l=[input() for i in range(n)]
m=len(l[0])
arr=[(i,j) for i in range(n) for j in range(m) if l[i][j] in "<>^"]

end=len(arr)-1
t=sorted([abs(arr[i][1]-arr[end][1])-abs(arr[i][0]-arr[end][0]) for i in range(end)])

result=[0 for i in range(t[-1])]
for i in t:
    result[i-1]=1

print("\n".join(["WAIT" if i==0 else "SHOOT" for i in result]))