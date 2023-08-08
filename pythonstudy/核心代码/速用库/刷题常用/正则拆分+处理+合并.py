+向右移动-向左移动
小写字符在[a-z]循环移动
大写字符在[A-Z]循环移动
input:
  Hello wn+1rld!
output:
  Hello world!

方法一:
import re

def moveChar(s,n):return chr(65+(ord(s)-65+n)%26) if s.isupper() else chr(97+(ord(s)-97+n)%26) if s.lower() else s
def MergeL(l1,l2): l1.reverse(),l2.reverse();return [(lambda i: l1.pop() if (l1!=[] and (i%2==0 or l2==[])) else l2.pop())(i) for i in range(len(l1) + len(l2))]


text = "Hello wn+1rld we arf-1 famim-1y!"
l1=re.split(r"[a-zA-Z][+-]\d+",text)
l2=re.findall(r"[a-zA-Z][+-]\d+",text)
l1=[*filter(lambda x:x!="",l1)]
l2=[*map(lambda x:moveChar(x[0],int(x[1:])),l2)]
print(l1,l2)

if text[1]=="+":
    l3=MergeL(l2,l1)
else:
    l3=MergeL(l1,l2)
print(''.join(l3))


方法二:
import re

def moveChar(s,n):return chr(65+(ord(s)-65+n)%26) if s.isupper() else chr(97+(ord(s)-97+n)%26) if s.lower() else s
def MergeL(l1,l2): l1.reverse(),l2.reverse();return [(lambda i: l1.pop() if (l1!=[] and (i%2==0 or l2==[])) else l2.pop())(i) for i in range(len(l1) + len(l2))]


text = "Hello wn+1rld we arf-1 famim-1y!"
s=re.sub(r"([a-zA-Z][+-]\d+)",lambda x:moveChar(x.group(0)[0],int(x.group(0)[1:])),text)
print(s)
