# -*- coding: utf-8 -*-
import requests
import re
from bs4 import BeautifulSoup
from crawler_crazy_ant.utils.UrlManage import UrlManage

url_manage = UrlManage()

root_url = "http://www.crazyant.net/"
pattern = re.compile(r"^http://www.crazyant.net/\d+.html$")
url_manage.add_url(root_url)
while url_manage.has_url():
    url = url_manage.get_url()
    r = requests.get(url, timeout=3)
    if r.status_code != 200:
        print("error, return status_code is not 200", url)
        continue
    html_doc = r.text
    soup = BeautifulSoup(html_doc, "html.parser")
    print(soup.title.string)

    for item in soup.find_all('a'):
        if item.get("href"):
            if re.match(pattern, item["href"]):
                url_manage.add_url(item["href"])
