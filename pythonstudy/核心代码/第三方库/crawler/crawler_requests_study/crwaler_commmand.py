# coding:utf8
from bs4 import BeautifulSoup

# soup = BeautifulSoup('<b class="boldest">Extremely bold</b>', 'html.parser')
# tag = soup.b
# print(type(tag))
# print(tag.name)  # tag 名
# print(tag["class"])  # tag 属性
# print(tag.attrs)

# html_doc = '''
# <!DOCTYPE html>
# <html lang="zh-CN">
#
# <head>
# 	<meta http-equiv="X-UA-Compatible" content="IE=Edge" />
# 	<meta charset="UTF-8" />
# </head>
#
# <body class="home blog wp-embed-responsive">
# 	<div id="site-container" class="clearfix">
#
# 		<div id="primary" class="sidebar-right clearfix">
# 			<!-- .ht-container -->
# 			<div class="ht-container">
# 				<!-- #content -->
# 				<section id="content" role="main">
# 					<div id="homepage-categories" class="clearfix">
# 						<div class="row">
# 							<div class="column col-half 1">
# 								<h3> <a href="https://www.linuxcool.com/category/file"
# 										title="View all posts in 1：文件管理">1：文件管理</a></h3>
# 							</div>
# 							<div class="column col-half 2">
# 								<h3> <a href="https://www.linuxcool.com/category/document"
# 										title="View all posts in 2：文档编辑">2：文档编辑</a></h3>
# 							</div>
# 						</div>
# 						<div class="row">
# 							<div class="column col-half 3">
# 								<h3> <a href="https://www.linuxcool.com/category/system"
# 										title="View all posts in 3：系统管理">3：系统管理</a></h3>
# 							</div>
# 							<div class="column col-half 4">
# 								<h3> <a href="https://www.linuxcool.com/category/disk"
# 										title="View all posts in 4：磁盘管理">4：磁盘管理</a></h3>
# 							</div>
# 						</div>
# 						<div class="row">
# 							<div class="column col-half 5">
# 								<h3> <a href="https://www.linuxcool.com/category/transfer"
# 										title="View all posts in 5：文件传输">5：文件传输</a></h3>
# 							</div>
# 							<div class="column col-half 6">
# 								<h3> <a href="https://www.linuxcool.com/category/network"
# 										title="View all posts in 6：网络通讯">6：网络通讯</a></h3>
# 							</div>
# 						</div>
# 						<div class="row">
# 							<div class="column col-half 7">
# 								<h3> <a href="https://www.linuxcool.com/category/device"
# 										title="View all posts in 7：设备管理">7：设备管理</a></h3>
# 							</div>
# 							<div class="column col-half 8">
# 								<h3> <a href="https://www.linuxcool.com/category/backup"
# 										title="View all posts in 8：备份压缩">8：备份压缩</a></h3>
# 							</div>
# 						</div>
# 						<div class="row">
# 							<div class="column col-half 9">
# 								<h3> <a href="https://www.linuxcool.com/category/other"
# 										title="View all posts in 9：其他命令">9：其他命令</a></h3>
# 							</div>
# 							<div class="column col-half 10">
# 								<h3> <a href="https://www.linuxcool.com/category/knowledge"
# 										title="View all posts in 扩展：知识干货">扩展：知识干货</a></h3>
# 							</div>
# 						</div>
# 					</div>
#
# 				</section>
# 				<!-- #content -->
#
# 			</div>
# 			<!-- /.ht-container -->
# 		</div>
# 	</div>
# </body>
# </html>
# '''
# soup = BeautifulSoup(html_doc, 'html.parser')
# # 使用CSS选择器匹配
# div_elements = soup.select('div[class^="column col-half"]')
#
# for div in div_elements:
#     print(div.a['href'].strip())
#     print(div.text.strip())

import re
import time
import random
import csv
import requests

ua_list = [
    'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Maxthon 2.0',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_0) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11',
    'User-Agent:Opera/9.80 (Windows NT 6.1; U; en) Presto/2.8.131 Version/11.11',
    'Mozilla/5.0 (Windows NT 6.1; rv:2.0.1) Gecko/20100101 Firefox/4.0.1',
    'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)',
    'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50',
    'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0',
    'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1',
    'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:2.0.1) Gecko/20100101 Firefox/4.0.1',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.37',
]


# 定义一个爬虫类
class CommandSpider(object):
    # 初始化
    # 定义初始页面url
    def __init__(self):
        self.url = 'https://www.linuxcool.com/category/other/page/'

    # 获取随机headers
    @staticmethod
    def get_headers():
        headers = {'User-Agent': random.choice(ua_list)}
        return headers

    # 请求函数
    def get_html(self, index):
        url = self.url + str(index)
        headers = self.get_headers()
        response = requests.get(url, headers=headers)
        # 直接调用解析函数
        self.parse_html(response.text)

    # 解析函数
    def parse_html(self, html_doc):
        soup = BeautifulSoup(html_doc, 'html.parser')
        # 使用CSS选择器匹配
        r_list = []
        lis = soup.findAll("article")
        for item in lis:
            r_list.append(item.text.replace("\n\n\n","--->").replace("Read More →","").strip())

        with open("./category/other.txt","a",encoding="utf-8") as file:
            file.write("\n".join(r_list)+"\n")


    # 主函数
    def run(self):
        for i in range(1, 12):
            self.get_html(i)
        time.sleep(3)


# 以脚本方式启动
if __name__ == '__main__':
    # 捕捉异常错误
    try:
        spider = CommandSpider()
        spider.run()
    except Exception as e:
        print("错误:", e)
