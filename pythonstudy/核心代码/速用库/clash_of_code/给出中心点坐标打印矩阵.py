2 2-->中心点坐标为(2,2)

*   *  -->5  长度
 * *   -->4
  *    -->3
 * *   -->4
*   *  -->5


x, y = [int(i) for i in input().split()]

l = [[" " for j in range(2*y+1)] for i in range(2*x+1)]

for i in range(2*x+1):
    for j in range(2*y+1):
        if i==j or i+j==2*y:
            l[i][j]="*"

for i in range(2*x+1):
    s = "".join([j for j in l[i]])
    print(s.rstrip())