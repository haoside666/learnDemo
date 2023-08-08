import sys
import math
import numpy
# The while loop represents the game.
# Each iteration represents a turn of the game
# where you are given inputs (the heights of the mountains)
# and where you have to print an output (the index of the mountain to fire on)
# The inputs you are given are automatically updated according to your last actions.


# game loop

while True:
    l=[]
    for i in range(8):
        mountain_h = int(input())  # represents the height of one mountain.
        l.append(mountain_h)
        
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)
    a = numpy.array(l)
# 获取最大值的索引
    print(a.argmax())
    # The index of the mountain to fire on.