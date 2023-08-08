
# print特定格式
def fun1():
    print('{}网址： "{}!"'.format('菜鸟教程', 'www.runoob.com'))
    print('站点列表 {0}, {1}, 和 {other}。'.format('Google', 'Runoob', other='Taobao'))
    # 在:后传入一个整数, 可以保证该域至少有这么多的宽度。 用于美化表格时很有用。
    table = {'Google': 1, 'Runoob': 2, 'Taobao': 3}
    for name, number in table.items():
        print('{0:10} ==> {1:10d}'.format(name, number))
    # 传入字典,修改格式
    table = {'Google': 1, 'Runoob': 2, 'Taobao': 3}
    print('Runoob: {Runoob}; Google: {Google}; Taobao: {Taobao}'.format(**table))

if __name__=="__main__":
    fun1()