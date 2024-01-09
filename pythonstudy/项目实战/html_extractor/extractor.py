# -*- coding: utf8 -*-
import sys

from bs4 import BeautifulSoup, NavigableString

with open("input.txt","r",encoding="utf-8") as file:
    html_doc=file.read()

    soup = BeautifulSoup(html_doc, 'html.parser')
    # print(soup.text)

    div = soup.find("div")
    for child in div.children:
        print(child.text)


    # for string in soup.stripped_strings:
    #     print(string)
