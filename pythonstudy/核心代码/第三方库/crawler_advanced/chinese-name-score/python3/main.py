# coding:utf-8
from urllib.parse import urlencode, quote

import requests
from bs4 import BeautifulSoup
import time


def get_cookies(xing, name):
    cookies_dict = {
        "Hm_lvt_668a2b1ccec82d575177212da2570e5d": 1704851927,
        "input%5FRenYue": "",
        "input%5Fday": 9,
        "input%5Fdata%5Ftype": 0,
        "iscookies": "yes",
        "input%5Fzty": "",
        "input%5Fmonth": 1,
        "input%5Fyear": 1999,
        "input%5Fhour": 1,
        "input%5Fminute": 10,
        "input%5Fsex": 0,
        "ASPSESSIONIDSUSTDSCT": "MGFAPLMCOGOMOKJIMAGPAFBA",
        "input%5Fpid": "",
        "input%5Fname": quote(f"{xing}{name}".encode("gb2312")),
        "input%5Fcid": "",
        "input%5Fming": quote(f"{name}".encode("gb2312")),
        "input%5Fxing": quote(f"{xing}".encode("gb2312")),
        "Hm_lpvt_668a2b1ccec82d575177212da2570e5d": int(time.time())
    }
    cookies = "; ".join([f'{k}={v}' for k, v in cookies_dict.items()])
    return cookies


def get_name_score(xing, name):
    url = "https://life.httpcn.com/xingming.asp"
    headers = {
        "Content-Type": "application/x-www-form-urlencoded",
        "Cookie": get_cookies(xing, name),
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:65.0) Gecko/20100101 Firefox/65.0"
    }

    data = {
        "isbz": 1,
        "xing": xing.encode("gb2312"),
        "ming": name.encode("gb2312"),
        "sex": 0,
        "data_type": 0,
        "year": 1999,
        "month": 1,
        "day": 1,
        "hour": 1,
        "minute": 10,
        "pid": "".encode("gb2312"),
        "cid": "".encode("gb2312"),
        "wxxy": 0,
        "xishen": "金".encode("gb2312"),
        "yongshen": "金".encode("gb2312"),
        "check_agree": "agree",
        "act": "submit"
    }

    params_data = urlencode(data)
    # print(params_data)
    r = requests.post(url, data=params_data, headers=headers)
    r.encoding = 'gb2312'

    if r.status_code != 200:
        raise Exception()
    # print(r.text)
    soup = BeautifulSoup(r.text, "html.parser")
    for node in soup.find_all("div", class_="chaxun_b"):
        if "姓名五格评分" not in node.get_text():
            continue
        score_fonts = node.find_all("font")
        wuge_score = score_fonts[0].get_text()
        bazi_score = score_fonts[1].get_text()
        return wuge_score.replace("分", "").strip(), bazi_score.replace("分", "").strip()
    return "", ""


if __name__ == "__main__":
    xing = "张"
    with open("input.txt", "r", encoding="utf-8") as fin, open("output.txt", "w", encoding="utf-8") as fout:
        for line in fin:
            name = line.strip()
            if not name or len(name) == 0:
                continue
            wuge, bazi = get_name_score(xing, name)
            fout.write("\t".join([f"{xing}{name}", wuge, bazi]) + "\n")
