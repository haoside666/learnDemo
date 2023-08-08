from lxml import etree

def fun1():
    html_str = '''
    <div class="wrapper">
        <a href="www.biancheng.net/product/" id="site">website product</a>
        <ul id="sitename">
            <li><a href="http://www.biancheng.net/" title="编程帮">编程</a></li>
            <li><a href="http://world.sina.com/" title="新浪娱乐">微博</a></li>
            <li><a href="http://www.baidu.com" title="百度">百度贴吧</a></li>
            <li><a href="http://www.taobao.com" title="淘宝">天猫淘宝</a></li>
            <li><a href="http://www.jd.com/" title="京东">京东购物</a></li>
            <li><a href="http://c.bianchneg.net/" title="C语言中文网">编程</a></li>
            <li><a href="http://www.360.com" title="360科技">安全卫士</a></li>
            <li><a href="http://www.bytesjump.com/" title=字节">视频娱乐</a></li>
            <li><a href="http://bzhan.com/" title="b站">年轻娱乐</a></li>
            <li><a href="http://hao123.com/" title="浏览器">搜索引擎</a></li>
        </ul>
        <ul id="sitename2">
            <li><a href="http://www.biancheng.net/" title="编程帮">编程</a></li>
            <li><a href="http://world.sina.com/" title="新浪娱乐">微博</a></li>
            <li><a href="http://www.baidu.com" title="百度">百度贴吧</a></li>
            <li><a href="http://www.taobao.com" title="淘宝">天猫淘宝</a></li>
            <li><a href="http://www.jd.com/" title="京东">京东购物</a></li>
            <li><a href="http://c.bianchneg.net/" title="C语言中文网">编程</a></li>
            <li><a href="http://www.360.com" title="360科技">安全卫士</a></li>
            <li><a href="http://www.bytesjump.com/" title=字节">视频娱乐</a></li>
            <li><a href="http://bzhan.com/" title="b站">年轻娱乐</a></li>
            <li><a href="http://hao123.com/" title="浏览器">搜索引擎</a></li>
        </ul>
    </div>
    '''
    html = etree.HTML(html_str)
    # 书写xpath表达式,提取文本最终使用text()
    xpath_bds = '//a/@href'
    # 提取文本数据，以列表形式输出
    r_list = html.xpath(xpath_bds)
    # 打印数据列表
    print(r_list)
    xpath_bds = '//a/text()'
    r_list = html.xpath(xpath_bds)
    print(r_list)
    xpath_bds = '//ul[@id="sitename"]/li/a/@href'
    r_list = html.xpath(xpath_bds)
    print(r_list)



def fun2():
    html_str='''
    <bookstore>
        <book id=1>
            <title lang="eng1">Harry Potter</title>
            <price>29.99</price>
        </book>
        <book id=2>
            <title lang="eng2">Learning XML</title>
            <price>39.95</price>
        </book>
    </bookstore>
    '''
    html = etree.HTML(html_str)
    xpath_bds = '//title/@lang'
    r_list = html.xpath(xpath_bds)
    print(r_list)

    xpath_bds = '//book[@id=2]/title/@lang'
    r_list = html.xpath(xpath_bds)
    print(r_list)

    xpath_bds = '//book[@id=2]/price/text()'
    r_list = html.xpath(xpath_bds)
    print(r_list)

def fun3():
    html_str = '''
    <div class="content">
      <div class="wrapper">
        <div class="main">
          <dl class="board-wrapper">
            <dd>
              <i class="board-index board-index-1">1</i>
              <a href="/films/1200486" title="我不是药神" class="image-link" data-act="boarditem-click"
                data-val="{movieId:1200486}">
                <img
                  src="//s3plus.meituan.net/v1/mss_e2821d7f0cfe4ac1bf9202ecf9590e67/cdn-prod/file:5788b470/image/loading_2.e3d934bf.png"
                  alt="" class="poster-default" />
                <img
                  data-src="https://p0.pipi.cn/mmdb/d2dad59253751bd236338fa5bd5a27c710413.jpg?imageView2/1/w/160/h/220"
                  alt="我不是药神" class="board-img" />
              </a>
              <div class="board-item-main">
                <div class="board-item-content">
                  <div class="movie-item-info">
                    <p class="name"><a href="/films/1200486" title="我不是药神" data-act="boarditem-click"
                        data-val="{movieId:1200486}">我不是药神</a></p>
                    <p class="star">
                      主演：徐峥,周一围,王传君
                    </p>
                    <p class="releasetime">上映时间：2018-07-05</p>
                  </div>
                  <div class="movie-item-number score-num">
                    <p class="score"><i class="integer">9.</i><i class="fraction">6</i></p>
                  </div>

                </div>
              </div>

            </dd>
            <dd>
              <i class="board-index board-index-2">2</i>
              <a href="/films/1297" title="肖申克的救赎" class="image-link" data-act="boarditem-click"
                data-val="{movieId:1297}">
                <img
                  src="//s3plus.meituan.net/v1/mss_e2821d7f0cfe4ac1bf9202ecf9590e67/cdn-prod/file:5788b470/image/loading_2.e3d934bf.png"
                  alt="" class="poster-default" />
                <img
                  data-src="https://p0.pipi.cn/mmdb/fb7386020fa51b0fafcf3e2e3a0bbe694d17d.jpg?imageView2/1/w/160/h/220"
                  alt="肖申克的救赎" class="board-img" />
              </a>
              <div class="board-item-main">
                <div class="board-item-content">
                  <div class="movie-item-info">
                    <p class="name"><a href="/films/1297" title="肖申克的救赎" data-act="boarditem-click"
                        data-val="{movieId:1297}">肖申克的救赎</a></p>
                    <p class="star">
                      主演：蒂姆·罗宾斯,摩根·弗里曼,鲍勃·冈顿
                    </p>
                    <p class="releasetime">上映时间：1994-09-10(加拿大)</p>
                  </div>
                  <div class="movie-item-number score-num">
                    <p class="score"><i class="integer">9.</i><i class="fraction">5</i></p>
                  </div>
                </div>
              </div>
            </dd>
          </dl>
        </div>
      </div>
    </div>
    '''
    # 创建解析对象
    html = etree.HTML(html_str)
    # print(etree.tostring(html).decode('utf-8'))
    # 书写xpath表达式,提取文本最终使用text()
    xpath_bds = '//dd/div/div/div/p/a/text()|//dd/div/div/div/p/text()'
    # 提取文本数据，以列表形式输出
    r_list = html.xpath(xpath_bds)
    for r in r_list:
        print(r.strip())


if __name__ == "__main__":
    fun3()
