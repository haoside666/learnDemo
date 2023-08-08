import numpy as np
import matplotlib.pyplot as plt

def test():
    x=np.linspace(0,np.pi,30)
    plt.plot(x,np.sin(x),"--*r")
    plt.xlabel("x")
    plt.ylabel("f(x)=sin(x)")
    plt.title("666")
    plt.show()

def test2():
    x=np.linspace(-3,3,30)
    fig=plt.figure(figsize=(12,6))
    ax=fig.add_axes([0.1,0.1,0.8,0.8])
    ax.plot(x,x**2,"b")
    ax.set_xlabel("x")
    ax.set_ylabel("f(x)=x^2")
    ax.set_title("数学图")
    plt.show()

def test3():
    x1 = [1, 16, 30, 42, 55, 68, 77, 88]
    x2 = [1, 6, 12, 18, 28, 40, 52, 65]
    y = [1, 4, 9, 16, 25, 36, 49, 64]
    fig=plt.figure()
    ax=fig.add_axes([0.1,0.1,0.8,0.8])
    a1=ax.plot(x1,y,"-dy")
    a2=ax.plot(x2,y,"--og")
    ax.set_title("666")
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.legend(handles=[*a2,*a1],labels=["first","second"],loc="lower right")
    plt.show()

def test4():
    x=np.arange(5)
    plt.subplot(121)
    plt.plot(x,x+2,'b')
    plt.subplot(122)
    plt.plot(x, x * 2, '-*r')
    plt.show()

def test5():
    x=np.linspace(-3,3,30)
    fig=plt.figure(figsize=(12,6))
    ax1=fig.add_subplot(111)
    ax1.plot(x,x**2,"c")
    ax2=fig.add_subplot(232)
    ax2.plot(x,np.sin(x),"m")
    plt.show()

def test6():
    x = np.arange(5)
    fig,ax=plt.subplots(2)
    # fig,ax=plt.subplots(2,2)
    print(ax)
    print(*ax)
    ax[0].plot(x, x + 2)
    # ax[0,1].plot(x, x + 2)
    ax[1].plot(x, x * 2)
    # ax[1,1].plot(x, x * 2)
    plt.show()

def test7():
    x=np.arange(1,10)
    a1=plt.subplot2grid((3,3),(0,0),2,2)
    a2=plt.subplot2grid((3,3),(2,0),1,2)
    a3=plt.subplot2grid((3,3),(0,2),3,1)
    a1.plot(x,x**2)
    a2.plot(x,np.exp(x))
    a3.plot(x,np.log(x))
    plt.show()

def test8():
    x = [5, 8, 12, 14, 16, 18, 20]
    y1 = [18, 21, 29, 31, 26, 24, 20]
    y2 = [15, 18, 24, 30, 31, 25, 24]
    # 绘制折线图，添加数据点，设置点的大小
    # * 表示绘制五角星；此处也可以不设置线条颜色，matplotlib会自动为线条添加不同的颜色
    plt.plot(x, y1, 'r', marker='*', markersize=10)
    plt.plot(x, y2, 'b', marker='*', markersize=10)
    plt.title('温度对比折线图')  # 折线图标题
    plt.xlabel('时间(h)')  # x轴标题
    plt.ylabel('温度(℃)')  # y轴标题
    # 给图像添加注释，并设置样式
    for a, b in zip(x, y1):
        plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
    for a, b in zip(x, y2):
        plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
    # 绘制图例
    plt.legend(['第一天', '第二天'])
    plt.ylim(10,35)
    plt.xlim(0,25)
    plt.xticks([5,8,12,14,16,18,20],["5点","8点", "12点", "14点", "16点", "18点", "20点"])
    # 显示图像
    plt.show()

def test9():
    fig = plt.figure(figsize=[12, 6])
    a1 = fig.add_axes([0.1, 0.1, 0.8, 0.8])
    x = np.arange(1, 11)
    l1 = a1.plot(x, np.exp(x))
    a1.set_ylabel('exp')
    a2 = a1.twinx()
    l2 = a2.plot(x, np.log(x), 'ro-')
    a2.set_ylabel('log')
    fig.legend(handles=[*l1, *l2], labels=('exp', 'log'), loc=(0.1, 0.8))
    plt.show()

def test10():
    x=[23,24,46,36,15,9]
    fig=plt.figure()
    ax=fig.add_axes([0.1,0.1,0.8,0.8])
    langs=["dog","cat","cow","sheep","targe","lion"]
    ax.pie(x,labels=langs, autopct='%1.2f%%')
    ax.set_title("动物数目分布图")
    plt.show()

def test11():
    labels = 'Geek1', 'Geek2', 'Geek3', 'Geek4', 'Geek5'
    sizes = [95, 230, 145, 40, 65]
    explode = (0, 0.1, 0, 0, 0)

    fig1, ax1 = plt.subplots(1,2,figsize=(12,6))
    ax1[0].pie(sizes, labels=labels,
            autopct='% 1.0f %%',
            shadow=True, startangle=90)
    ax1[0].axis('image')
    ax1[0].set_title('matplotlib.axes.Axes.axis() \
    Example\n', fontsize=14, fontweight='bold')

    ax1[1].pie(sizes, explode=explode,labels=labels,
               autopct='% 1.0f %%',
               shadow=True, startangle=90)
    ax1[1].axis('scaled')
    ax1[1].set_title('matplotlib.axes.Axes.axis() \
        Example\n', fontsize=14, fontweight='bold')
    plt.show()


def test12():
    girls_grades = [89, 90, 70, 89, 100, 80, 90, 100, 80, 34]
    boys_grades = [30, 29, 49, 48, 100, 48, 38, 45, 20, 30]
    grades_range = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    fig=plt.figure(figsize=(12,6))
    ax=fig.add_axes([0.1,0.1,0.8,0.8])
    ax.scatter(grades_range,girls_grades,color="r")
    ax.scatter(grades_range,boys_grades,color="b")
    ax.legend(labels=["girl","boy"])
    plt.show()


if __name__=="__main__":
    test12()