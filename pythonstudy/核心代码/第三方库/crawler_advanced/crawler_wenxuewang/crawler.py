# -*- coding: utf-8 -*-
import os.path
import sys

import requests
from bs4 import BeautifulSoup

root_url = "http://www.wenxuewang.net"
longwangchuanshuo_url = os.path.join(root_url, "0", "20")


def get_chapter_list():
    r = requests.get(longwangchuanshuo_url)
    if r.status_code != 200:
        print("error: the status code not is 200", file=sys.stderr)
        exit(1)

    soup = BeautifulSoup(r.text, "html.parser")
    dds = soup.find_all("dd")
    chapter_list = []
    for dd in dds:
        link = dd.next_element
        href = f'{root_url}/{link["href"]}'
        text = link.text
        chapter_list.append((href, text))
    return chapter_list


def write_content_to_file(filename, content):
    with open(filename, "w", encoding="utf-8") as file:
        file.write(content)


def get_chapter_content(chapter):
    url, title = chapter

    r = requests.get(url)
    if r.status_code != 200:
        print("error: the status code not is 200", file=sys.stderr)
        return
    soup = BeautifulSoup(r.text, "html.parser")
    content = soup.find(id="content").text
    content = content.replace(chr(160), '').replace(chr(13), "\n").replace(chr(32), "")
    write_content_to_file(f'./output/{title}.txt', content)


if __name__ == "__main__":
    chapter_list = get_chapter_list()
    cnt = 1
    for chapter in chapter_list:
        get_chapter_content(chapter)
        print(f"process the {cnt}th----")
        cnt += 1
