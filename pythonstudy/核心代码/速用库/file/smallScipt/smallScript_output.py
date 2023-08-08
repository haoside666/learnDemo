import sys
import os

for line in sys.stdin:
	if(len(line.strip())!=0):  
		print(eval(str(line)))
