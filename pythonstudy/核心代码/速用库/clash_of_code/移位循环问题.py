问题描述
有一串序列EFGABCD,其中EF和BC只需移动一位
input:
当前字符之后是需要移动的位置
output:
移动之后的字符
例如：
A2   B
B1   C



a="EFG A BCD "
s=input()
i=a.find(s[0])
c=int(s[1:])
print(a[(i+c)%10])