import sys
import math

n = int(input())  # Number of elements which make up the association table.
q = int(input())  # Number Q of file names to be analyzed.
d={}
for i in range(n):
    # ext: file extension
    # mt: MIME type.
    ext, mt = input().split()
    d[ext.lower()]=mt

for i in range(q):
    fname = input().lower()  # One file name per line.
    index=fname.rfind(".")
    exname=fname[index+1:]
    print(d[exname] if index!=-1 and exname in d else "UNKNOWN")
