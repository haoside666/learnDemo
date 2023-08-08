### 导入库

```
import numpy as np
```

### 1.创建

```
创建一个2*2的全0数组,类型为i
1.arr=np.zeros((2,2),"i")
类型如下:
i - 整数
b - 布尔
u - 无符号整数
f - 浮点
c - 复合浮点数
m - timedelta
M - datetime
O - 对象
S - 字符串
U - unicode 字符串
V - 固定的其他类型的内存块 ( void )
创建一个2*3的全空格数组
2.arr=np.full((2,3)," ")
创建一个从0到8的一维格数组
3.arr=np.arange(1,10)
4.与arange类似不过前者使用步长,后者指明数目,此外结束位置也有差异
linspace(start, stop, num=50,endpoint=True)==>为False不包含结束值
	在指定的间隔[“start”,“stop”]内均匀地返回数字。
	返回“num”个等间距的样本。
arr=np.linespace(1,9,9)
5.np.logspace(1.0,2.0, num = 10) ===>创建等比数列,linspace是创建等比数列
6.arr = np.array([2,3,4])
```

![img](.\images\29625b4d98bdef325495b21d0b0ac5ec.png)

### 2.索引

```
arr = np.array([[1, 2, 3], [4, 5, 6]])
print(arr[0,1:3]) #[2 3]相当于arr[0][1:3]
```

### 3.切片

```
arr=np.arange(30)
arr=arr.reshape(5,6)
print(arr)
print(arr[0:,::2])--->只保留偶数
```

### 4.条件

```
arr=np.arange(30)
arr=arr.reshape(5,6)
print(np.where(arr%2==0,'a','b'))#整除2输出'a',否则输出'b'
print(type(np.where(arr%2==0)))  #输出满足条件的坐标,类型为元组类型
print(arr[np.where(arr%2==0)])-->打印满足条件的值

给定一个字符串求#的个数,用空格分开
s = " ####  ## ###  ####################  ## "
arr = np.array(re.split(r"[ ]+", s))
print(*map(lambda x:len(x),arr[np.where(arr!="")]))
```

### 5.维度变换

```
reshape-->不修改向量本身
resize-->修改向量本身
arr=np.arange(30)
brr=arr.reshape(5,6)
print(arr,brr)
```

![img](.\images\d4b651dcf70ac84af76dc1744f8d83e2.png)

### 6.numpy数值计算

```
np.argmin--->获得最小值的下标
np.argmax--->获得最大值的下标
np.min--->获得最小值
np.max--->获得最大值
np.argsort--->获得排序后的下标
np.sort--->进行排序
np.median-->求中位数
矩阵对应元素相乘与矩阵点积
arr=np.array([
        [1,2],
        [3,4]
    ])
brr = np.array([
        [1, 1],
        [2, 2]
    ])
print(arr*brr)
print(np.dot(arr,brr))
-------------------------------------
[[1 2]
 [6 8]]
[[ 5  5]
 [11 11]]
-------------------------------------

np.linalg.det(arr)--->求矩阵的行列式
np.linalg.inv(arr)--->求矩阵的逆矩阵(前提可逆)
np.linalg.eig(arr)-->求矩阵的特征值和特征向量
```

![img](.\images\4911ec0777867450612b3d3d34fc8230.png)

### 7.矩阵合并

```
矩阵的合并可以通过numpy中的hstack方法和vstack方法实现
arr=np.array([
        [1,2],
        [3,4]
    ])
brr = np.array([
        [1, 1],
        [2, 2]
    ])
print(np.vstack((arr,brr)))  --->v垂直,按行加
print(np.hstack((arr,brr)))  --->h水平,按列加
vstack
[[1 2]
 [3 4]
 [1 1]
 [2 2]]
____________________
hstack
[[1 2 1 1]
 [3 4 2 2]]
```

### 8.字符串序列化

```
a = "abcdef"
b = np.fromstring(a,dtype=np.int8) # 因为一个字符为8位，所以指定dtype为np.int8
print(b) # 返回 [ 97  98  99 100 101 102]
```

### 9.遍历

```
1.原始遍历
arr=np.array([
        [1,2,3],
        [4,5,6]
])
x,y=arr.shape
for i in range(x):
	for j in range(y):
		print(arr[i][j])
		
2.遍历2.0
for x in arr:
        for y in x:
            print(y)

3.遍历3.0
for x in np.nditer(arr):
        print(x)
        
使用 ndenumerate() 进行枚举迭代
a = np.array([[1, 2], [3, 4]])
for index, x in np.ndenumerate(a):
	print(index, x)

(0, 0) 1
(0, 1) 2
(1, 0) 3
(1, 1) 4
```

### 10.数组过滤

```
arr = np.array([61, 62, 63, 64, 65])
x = [True, False, True, False, True]
newarr = arr[x]
print(newarr)
--------------------------------------------
arr = np.array([61, 62, 63, 64, 65])
filter_arr = arr > 62   ===>创建过滤器数组
newarr = arr[filter_arr]
print(filter_arr)
print(newarr)
```

### 11.随机数

```
#生成一个 0 到 100 之间的随机整数
x = np.random.randint(100)

random 模块的 rand() 方法返回 0 到 1 之间的随机浮点数
x = random.rand()
print(x)

生成有 3 行的 2-D 数组，每行包含 5 个从 0 到 100 之间的随机整数
x = random.randint(100, size=(3, 5))
print(x)

生成由数组参数（0和1）中的值组成的二维数组
x = random.choice([0,1], size=(3, 5))
print(x)
```



