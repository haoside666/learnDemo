## 介绍

Pandas  在 ndarray 数组（NumPy 中的数组）的基础上构建出了两种不同的数据结构，分别是 Series（一维数据结构）DataFrame（二维数据结构）：

- Series 是带标签的一维数组，这里的标签可以理解为索引，但这个索引并不局限于整数，它也可以是字符类型，比如 a、b、c 等；
- DataFrame 是一种表格型数据结构，它既有行标签，又有列标签。


下面对上述数据结构做简单地的说明：

| 数据结构  | 维度 | 说明                                                         |
| --------- | ---- | ------------------------------------------------------------ |
| Series    | 1    | 该结构能够存储各种数据类型，比如字符数、整数、浮点数、Python 对象等，Series 用 name 和 index 属性来描述 数据值。Series 是一维数据结构，因此其维数不可以改变。 |
| DataFrame | 2    | DataFrame 是一种二维表格型数据的结构，既有行索引，也有列索引。行索引是 index，列索引是 columns。 在创建该结构时，可以指定相应的索引值。 |

## 导入库

```
import pandas as pd
```

## series结构与dataframe结构

```
series结构
s=pd.Series( data, index, dtype, copy)
参数说明如下所示：

参数名称	描述
data	输入的数据，可以是列表、常量、ndarray 数组等。
index	索引值必须是惟一的，如果没有传递索引，则默认为 np.arrange(n)。
dtype	dtype表示数据类型，如果没有提供，则会自动判断得出。
copy	表示对 data 进行拷贝，默认为 False。

Series常用属性
名称	属性
axes	以列表的形式返回所有行索引标签。
dtype	返回对象的数据类型。
empty	返回一个空的 Series 对象。
ndim	返回输入数据的维数。
size	返回输入数据的元素数量。
values	以 ndarray 的形式返回 Series 对象。
index	返回一个RangeIndex对象，用来描述索引的取值范围。
Series常用函数
1.Series.value_counts(normalize=False, sort=True, ascending=False, bins=None, dropna=True) 
参数
normalize: 如果为true，则返回的对象将包含唯一值的相对频率。否则，返回其频数。
sort: It sort by the values.
ascending: It sort in the ascending order.
bins: Rather than counting the values, it groups them into the half-open bins that provide convenience for the pd.cut, which only works with numeric data.
dropna: It does not include counts of NaN.

2.idxmax返回最大值对应的索引

--------------------------------------------------------------------------
创建series结构
字典形式
arr=pd.Series({"name":"xiao ming","age":18,"sex":"man","grade":80})
数组形式
brr = pd.Series(["xiao ming",18,"man",80],["name","ago","sex","grade"])

访问series数据
print(brr[0])
print(brr["name"])
print(arr[:3])  --->返回前三行数据
print(arr.head(3))--->返回前三行数据

print(brr.size) --—>4
print(brr.values) --->["xiao ming",18,"man",80]
print(brr.index)   --->返回索引的取值范围 ["name","ago","sex","grade"]
print(brr.index[0]) --->name


缺失值处理
data=np.array([1,2,5,None,None])
s = pd.Series(data,copy=True)--->使用深拷贝

f=pd.isnull(s)   --->检测缺失值
k=1
for i in range(f.size):
	if f[i]:
		s[i]="None"+str(k)
		k+=1
print(s)
print(data)
--------------------------------------------------------------------------

DataFrame结构
pd.DataFrame( data, index, columns, dtype, copy)
 
参数说明：
参数名称	说明
data	输入的数据，可以是 ndarray，series，list，dict，标量以及一个 DataFrame。
index	行标签，如果没有传递 index 值，则默认行标签是 np.arange(n)，n 代表 data 的元素个数。
columns	列标签，如果没有传递 columns 值，则默认列标签是 np.arange(n)。
dtype	dtype表示每一列的数据类型。
copy	默认为 False，表示复制数据 data。

常用属性和方法
名称	属性&方法描述
T	行和列转置。
axes	返回一个仅以行轴标签和列轴标签为成员的列表。----->axis=0 表示按垂直方向进行计算，而 axis=1 则表示按水平方向
dtypes	返回每列数据的数据类型。
empty	DataFrame中没有数据或者任意坐标轴的长度为0，则返回True。
ndim	轴的数量，也指数组的维数。
shape	返回一个元组，表示了 DataFrame 维度。
size	DataFrame中的元素数量。
values	使用 numpy 数组表示 DataFrame 中的元素值。
head()	返回前 n 行数据。
tail()	返回后 n 行数据。
shift()	将行或列移动指定的步幅长度


--------------------------------------------------------------------------
创建和删除
注意字典创建与列表创建的区别，字典为列，列表为行
data = {
        'A': [1, 0, 1, 1],
        'B': [0, 2, 5, 0],
        'C': [4, 0, 4, 4],
        'D': [1, 0, 1, 1],
        'E': [1, 0, 1, 1]
}
data = [
    [1, 0, 1, 1],
    [0, 2, 5, 0],
    [4, 0, 4, 4],
    [1, 0, 1, 1],
    [1, 0, 1, 1]
]
    
arr=pd.DataFrame([[1,2,3],[4,5,6],[7,8,9]])
print(arr)
arr.pop(0)--->删除列
print(arr)

brr = pd.DataFrame([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print(brr)
brr=brr.drop(0)-->删除行，需接受返回值
print(brr)

访问
arr=pd.DataFrame([[1,2,3],[4,5,6],[7,8,9]])
print(arr[0]) -->访问列
print(arr.loc[0])-->访问行

arr=pd.DataFrame([[1,2,3],[4,5,6],[7,8,9]],index=["row1","row2","row3"],columns=["col1","col2","col3"])
print(arr)
print(arr["col1"])      -->访问col1列
print(arr.loc["row1"])  -->访问row1行

切片(重点)
arr = pd.DataFrame([["a",1, 2, 3], ["b",4, 5, 6], ["c",7, 8, 9]])
print(arr)
print(arr[1:])--->得到第一行到最后一行的数据
print(arr[np.arange(1,4)])--->arr[[1,2,3]]得到第一列到第三列的数据
也可以通过loc，iloc函数进行切片、
方法名称		说明
.loc[]		基于标签索引选取数据(与iloc有一定区别)
.iloc[]		基于整数索引选取数据
	iloc uses the Python stdlib indexing scheme, where the first element of the range is included and the last one excluded. So 0:10 will select entries 0,...,9. loc, meanwhile, indexes inclusively. So 0:10 will select entries 0,...,10
	iloc使用Python标准库索引方案，其中范围的第一个元素被包含，最后一个元素被排除。所以0:10将选择条目0…9。同时，loc包含索引。所以0:10将选择条目0…10
	
arr = pd.DataFrame([["a", 1, 2, 3], ["b", 4, 5, 6], ["c", 7, 8, 9]])
print(arr)
print(arr[1:])				#从第一行开始
print(arr.loc[1:,1:])		#指定行和列,连续形式
print(arr.loc[[0,2],[0,2]])	#指定行和列,离散形式



属性测试
arr=pd.DataFrame([[1,2,3],[4,5,6],[7,8,9]])
print(arr)
print(arr.shape)
print(arr.head(2))

print(arr.T)
print(arr.size)
print(arr.index)
print(arr.columns)
```

## pandas描述性统计

```
函数名称		描述说明
count()		统计某个非空值的数量。
sum()		求和
mean()		求均值
median()	求中位数
mode()		求众数
std()		求标准差
min()		求最小值
max()		求最大值
abs()		求绝对值
prod()		求所有数值的乘积。
cumsum()	计算累计和，axis=0，按照行累加；axis=1，按照列累加。
cumprod()	计算累计积，axis=0，按照行累积；axis=1，按照列累积。
corr()		计算数列或变量之间的相关系数，取值-1到1，值越大表示关联性越强。
describe() 	显示与 DataFrame 数据列相关的统计信息摘要,包括count、mean、std、min、25%、75%、max
通过 describe() 提供的include能够筛选字符列或者数字列的摘要信息。

include 相关参数值说明如下：
object： 表示对字符列进行统计信息描述；
number：表示对数字列进行统计信息描述；
all：汇总所有列的统计信息。
用法
df.describe(include="all")
```

## pandas使用自定义函数

```
df = pd.DataFrame([[1, 2, 1], [4, 5, 5], [7, 8, 9]])
print(df)
pipe
print("对所有数据(即DataFrame对象进行操作)")
print(df.pipe(lambda x: type(x)))

apply
#axis=0垂直方向 =1水平方向
print("对一行或一列(即series对象)进行操作")
print("对一列求和:")
print(df.apply(np.sum, axis=0))
print("去除一行重复数据并按升序排序")
print(df.apply(lambda x: sorted(set(x)), axis=1))
print("求一行最大值与最小值的差")
temp = df.apply(lambda x: max(x) - min(x), axis=1)
print(*temp.values)

applymap
print("对单个数据进行操作")
print(df.applymap(lambda x: x + 3))
```

## pandas reindex重置索引

```
N = 20
df = pd.DataFrame({
    'A': pd.date_range(start='2016-01-01', periods=N, freq='D'),
    'x': np.linspace(0, stop=N - 1, num=N),
    'y': np.random.rand(N),
    'C': np.random.choice(['Low', 'Medium', 'High'], N).tolist(),
    'D': np.random.normal(100, 10, size=(N)).tolist()
})
print(df)
# 重置行、列索引标签
df_reindexed = df.reindex(index=[2, 0, 5], columns=['C', 'A', 'B'])
print(df_reindexed)

填充元素值
reindex_like() 提供了一个可选的参数method，使用它来填充相应的元素值，参数值介绍如下：
pad/ffill：向前填充值；
bfill/backfill：向后填充值；
nearest：从距离最近的索引值开始填充。
```

![image-20230320203641509](.\images\image-20230320203641509.png)

## pandas遍历

```
对于 Series 而言，您可以把它当做一维数组进行遍历操作；而像 DataFrame 这种二维数据表结构，则类似于遍历 Python 字典。

N = 5
df = pd.DataFrame({
    'A': pd.date_range(start='2016-01-01', periods=N, freq='D'),
    'x': np.linspace(0, stop=N - 1, num=N),
    'y': np.random.rand(N),
    'C': np.random.choice(['Low', 'Medium', 'High'], N).tolist(),
    'D': np.random.normal(100, 10, size=(N)).tolist()
})

如果想要遍历 DataFrame 的每一行，我们下列函数：
1) items()或者iteritems()：以键值对 (key,value) 的形式遍历；--->遍历列
2) iterrows()：以 (row_index,row) 的形式遍历行;
3) itertuples()：使用已命名元组的方式对行遍历。


for key,value in df.items():
    print(key)
    print(value.values)  #value是series对象，通过values得到列表
    
#注意i为元组类型，i[0]为行标签。i[1]为行数据为series类型
for i in df.iterrows():
	print(i[1].values)
        
#Iterable[tuple[Any, ...]]，返回一个元组类型
for i in df.itertuples():
	print(i[1:])        
```

## pandas排序

```
Pands 提供了两种排序方法，分别是按标签排序和按数值排序。
sort_index()

unsorted_df = pd.DataFrame(np.random.randn(10, 2), index=[1, 6, 4, 2, 3, 5, 9, 8, 0, 7], columns=['col2', 'col1'])
print(unsorted_df)
#False表示按标签降序排序，默认为True升序排序,axis=0 垂直方向 =1水平方向
df=unsorted_df.sort_index(ascending=False，axis=0)
print(df)

sort_values(by=列名) 提供了参数kind用来指定排序算法。这里有三种排序算法：
mergesort
heapsort
quicksort

unsorted_df = pd.DataFrame({'col1': [2, 1, 1, 1], 'col2': [1, 3, 2, 4]})
print(unsorted_df)
sorted_df = unsorted_df.sort_values(by='col1', kind='mergesort')
print(sorted_df)
```

## pandas去重

```
data = {
        'A': [1, 0, 1, 1],
        'B': [0, 2, 5, 0],
        'C': [4, 0, 4, 4],
        'D': [1, 0, 1, 1]
    }
df = pd.DataFrame(data=data)
df=df.drop_duplicates() 
print(df) #会留A

# keep=False删除所有重复项，默认保留第一次出现的重复项 ==>A,D均删除

#指定第1列，去除所有重复项 0 2 0 0后面两个0会被去掉
df2=df.drop_duplicates(subset=[1])
print(df2)
```

## pands设置数据显示格式

| 函数名称        | 说明                                                     |
| --------------- | -------------------------------------------------------- |
| get_option      | 获取解释器的默认参数值。                                 |
| set_option      | 更改解释器的默认参数值。                                 |
| reset_option    | 解释器的参数重置为默认值。                               |
| describe_option | 输出参数的描述信息。                                     |
| option_context  | 临时设置解释器参数，当退出使用的语句块时，恢复为默认值。 |

| 参数                      | 说明                                                         |
| ------------------------- | ------------------------------------------------------------ |
| display.max_rows          | 最大显示行数，超过该值用省略号代替，为None时显示所有行。     |
| display.max_columns       | 最大显示列数，超过该值用省略号代替，为None时显示所有列。     |
| display.expand_frame_repr | 输出数据宽度超过设置宽度时，表示是否对其要折叠，False不折叠，True要折叠。 |
| display.max_colwidth      | 单列数据宽度，以字符个数计算，超过时用省略号表示。           |
| display.precision         | 设置输出数据的小数点位数。                                   |
| display.width             | 数据显示区域的宽度，以总字符数计算。                         |
| display.show_dimensions   | 当数据量大需要以truncate（带引号的省略方式）显示时，该参数表示是否在最后显示数据的维数，默认 True 显示，False 不显示。 |

## pandas统计高级函数

### 统计函数

```
1.百分比变化

s = pd.Series([1, 2, 3, 4, 5, 4]) 
#该函数将每个元素与其前一个元素进行比较，并计算前后数值的百分比变化
#0    NaN       第一个为NaN，后面为(当前元素-前一个元素)/前一个元素
#1    1         (2-1)/1
#2    1/2		(3-2)/2
#3    1/3		(4-3)/3
#4    1/4		(5-4)/4
#5   -1/5		(4-5)/5
print(s.pct_change())

2.协方差和相关系数
对于计算两个series对象的线性相关度
对于DataFrame将计算所有列之间的协方差
s = pd.Series([1, 2, 3, 4, 5, 4])
s2 = pd.Series([2, 3, 4, 5, 6, 5])

print(s.cov(s2))#计算协方差
print(s.cov(s2)/(s.std()*s2.std()))	#计算相关系数为1
print(s.corr(s2))					#同上

3.rank排名
s = pd.Series([1, 2, 3, 4, 5, 4])
print(s.rank())
如果序列中包含两个相同的的元素值，那么会为其分配两者的平均排名
输出结果如下：
0    1.0
1    2.0
2    3.0
3    4.5
4    6.0
5    4.5
rank() 提供了 method 参数，可以针对相同数据，进行不同方式的排名。如下所示：
average：默认值，如果数据相同则分配平均排名；
min：给相同数据分配最低排名；
max：给相同数据分配最大排名；
first：对于相同数据，根据出现在数组中的顺序进行排名。

rank() 有一个ascening参数， 默认为 True 代表升序；如果为 False，则表示降序排名（将较大的数值分配给较小的排名）。
如
print(s.rank(method="max",ascending=False))
```

### 窗口函数

```
rolling
参数名称			说明
window			默认值为 1，表示窗口的大小，也就是观测值的数量，
min_periods		表示窗口的最小观察值，默认与 window 的参数值相等。
# 每4个数求求一次和
s = pd.Series([1, 2, 3, 4, 5, 4])
print(s.rolling(window=4,min_periods=1).sum())
结果如下：
0     1.0
1     3.0
2     6.0
3    10.0
4    14.0
5    16.0

expanding() 又叫扩展窗口函数，扩展是指由序列的第一个元素开始，逐个向后计算元素的聚合值。
s = pd.Series([1, 2, 3, 4, 5, 4])
print(s.expanding(min_periods=2).sum())
0     NaN
1     3.0
2     6.0
3    10.0
4    15.0
5    19.0

ewm（全称 Exponentially Weighted Moving）表示指数加权移动。ewn() 函数先会对序列元素做指数加权运算，其次计算加权后的均值。该函数通过指定 com、span 或者 halflife 参数来实现指数加权移动。

背景
------------------------------------------------------------------
指数加权平均，也称为指数平滑，是一种用于时间序列数据的平滑技术。它最初是由物理学家欧内斯特·卡尔曼（Ernest Kalman）开发的，用于飞行器的导航系统中。指数加权平均可以用于处理时间序列中的噪声、趋势和周期性变化，以提取数据的趋势和周期性成分。

指数加权平均的基本思想是，对于一个时间序列的数据点，使用当前数据点和之前所有数据点的加权平均来估计下一个数据点。这里的加权是指使用指数函数对数据点进行加权，使得离当前时间点越近的数据点的权重越大，离当前时间点越远的数据点的权重越小。
--------------------------------------------------------------------
def ewm(
        self,
        com: float | None = None,
        span: float | None = None,
        halflife: float | TimedeltaConvertibleTypes | None = None,
        alpha: float | None = None,
        min_periods: int | None = 0,
        adjust: bool_t = True,
        ignore_na: bool_t = False,
        axis: Axis = 0,
        times: str | np.ndarray | DataFrame | Series | None = None,
        method: str = "single",
    )
    
    

s = pd.Series([1, 2, 3, 4, 5, 4])
s1=s.ewm(alpha=0.5).sum()
df=pd.DataFrame({"观测值":s,"预测值":s1})
#是否使用Unicode东亚宽度来计算显示文本宽度 -->解决列名和值不对应情况
pd.set_option('display.unicode.east_asian_width', True)
print(df)

结果
   观测值   预测值
0       1  1.00000			没有前一个数，默认为本身即1
1       2  2.50000			s=0.5*2+0.5*(1+2)  -->因为是sum故为当前值加上上一个预测值
2       3  4.25000			s=0.5*3+0.5*(2.5+3)
3       4  6.12500			s=0.5*4+0.5*(4.25+4)
4       5  8.06250			s=0.5*5+0.5*(6.125+5)
5       4  8.03125			s=0.5*4+0.5*(8.0625+4)
```



![image-20230321155410154](.\images\image-20230321155410154.png)

### 聚合函数

```
窗口函数可以与聚合函数一起使用，聚合函数指的是对一组数据求总和、最大值、最小值以及平均值的操作
aggregate()

df = pd.DataFrame([
        [1, 1, 1, 1, 2, 2],
        [1, 1, 1, 2, 2, 2],
        [1, 1, 2, 2, 2, 2],
        [1, 2, 2, 2, 2, 2]
    ])
r = df.rolling(window=3, min_periods=1)
# 使用 aggregate()聚合操作
print(r.aggregate(np.sum))
print(r[0].sum())
print(r[0].aggregate([np.sum,np.mean,np.min,np.max]))--->对第0列应用多个函数
```

## pandas缺失值处理

```
1.检查缺失值
Pandas 提供了 isnull() 和 notnull() 两个函数，它们同时适用于 Series 和 DataFrame 对象
2.清理并填充缺失值
a.用标量值替换NaN值
fillna(0)

method设置填充方式
pad/ffill：向前填充值；
bfill/backfill：向后填充值；
df = pd.DataFrame([
        [1, 1, None, 1, 2, 2],
        [1, 1, 1, None, 2, 2],
        [1, None, 2, 2, 2, 2],
        [1, 2, 2, 2, 2, 2]
    ])
print(df)
print(df.fillna(0))
print(df.fillna(method='ffill'))
b.使用replace替换通用值
print(df.replace({2:1}))  #把2换成1

3.删除缺失值
df.dropna()#有缺失值的行将被删除
```

## pandas 分组操作

```
df = pd.DataFrame({'种类': ['水果', '水果', '水果', '蔬菜', '蔬菜', '肉类', '肉类'],
                       '产地': ['朝鲜', '中国', '缅甸', '中国', '菲律宾', '韩国', '中国'],
                       '类型': ['橘子', '苹果', '哈密瓜', '番茄', '椰子', '鱼肉', '牛肉'],
                       '数量': [3, 5, 5, 3, 2, 15, 9],
                       '价格': [2, 5, 12, 3, 4, 18, 20]})

def get_rows(df, n):
return df.iloc[:n, :]
# 分组后的组名作为行索引
print(df.groupby('种类').groups) #以种类为分组 分为三类
print(df.groupby('种类').transform(np.sum)) #以种类为分组，对每一类数值求和
print(df.groupby('种类').apply(get_rows, n=1))#以种类为分组，返回每一类第一项
##以种类为分组，过滤价格大于15的类别
print(df.groupby('种类').filter(lambda x:all(False if i>15 else True for i in x['价格'])))

分组对象应用聚合函数
df.groupby('种类').价格.agg([min,max])
```

## pandas合并操作

```
merge() 函数的法格式如下：
pd.merge(left, right, how='inner', on=None, left_on=None, right_on=None,left_index=False, right_index=False, sort=True,suffixes=('_x', '_y'), copy=True)

参数说明，如下表所示：

参数名称	说明
left/right	两个不同的 DataFrame 对象。
on	指定用于连接的键（即列标签的名字），该键必须同时存在于左右两个 DataFrame 中，如果没有指定，并且其他参数也未指定， 那么将会以两个 DataFrame 的列名交集做为连接键。
left_on	指定左侧 DataFrame 中作连接键的列名。该参数在左、右列标签名不相同，但表达的含义相同时非常有用。
right_on	指定左侧 DataFrame 中作连接键的列名。
left_index	布尔参数，默认为 False。如果为 True 则使用左侧 DataFrame 的行索引作为连接键，若 DataFrame 具有多层
索引(MultiIndex)，则层的数量必须与连接键的数量相等。
right_index	布尔参数，默认为 False。如果为 True 则使用左侧 DataFrame 的行索引作为连接键。
how	要执行的合并类型，从 {'left', 'right', 'outer', 'inner'} 中取值，默认为“inner”内连接。
sort	布尔值参数，默认为True，它会将合并后的数据进行排序；若设置为 False，则按照 how 给定的参数值进行排序。
suffixes	字符串组成的元组。当左右 DataFrame 存在相同列名时，通过该参数可以在相同的列名后附加后缀名，默认为('_x','_y')。
copy	默认为 True，表示对数据进行复制。

使用how参数合并
通过how参数可以确定 DataFrame 中要包含哪些键，如果在左表、右表都不存的键，那么合并后该键对应的值为 NaN。为了便于大家学习，我们将 how 参数和与其等价的 SQL 语句做了总结：
Merge方法	等效 SQL	描述
left	LEFT OUTER JOIN	使用左侧对象的key
right	RIGHT OUTER JOIN	使用右侧对象的key
outer	FULL OUTER JOIN	使用左右两侧所有key的并集
inner	INNER JOIN	使用左右两侧key的交集


left = pd.DataFrame({
        'id': [1, 2, 3, 4],
        'Name': ['Smith', 'Maiki', 'Hunter', 'Hilen'],
        'subject_id1': ['sub1', 'sub2', 'sub4', 'sub6']})
right = pd.DataFrame({
        'id': [1, 2, 3, 4],
        'Name': ['Smith', 'Albert', 'Tony', 'Hilen'],
        'subject_id2': ['sub2', 'sub4', 'sub3', 'sub6']})
print(left)
print(right)
print(pd.merge(left, right, on="id"))
print(pd.merge(left,right,on=["id","Name"]))
print(pd.merge(left,right,left_on="subject_id1",right_on="subject_id2"))
print(pd.merge(left,right,on=["id","Name"],how="left"))
print(pd.merge(left,right,on=["id","Name"],how="outer"))
```

## Pandas concat连接操作

```
Pandas 通过 concat() 函数能够轻松地将 Series 与 DataFrame 对象组合在一起，函数的语法格式如下：
 pd.concat(objs,axis=0,join='outer',join_axes=None,ignore_index=False)

参数说明如下所示：
参数名称	说明
objs	一个序列或者是Series、DataFrame对象。
axis	表示在哪个轴方向上（行或者列）进行连接操作，默认 axis=0 表示行方向。
join	指定连接方式，取值为{"inner","outer"}，默认为 outer 表示取并集，inner代表取交集。
ignore_index	布尔值参数，默认为 False，如果为 True，表示不在连接的轴上使用索引。
join_axes	表示索引对象的列表。

s1=pd.Series([1,2,3,4,5])
s2=pd.Series([6,7,8,9,0])
print(pd.concat([s1,s2]))
df1=pd.DataFrame([[1,2,3],[4,5,6]])
df2=pd.DataFrame([[1,1,1],[2,2,2]])
print(pd.concat([df1,df2]))
print(pd.concat([df1,df2],axis=1))
```

## Pandas时间序列

```
1.创建时间戳
datetime1=pd.Timestamp('2020-01-01')
2.创建时间范围
print(datetime1)
print(pd.date_range("9:00", "18:10", freq="30min").time)
print(pd.date_range("9:00", "18:10", freq="30min").values)
#周期为10产生十个日期，频率为 "D"， 也就是“天”
print(pd.date_range('12/15/2020', periods=10,freq="D"))
3.将 series 或 list 转换为日期对象
print(pd.to_datetime(pd.Series(['Jun 3, 2020', '2020-12-10'])))
#periods

4.创建工作日日期
bdate_range() 表示创建工作日的日期范围，它与 date_range() 不同，它不包括周六、周日。
print(pd.bdate_range('12/15/2020', periods=10))#默认freq="B"

频率
别名	描述				别名			描述
B	工作日频率			BQS			工作季度开始频率
D	日历日频率			A			年终频率
W	每周频率			BA			工作年度结束频率
M	月末频率			BAS			工作年度开始频率
SM	半月结束频率		   BH			营业时间频率
BM	工作月结束频率		   H			小时频率
MS	月开始频率		   T,min			每分钟频率
SMS	半月开始频率		   S			每秒钟频率
BMS	工作月开始频率		  L,ms			毫秒
Q	季末频率		    U,us			微妙
BQ	工作季度结束频率	  N				纳秒
QS	季度开始频率	 	 


datetime
日期格式化符号
符号	说明
%y	两位数的年份表示（00-99）
%Y	四位数的年份表示（000-9999）
%m	月份（01-12）
%d	月内中的一天（0-31）
%H	24小时制小时数（0-23）
%I	12小时制小时数（01-12）
%M	分钟数（00=59）
%S	秒（00-59）
%a	本地英文缩写星期名称
%A	本地英文完整星期名称
%b	本地缩写英文的月份名称
%B	本地完整英文的月份名称
%w	星期（0-6），星期天为星期的开始
%W	一年中的星期数（00-53）星期一为星期的开始
%x	本地相应的日期表示
%X	本地相应的时间表示
%Z	当前时区的名称
%U	一年中的星期数（00-53）星期天为星期的开始
%j	年内的一天（001-366）
%c	本地相应的日期表示和时间表示

Python 内置的 strptime() 方法能够将字符串日期转换为 datetime 类型

from datetime import datetime
#将日期定义为字符串    
date_str1 = 'Wednesday, July 18, 2020' 
date_str2 = '18/7/20' 
date_str3 = '18-07-2020'  
#将日期转化为datetime对象 
dmy_dt1 = datetime.strptime(date_str1, '%A,%B%d,%Y') 
dmy_dt2 = datetime.strptime(date_str2, '%d/%m/%y') 
dmy_dt3 = datetime.strptime(date_str3, '%d-%m-%Y')  
#处理为相同格式，并打印输出
print(dmy_dt1) 
print(dmy_dt2) 
print(dmy_dt3) 
```

## pandas随机选择样本

```
sample() 函数的语法格式如下：
DataFrame.sample(n=None, frac=None, replace=False, weights=None, random_state=None, axis=None)

参数名称			参数说明
n				表示要抽取的行数。
frac			表示抽取的比例，比如 frac=0.5，代表抽取总体数据的50%。
replace			布尔值参数，表示是否以有放回抽样的方式进行选择，默认为 False，取出数据后不再放回。
weights			可选参数，代表每个样本的权重值，参数值是字符串或者数组。
random_state	可选参数，控制随机状态，默认为 None，表示随机数据不会重复；若为 1 表示会取得重复数据。
axis			表示在哪个方向上抽取数据(axis=1 表示列/axis=0 表示行)。


info = pd.DataFrame({'data1': [2, 6, 8, 0], 'data2': [2, 5, 0, 8], 'data3': [12, 2, 1, 8]}, index=['John', 'Parker', 'Smith', 'William'])
info
#随机抽取3个数据
info['data1'].sample(n=3)
#总体的50%
info.sample(frac=0.5, replace=True)
#data3序列为权重值，并且允许重复数据出现
info.sample(n=2, weights='data3', random_state=1)
```

## pandas数据重采样

```
数据重采样是将时间序列从一个频率转换至另一个频率的过程，它主要有两种实现方式，分别是降采样和升采样，降采样指将高频率的数据转换为低频率，升采样则与其恰好相反

降采样
#将一百天变为四个月求和
rng = pd.date_range('1/1/2021', periods=100, freq='D')
ts = pd.Series(np.random.randn(len(rng)), index=rng)
print(ts.resample("M").sum())

升采样并填充缺失值
asfreq() 方法不仅能够实现频率转换，还可以保留原频率对应的数值
rng = pd.date_range('1/1/2021', periods=5, freq='3D')
print(rng)
ts = pd.Series(np.random.randn(len(rng)), index=rng)
print(ts.resample('D').asfreq())
# 使用ffill处理缺失值
print(ts.resample('D').asfreq().ffill())
```

## pandas分类对象

```
创建分类对象
方式一：
s = pd.Series(['a', 'b', 'c', 'a', 'b', 'c'], dtype="category")
print(s.cat.categories)

方式二：
cat = pd.Categorical(['a', 'b', 'c', 'a', 'b', 'c'])
print(cat)
添加分类对象
s=s.cat.add_categories('d')
print(s.cat.categories)
删除分类对象
s = s.cat.remove_categories('a')
print(s.cat.categories)
```

## pandas读写文件

```
当使用 Pandas 做数据分析的时，需要读取事先准备好的数据集，这是做数据分析的第一步。Panda 提供了多种读取数据的方法：
read_csv() 用于读取文本文件
read_json() 用于读取 json 文件
read_sql_query() 读取 sql 语句的

pandas.read_csv(filepath_or_buffer, sep=',', delimiter=None, header='infer',names=None, index_col=None, usecols=None)
header=None==>则第一行数据不为列名
header='infer'===>第一行数据为列名


文件内容如下：
ID,Name,Age,City,Salary
1,Jack,28,Beijing,22000
2,Lida,32,Shanghai,19000
3,John,43,Shenzhen,12000
4,Helen,38,Hengshui,3500

df = pd.read_csv('./hrd.csv',index_col='ID')
#在CSV文件中指定了一个列，然后使用index_col可以实现自定义索引。
print(df)
print(df.dtypes)
#skiprows参数表示跳过指定的行数
df2 = pd.read_csv("./hrd.csv",header=None,skiprows=2)
print(df2)


--------------写---------------------
# to_csv() 函数用于将 DataFrame 转换为 CSV 数据,path_or_buf指定文件路径或缓冲区，若指定返回None,否则以字符串形式返回,sep指定分隔符
csv_data=df.to_csv(path_or_buf="./1.csv",sep=" ")
print(csv_data)


```

## excel读写操作

### 读

```
pd.read_excel(io, sheet_name=0, header=0, names=None, index_col=None,              usecols=None, squeeze=False,dtype=None, engine=None, converters=None, true_values=None, false_values=None, skiprows=None, nrows=None, na_values=None, parse_dates=False, date_parser=None, thousands=None, comment=None, skipfooter=0, convert_float=True, **kwds)
```

| 参数名称   | 说明                                                         |
| ---------- | ------------------------------------------------------------ |
| io         | 表示 Excel 文件的存储路径。                                  |
| sheet_name | 要读取的工作表名称。                                         |
| header     | 指定作为列名的行，默认0，即取第一行的值为列名；若数据不包含列名，则设定 header = None。若将其设置 为 header=2，则表示将前两行作为多重索引。 |
| names      | 一般适用于Excel缺少列名，或者需要重新定义列名的情况；names的长度必须等于Excel表格列的长度，否则会报错。 |
| index_col  | 用做行索引的列，可以是工作表的列名称，如 index_col = '列名'，也可以是整数或者列表。 |
| usecols    | int或list类型，默认为None，表示需要读取所有列。              |
| squeeze    | boolean，默认为False，如果解析的数据只包含一列，则返回一个Series。 |
| converters | 规定每一列的数据类型。                                       |
| skiprows   | 接受一个列表，表示跳过指定行数的数据，从头部第一行开始。     |
| nrows      | 需要读取的行数。                                             |
| skipfooter | 接受一个列表，省略指定行数的数据，从尾部最后一行开始。       |

### 写

```
DataFrame.to_excel(excel_writer, sheet_name='Sheet1', na_rep='', float_format=None, columns=None, header=True, index=True, index_label=None, startrow=0, startcol=0, engine=None, merge_cells=True, encoding=None, inf_rep='inf', verbose=True, freeze_panes=None)  
```

| 参数名称     | 描述说明                                                     |
| ------------ | ------------------------------------------------------------ |
| excel_wirter | 文件路径或者 ExcelWrite 对象。                               |
| sheet_name   | 指定要写入数据的工作表名称。                                 |
| na_rep       | 缺失值的表示形式。                                           |
| float_format | 它是一个可选参数，用于格式化浮点数字符串。                   |
| columns      | 指要写入的列。                                               |
| header       | 写出每一列的名称，如果给出的是字符串列表，则表示列的别名。   |
| index        | 表示要写入的索引。                                           |
| index_label  | 引用索引列的列标签。如果未指定，并且 hearder 和 index 均为为 True，则使用索引名称。如果 DataFrame 使用 MultiIndex，则需要给出一个序列。 |
| startrow     | 初始写入的行位置，默认值0。表示引用左上角的行单元格来储存 DataFrame。 |
| startcol     | 初始写入的列位置，默认值0。表示引用左上角的列单元格来储存 DataFrame。 |
| engine       | 它是一个可选参数，用于指定要使用的引擎，可以是 openpyxl 或 xlsxwriter。 |

## pandas索引

```
info = pd.DataFrame({'Name': ['Parker', 'Terry', 'Smith', 'William'],  'Year': [2011, 2009, 2014, 2010], 'Leaves': [10, 15, 9, 4]})
#设置Name为行索引
print(info.set_index('Name'))
#使用 reset_index() 来恢复初始行索引
print(info.reset_index())


分层索引（Multiple Index）是 Pandas 中非常重要的索引类型，它指的是在一个轴上拥有多个（即两个以上）索引层数，这使得我们可以用低维度的结构来处理更高维的数据。比如，当想要处理三维及以上的高维数据时，就需要用到分层索引。

#标签存在多重情况
df = pd.DataFrame(np.arange(1, 13).reshape((4, 3)),
                      index=[['a', 'a', 'b', 'b'], [1, 2, 1, 2]],
                      columns=[['Jack', 'Jack', 'Helen'],
                               ['Python', 'Java', 'Python']])
print(df)
df.index.names = ['key1', 'key2']
df.columns.names = ['name', 'course']
print(df.sum(level='key2'))
print(df.sum(level="course", axis=1))

```

## pandas条件查询

```
df=pd.read_csv("./hrd.csv")  
print(df)                    
print(df[df['Salary']>10000])
输出如下：
   ID   Name  Age      City  Salary
0   1   Jack   28   Beijing   22000
1   2   Lida   32  Shanghai   19000
2   3   John   43  Shenzhen   12000
3   4  Helen   38  Hengshui    3500

   ID  Name  Age      City  Salary
0   1  Jack   28   Beijing   22000
1   2  Lida   32  Shanghai   19000
2   3  John   43  Shenzhen   12000
```

## pandas布尔索引

```
dict = {'name':["Smith", "William", "Phill", "Parker"],
           'age': ["28", "39", "34", "36"]}
info = pd.DataFrame(dict, index = [True, True, False, True])
#返回所有为 True的数据
print(info.loc[True])


isin() 也会返回一个布尔序列，它用来判断元素值是否包含在的 Series 序列中。
s = pd.Series(list('abc'))
s = s.isin(['a', 'c', 'e'])
print(s)
0    True
1    False
2    True
dtype: bool
```

