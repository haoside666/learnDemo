1 1 1 3 5 9.........


求第index位斐波拉契数列值（从0开始）
l = [1, 1, 1]
for i in range(2, index):
    l.append(l[i]+l[i-1]+l[i-2])
print(l[index])


