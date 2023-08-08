方法一:
x, y, tx, ty = [int(i) for i in input().split()]

while True:
    remaining_turns = int(input())  # The remaining amount of turns Thor can move. Do not remove this line.
    s=""
    if ty>y:
        s+="N"
        ty-=1
    elif ty<y:
        s+="S"
        ty+=1
    
    if tx>x:
        s+="W"
        tx-=1
    elif tx<x:
        tx+=1
        s+="E"
    print(s)



方法二:坐标法
import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
# ---
# Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

# light_x: the X position of the light of power
# light_y: the Y position of the light of power
# initial_tx: Thor's starting X position
# initial_ty: Thor's starting Y position
light_x, light_y, initial_tx, initial_ty = [int(i) for i in input().split()]
d_x=light_x-initial_tx
d_y=light_y-initial_ty
b_x=1 if d_x>0 else -1
b_y=1 if d_y>0 else -1
n=min(abs(d_x),abs(d_y))
after_x=d_x-b_x*n
after_y=d_y-b_y*n
m=max(abs(after_x),abs(after_y))
after_b_x=0 if after_x ==0 else int(after_x/abs(after_x))
after_b_y=0 if after_y ==0 else int(after_y/abs(after_y))
coord=["(1,0)","(1,1)","(0,1)","(-1,1)","(-1,0)","(-1,-1)","(0,-1)","(1,-1)"]
opp=["E", "SE", "S", "SW", "W", "NW","N", "NE"]
co1="("+str(b_x) +","+str(b_y) +")"
co2="("+str(after_b_x) +","+str(after_b_y) +")"
dic=dict(zip(coord,opp))
s=[]
for i in range(n):
    s.append(dic[co1])
for i in range(m):
    s.append(dic[co2])
index=0
len1=len(s)
# game loop
while True:
    remaining_turns = int(input())  # The remaining amount of turns Thor can move. Do not remove this line.
    if index<len1:
        print(s[index])
        index=index+1
    else:
        break
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)


    # A single line providing the move to be made: N NE E SE S SW W or NW
    
