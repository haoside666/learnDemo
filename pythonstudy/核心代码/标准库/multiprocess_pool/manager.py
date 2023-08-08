import multiprocessing


def init_jq():
    jq.a="a"
    jq.b="b"

def download_data(stock):
    print(jq.a) # 这里可以直接调用共享的jq
    # do something

if __name__ == '__main__':
    manager = multiprocessing.Manager()
    jq = manager.Namespace()
    init_jq()
    pool = multiprocessing.Pool(processes=4)
    stocks = ['000001.XSHE', '000002.XSHE', '000003.XSHE']
    pool.map(download_data, stocks)