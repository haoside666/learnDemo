message = input()
l=""

for i in message:
    binary=""
    t=ord(i)
    binary=bin(ord(i))
    binary=(9-len(binary))*"0"+binary[2:] 
    l+=binary

index=0
end=len(l)
ans=[]
while 1:
    c=l[index]
    c_index=index+1
    while 1:
        if c_index==end or c!=l[c_index]:
            break
        else:
            c_index+=1
    length=c_index-index
    ans.append("00" if c=="0" else "0")
    ans.append(length*"0")
    if c_index==end:
        break
    else:
        index=c_index
print(*ans)