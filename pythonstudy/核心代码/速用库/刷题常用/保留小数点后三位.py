a, b = [float(i) for i in input().split()]
c, d = [float(i) for i in input().split()]

det=a*d-b*c
if det==0:
    print("IMPOSSIBLE")
else:
    print('{:.3f} {:.3f}'.format(d/det, -b/det))
    print('{:.3f} {:.3f}'.format(-c/det, a/det))


"{:.0f}".format(12345678.40)--->四舍五入
