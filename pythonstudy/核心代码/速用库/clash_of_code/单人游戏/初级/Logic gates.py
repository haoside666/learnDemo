n = int(input())
m = int(input())

d={}
for i in range(n):
    s= input().split()
    d[s[0]]=s[1]

l=["AND","OR","XOR","NAND","NOR","NXOR"]
for i in range(m):
    output_name, _type, n1, n2 = input().split()
    index=l.index(_type)
    s1,s2=d[n1],d[n2]
    if index==0: output="".join(["-" if s1[i]=="-" and s2[i]=="-" else "_" for i in range(len(s1))])
    elif index==1: output="".join(["-" if s1[i]=="-" or s2[i]=="-" else "_" for i in range(len(s1))])
    elif index==2: output="".join(["_" if s1[i]==s2[i] else "-" for i in range(len(s1))])
    elif index==3: output="".join(["_" if s1[i]=="-" and s2[i]=="-" else "-" for i in range(len(s1))])
    elif index==4: output="".join(["_" if s1[i]=="-" or s2[i]=="-" else "-" for i in range(len(s1))])
    else: output="".join(["-" if s1[i]==s2[i] else "_" for i in range(len(s1))])
  
    print(output_name,output)
    