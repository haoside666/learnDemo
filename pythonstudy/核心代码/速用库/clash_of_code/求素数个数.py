n=int(input())

cnt=0
for i in range(2,n+1):
    flags=1
    for j in range(2,int(i**0.5)+1):
        if i%j==0:
            flags=0
            break
    if flags==1:
        cnt+=1

print(cnt)