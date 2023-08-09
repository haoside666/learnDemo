import sys
import os

def main()->int:
    fd=open("./1.txt","w")
    save_fd=os.dup(1)
    os.dup2(fd.fileno(),1)
    fd.close()
    print("hello world")
    os.dup2(save_fd,1)
    return 0

'''
def main()->int:
    f=open('1.txt','a')
    os.dup2(f.fileno(), sys.stdout.fileno())
    f.close()
    print('runoob')
    print('google')
    sys.stdout.flush()
    return 0
'''

if __name__=="__main__":
    sys.exit(main())

