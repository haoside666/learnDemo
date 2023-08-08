方法一:
d={}
for i in "1 1 1 2 2 2 3 3 3 4 4 5 5".split():
    c=int(i)
    if c not in d:
        d[c]=1
    else:
        d[c]+=1
d=sorted(d.items(), key=lambda item: item[1],reverse=True)
f=d[0][1]
d=[*filter(lambda x:x[1]==f,d)]
print(f'{sorted(d)[-1][0]}\n{f}')


方法二：
d = {}
for i in "1 1 1 2 2 2 3 3 3 4 4 5 5".split():
    c=int(i)
    if c not in d:
        d[c]=1
    else:
        d[c]+=1
s1=pd.Series(d)
df=pd.DataFrame({"value":s1.index,"f":s1.values})
df.sort_values(["f","value"],inplace=True,ascending=False)
print(f'{df.iloc[0,0]}\n{df.iloc[0,1]}')

方法二:
l=[*map(int,"3 3 3 2 2 2 1 1 1 4 4 5 5 0 0 0".split())]
a=sorted(set(l), key=l.count)[-1]
f=l.count(a)
print(f'{a}\n{f}')


# np.bincount：首先找到数组最大值max，然后返回0～max的各个数字出现的次数，在上例中，0出现了1次，1出现了1次，2出现了2次...以此类推。np.bincount返回的数组中的下标对应的就是原数组的元素值。
方法三:===>跟方法二思路差不多(有负数不行,推荐方法二)
array = [0, 2, 2, 3, 5, 5, 5, 4, 4, 4, 7]
l=np.bincount(array)
a=np.argsort(l)[-1]
print(l)
f=max(l)
print(f'{a}\n{f}')