from multiprocessing import Process
from os import getpid
from random import randint
from time import time, sleep
import multiprocessing
import socket
def download_task(filename):
    # print('启动下载进程，进程号[%d].' % getpid())
    print('开始下载%s...' % filename)
    return filename



if __name__ == '__main__':
    start = time()
    for i in range(10):
        pool = multiprocessing.Pool()
        results = pool.imap(download_task, range(1000), chunksize=3)
        for result in results:
            print(f"filename:{result}")
        sleep(1)
        pool.close()
        pool.join()

    end = time()
    print('总共耗费了%.2f秒.' % (end - start))


# def f(x,y):
#     sleep(4)
#     sleep(1)
#     return x+y



# def tcp(port):
#     sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     sock.bind(('localhost', port))
#     sock.listen()
#
#     clientsocket, address = sock.accept()
#     print("连接地址: %s" % str(address))
#     clientsocket.close()
#     print("this is a test text.")
#     return port
#
# if __name__ == '__main__':
#     with multiprocessing.Pool(processes=4) as pool:         # start 4 worker processes
#         result = pool.map_async(tcp, (8080,))
#         result = pool.apply_async(tcp, (8080,))
#         result = pool.apply(tcp, (8081,))
#         print(result)
#         print(result.get())
#
#         for i in range(8080,8083):
#             result = pool.apply(tcp, (i,))
#             print(result)
#             result = pool.apply_async(tcp, (i,))
#             print(result.get())
#
#         result = pool.map(tcp,range(8080,8083))
#         print(result)
#
#         result = pool.imap(tcp, range(8080, 8083),chunksize=1)
#         for i in result:
#             print(i)
#
#
#         result = pool.map_async(tcp, range(8080, 8083))
#         print(result.get())
#
#         result = pool.imap_unordered(tcp,range(8080,8083),chunksize=10)
#         for i in result:
#             print(i)
#
#         for i in range(10):
#             print(i)
#         pool.close()
#         pool.join()



# import multiprocessing
# import time
#
# def func(x):
#     time.sleep(x)
#     return x + 2
#
# if __name__ == "__main__":
#     p = multiprocessing.Pool()
#     start = time.time()
#     for x in p.imap(func, [1,5,3]):
#         print("{} (Time elapsed: {}s)".format(x, int(time.time() - start)))
