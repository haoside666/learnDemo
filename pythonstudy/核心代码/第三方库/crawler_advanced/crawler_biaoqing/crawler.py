import time

import requests
from bs4 import BeautifulSoup
import re


def download_all_htmls():
    url = "https://fabiaoqing.com/biaoqing/lists/page/{}.html"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
    }
    htmls = []
    for page in range(1, 6):
        r = requests.get(url.format(page), headers=headers)
        while r.status_code != 200:
            time.sleep(1)
            r = requests.get(url.format(page), headers=headers)
        r.encoding = "utf-8"
        htmls.append(r.text)
    return htmls


def parse_single_html(html):
    soup = BeautifulSoup(html, "html.parser")
    divs = soup.find_all("div", class_="tagbqppdiv")
    datas = []
    default_name = "img_random_"
    for index in range(len(divs)):
        img = divs[index].find("img")
        if not img: continue
        if len(img["title"]) == 0:
            name = f'{default_name}{int(time.time())}{index}'
        else:
            # 移除标点符号，只保留中文，大小写字母以及阿拉伯数字
            pattern = "[^0-9A-Za-z\u4e00-\u9fa5]"
            name = re.sub(pattern, "", img["title"])
            if len(img["title"]) > 10:
                name = name[-10:]
        datas.append((img["data-original"], name))
    return datas


def download_img(img_url, filename):
    headers = {
        "Referer": "https://fabiaoqing.com/"
    }
    r = requests.get(img_url, headers=headers)
    while r.status_code != 200:
        time.sleep(1)
        r = requests.get(img_url, headers=headers)
    with open(filename, "wb") as file:
        file.write(r.content)


if __name__ == "__main__":
    htmls = download_all_htmls()
    for html in htmls:
        for img_url, name in parse_single_html(html):
            post_fix = img_url.rpartition('.')[2]
            download_img(img_url, f'./output/{name}.{post_fix}')
