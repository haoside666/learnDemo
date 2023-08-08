import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())
nums = {}
for i in input().split():
    value = int(i)
    if value not in nums:
        nums[value] = 0
    nums[value] += 1
print(nums)


1.值排序,输出键
a=sorted(nums, key=lambda x: nums[x])
或者
a=sorted(nums, key=nums.get)
传入x-->指字典的键  ,按nums[x]--->字典的值进行排序 --->排序之后的还是传入的对象


2.值排序,输出字典
b=sorted(nums.items(), key=lambda item: item[1])
nums.items()-->将字典转化为可迭代对象，其中字典的元素 转化为了元组
如字典为{'lilee':25,'wangyan':21,'liqun'：32} 
nums.items()--->{('lilee',25),('wangyan',21),('liqun',32)} 

传入item-->('lilee',25)  
按item[1]--->25 进行排序--->排序之后的还是传入的对象

3.键排序,输出字典
这里同样转化为元组,只不过是对键排序,输出值
print(sorted(l.items())[0][1])
