import os.path

import requests
import sys
from bs4 import BeautifulSoup

root_url = "https://pic.netbian.com"
meinv = "4kmeinv"


def download_image(img_src, save_filename):
    with open(f"output/{save_filename}.jpg", "wb") as f:
        resp_img = requests.get(img_src)
        f.write(resp_img.content)


def get_current_page_image_list(page):
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
    }
    if page == 1:
        url = f'{root_url}/{meinv}'
    else:
        url = f'{root_url}/{meinv}/index_{page}.html'
    r = requests.get(url, headers=headers)
    if r.status_code != 200:
        print("error: the status code not is 200", file=sys.stderr)
        exit(1)
    r.encoding = "gbk"
    soup = BeautifulSoup(r.text, "html.parser")
    clearfix = soup.find("ul", class_="clearfix")

    image_list = []
    for img in clearfix.find_all("img"):
        image_list.append((root_url + img["src"], img["alt"].replace(" ","")))
    return image_list


def get_image_list():
    image_list = []
    for page in range(1, 3):
        image_list.extend(get_current_page_image_list(page))
    return image_list


for image in get_image_list():
    download_image(*image)
