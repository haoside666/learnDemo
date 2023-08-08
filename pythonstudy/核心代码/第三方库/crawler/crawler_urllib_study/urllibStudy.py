#导包,发起请求使用urllib库的request请求模块
import urllib.request
from urllib import request
from urllib import error
from fake_useragent import UserAgent
#导入parse模块
from urllib import parse

def fun1():
    # urlopen()向URL发请求,返回响应对象,注意url必须完整
    response=urllib.request.urlopen('http://www.baidu.com/')
    #提取响应内容
    html = response.read().decode('utf-8')
    #打印响应内容
    with open("../1.html", "w") as file:
        file.write(html)


def fun2():
    #向网站发送get请求
    response=urllib.request.urlopen('http://httpbin.org/get')
    html = response.read().decode()
    print(html)

def fun3():
    # 定义变量：URL 与 headers
    url = 'http://httpbin.org/get' #向测试网站发送请求
    #重构请求头
    headers = {
    'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36'}
    # 1、创建请求对象，包装ua信息
    req = request.Request(url=url,headers=headers)
    # 2、发送请求，获取响应对象
    res = request.urlopen(req)
    # 3、提取响应内容
    html = res.read().decode('utf-8')
    print(html)



def fun4():
    ua_list = [
        'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Maxthon 2.0',
        'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_0) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11',
        'User-Agent:Opera/9.80 (Windows NT 6.1; U; en) Presto/2.8.131 Version/11.11',
        'Mozilla/5.0 (Windows NT 6.1; rv:2.0.1) Gecko/20100101 Firefox/4.0.1',
        'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)',
        'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50',
        'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0',
        ' Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1',
        'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1',
        ' Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:2.0.1) Gecko/20100101 Firefox/4.0.1',
    ]
    # 实例化一个对象
    ua = UserAgent()
    # 随机获取一个ie浏览器ua
    print(ua.ie)
    print(ua.ie)
    # 随机获取一个火狐浏览器ua
    print(ua.firefox)
    print(ua.firefox)



def fun5():
    # urllib.parse
    # urllib.parse.urlencode({'key': 'value'})  # 字典
    # urllib.parse.quote(string)  # 字符串
    # 构建查询字符串字典
    query_string = {
        'wd': '爬虫'
    }
    # 调用parse模块的urlencode()进行编码
    result = parse.urlencode(query_string)
    # 使用format函数格式化字符串，拼接url地址
    url = 'http://www.baidu.com/s?{}'.format(result)
    print(url)

    # 注意url的书写格式，和 urlencode存在不同
    url = 'http://www.baidu.com/s?wd={}'
    word = "爬虫"
    # quote()只能对字符串进行编码
    query_string = parse.quote(word)
    print(url.format(query_string))

def fun6():
    try:
        response=urllib.request.urlopen('http://123/com')
        html = response.read().decode('utf-8')
        print(html)
    except error.URLError as e:
        print("URLError")
    except error.HTTPError as e:
        print("HTTPError")
    except error.ContentTooShortError as e:
        print("ContentTooShortError")
    except ValueError as e:
        print("ValueError")
    except Exception as e:
        # 捕获异常并获取异常类型
        exception_type = type(e).__name__
        print("发生异常:", exception_type)
        exit(1)

if __name__ == '__main__':
    fun5()

