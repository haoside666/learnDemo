import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# w: width of the building.
# h: height of the building.
w, h = [int(i) for i in input().split()]
n = int(input())  # maximum number of turns before game over.
x0, y0 = [int(i) for i in input().split()]
print(w,h,n,x0,y0,file=sys.stderr)

coord=["(1,0)","(1,1)","(0,1)","(-1,1)","(-1,0)","(-1,-1)","(0,-1)","(1,-1)"]
opp=["R", "DR", "D", "DL", "L", "UL","U", "UR"]
d=dict(zip(opp,coord))

point=[(0,w-1),(0,h-1)]

# game loop
while True:
    bomb_dir = input()  # the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
    print(bomb_dir,file=sys.stderr)
    pos=d[bomb_dir]
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)
    index=pos.find(",")
    dir_x=int(pos[1:index])
    dir_y=int(pos[index+1:-1])

    if dir_x==0:
        point[0]=(x0,x0)
    elif dir_x==1:
        point[0]=(x0,point[0][1])
    elif dir_x==-1:
        point[0]=(point[0][0],x0)
    
    if dir_y==0:
        point[1]=(y0,y0)
    elif dir_y==1:
        point[1]=(y0,point[1][1])
    elif dir_y==-1:
        point[1]=(point[1][0],y0)

    x0=x0+dir_x*math.ceil(abs(point[0][0]-point[0][1])/2)
    y0=y0+dir_y*math.ceil(abs(point[1][0]-point[1][1])/2)
        
    print(point,file=sys.stderr)
    # the location of the next window Batman should jump to.
    print(x0,y0)
