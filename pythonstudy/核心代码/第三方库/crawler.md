## 编写爬虫的流程

爬虫程序与其他程序不同，它的的思维逻辑一般都是相似的， 所以无需我们在逻辑方面花费大量的时间。下面对 Python 编写爬虫程序的流程做简单地说明：

- 先由 urllib 模块的 request 方法打开 URL 得到网页 HTML 对象。
- 使用浏览器打开网页源代码分析网页结构以及元素节点。
- 通过 Beautiful Soup 或则正则表达式提取数据。
- 存储数据到本地磁盘或数据库。



## urllib爬虫库

#### 1) urlopen()

表示向网站发起请求并获取响应对象，如下所示：

```
urllib.request.urlopen(url,timeout)
```

urlopen() 有两个参数，说明如下：

- url：表示要爬取数据的 url 地址。
- timeout：设置等待超时时间，指定时间内未得到响应则抛出超时异常。

#### 2) Request()

该方法用于创建请求对象、包装请求头，比如重构 User-Agent（即用户代理，指用户使用的浏览器）使程序更像人类的请求，而非机器。重构 User-Agent 是爬虫和反爬虫斗争的第一步。在下一节会做详细介绍。

```
urllib.request.Request(url,headers)
```

参数说明如下：

- url：请求的URL地址。
- headers：重构请求头。

#### 3) html响应对象方法

```
bytes = response.read() # read()返回结果为 bytes 数据类型
string = response.read().decode() # decode()将字节串转换为 string 类型
url = response.geturl() # 返回响应对象的URL地址
code = response.getcode() # 返回请求时的HTTP响应码
```

#### 4) 编码解码操作

```
#字符串转换为字节码
string.encode("utf-8") 
#字节码转换为字符串
bytes.decode("utf-8") 
```



