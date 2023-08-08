import pandas as pd


def test1():
    a = [1, 2, 3]
    myvar = pd.Series(a)
    print(myvar)


# 指定列数据来创建DataFrame
def test2():
    data = [['Google', 10], ['Runoob', 12], ['Wiki', 13]]
    df = pd.DataFrame(data, columns=['Site', 'Age'])
    print(df)


def test3():
    data = {'calories': [420, 380, 390], 'duration': [50, 40, 45]}
    df = pd.DataFrame(data)
    print(df.loc[0])
    print(df.loc[1])
    print(df.loc[[0, 1]])  # loc为根据行列索引访问数据


# 指定行索引值
def test4():
    data = {'calories': [420, 380, 390], 'duration': [50, 40, 45]}
    df = pd.DataFrame(data, index=['day1', 'day2', 'day3'])
    print(df)
    print(df.loc['day2'])


# 读入CSV文件并构建DataFrame
def test5():
    df = pd.read_csv('nba.csv')
    print(df)


# 将DataFrame保存成CSV文件
def test6():
    nme = ["Google", "Runoob", "Taobao", "Wiki"]
    st = ["www.google.com", "www.runoob.com", "www.taobao.com", "www.wikipedia.org"]
    ag = [90, 40, 80, 98]
    dict = {'name': nme, 'site': st, 'age': ag}
    df = pd.DataFrame(dict)
    print(df)
    df.to_csv('site.csv')


# 处理DataFrame数据
def test7():
    df = pd.read_csv('nba.csv')
    print(df.head(5))
    print(df.info())


# how = ‘any’：只要该行有一个空字段就删除,inplace = True：在原始数据上删除（如果为False则返回删除后的数据）

def test8():
    missing_values = ['n / a', '']
    df = pd.read_csv('property-data.csv', na_values=missing_values)  # 将'n / a' and 空换成NaN
    print(df)
    print("-------------------------------------------------------------")
    df.dropna(how='any', inplace=True)
    print(df.to_string())
    # df.fillna(12345, inplace = True) 将所有空值替换为12345


if __name__ == "__main__":
    # test1()
    # print("----------------------------------------------------------")
    # test2()
    # print("----------------------------------------------------------")
    # test3()
    # print("----------------------------------------------------------")
    # test4()
    # print("----------------------------------------------------------")
    # test5()
    # print("----------------------------------------------------------")
    # test6()
    # print("----------------------------------------------------------")
    # test7()
    print("----------------------------------------------------------")
    test8()
