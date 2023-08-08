```
语法：
sorted(iterable, key=None, reverse=False)

参数：
iterable – 表示可以迭代的对象，例如可以是dict.items()、dict.keys()等。
key – 是一个函数，用来选取参与比较的元素。
reverse – 排序规则，reverse = True 降序 ， reverse = False 升序（默认）。

返回：
返回重新排序的列表。
```



## 字典排序

```
字典默认传入key,对key进行排序
dict1 =
dict2 = {'a': 5, 'c': 7, 'b': 6, 'd': 3, 'e': 4}

传入a,c,b,d,e对key进行排序
print(sorted(dict2))
传入key,按值进行排序
print(sorted(dict2, key=lambda x: dict2[x]))
传入元组，按item[0](即键进行排序)
print(sorted(dict2.items(), key=lambda item: item[0]))
传入元组，按item[1](即值进行排序)
print(sorted(dict2.items(), key=lambda item: item[1]))

dict1 = {'a': "abc", 'b': "ab", 'c': "a",'d': "abcde", 'e': "abcd"}
dict2 = {'a': 3, 'b': 2, 'c': 1, 'd': 5, 'e': 4}
传入元组，item[0]==>key,dict2[item[0]]字典dict2的值进行排序
print(sorted(dict1.items(), key=lambda item: dict2[item[0]]))
    
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

```



