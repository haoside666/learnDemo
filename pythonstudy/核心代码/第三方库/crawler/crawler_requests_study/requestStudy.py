import requests

def fun1():
    # 定义变量：URL 与 headers
    url = 'http://httpbin.org/get'  # 向测试网站发送请求
    # 重构请求头
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36'}
    response = requests.get(url=url, headers=headers)
    print(response.text)

def fun2():
    # 百度翻译
    url = 'https://fanyi.baidu.com'
    # post请求体携带的参数，可通过开发者调试工具查看
    # 查看步骤：NetWork选项->Headers选项->Form Data
    data = {'from': 'zh',
            'to': 'en',
            'query': '编程帮www.biancheng.net你好'
            }
    response = requests.post(url, data=data)
    print(response)

def fun3():
    response = requests.get('http://www.baidu.com')
    print(response.encoding)
    response.encoding = "utf-8"  # 更改为utf-8编码
    print(response.status_code)  # 打印状态码
    print(response.url)  # 打印请求url
    print(response.headers)  # 打印头信息
    print(response.cookies)  # 打印cookie信息
    print(response.text)  # 以字符串形式打印网页源码
    print(response.content)  # 以字节流形式打印


def fun4():
    url = 'https://img2.baidu.com/it/u=1333368120,1655314893&fm=253&fmt=auto&app=138&f=JPEG?w=500&h=500'
    # 简单定义浏览器ua信息
    headers = {'User-Agent': 'Mozilla/4.0'}
    html = requests.get(url=url, headers=headers).content
    # 以二进制的方式下载图片
    with open('./python_logo.jpg', 'wb') as f:
        f.write(html)


if __name__ == '__main__':
    fun4()

