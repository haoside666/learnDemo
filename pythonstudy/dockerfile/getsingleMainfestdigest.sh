#!/usr/bin/python3
import sys
if len(sys.argv)!=2:
    print("please input filename!!")
    exit(0)
with open(sys.argv[1], "r") as f_r:
    str=f_r.read()
    str=str.replace("\t","   ")
    str=str.replace("    ","   ")
    str=str.rstrip()
    
with open("2.json", "w") as f_w:
    f_w.write(str)

