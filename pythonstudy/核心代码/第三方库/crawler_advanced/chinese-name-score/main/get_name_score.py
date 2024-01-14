# -*- coding: utf-8 -*-
import random
import sys

from bs4 import BeautifulSoup
import time
import requests

from urllib.parse import urlencode, quote
import user_config
import sys_config
from exception.CustomizedException import RequestContentExcept

origin_cookies_dict = dict()


def get_name_postfixs():
    """根据是否使用单字和用户配置的性别参数，获取所有的名字列表
    """
    target_name_postfixs = set()

    # 是否有单字限制
    limit_word = user_config.setting["limit_world"]

    fpath_input = ""
    if limit_word:
        if user_config.setting["sex"] == "男":
            fpath_input = sys_config.FPATH_DICTFILE_BOYS_SINGLE
        elif user_config.setting["sex"] == "女":
            fpath_input = sys_config.FPATH_DICTFILE_GIRLS_SINGLE
        print(f"has limit word!")
    else:
        if user_config.setting["sex"] == "男":
            fpath_input = sys_config.FPATH_DICTFILE_BOYS_DOUBLE
        elif user_config.setting["sex"] == "女":
            fpath_input = sys_config.FPATH_DICTFILE_GIRLS_DOUBLE

    for line in open(fpath_input):
        iter_name = str(line).strip()
        target_name_postfixs.add(iter_name)

    return target_name_postfixs


def get_cookies(name):
    if user_config.setting["sex"] == "男":
        sex = "1"
    else:
        sex = "0"
    global origin_cookies_dict
    cookies_dict = {
        "Hm_lvt_668a2b1ccec82d575177212da2570e5d": int(time.time()) - random.randint(101, 999) * 12,
        "input%5FRenYue": "",
        "input%5Fday": 9,
        "input%5Fdata%5Ftype": 0,
        "iscookies": "yes",
        "input%5Fzty": "",
        "input%5Fmonth": user_config.setting["month"],
        "input%5Fyear": user_config.setting["year"],
        "input%5Fhour": user_config.setting["hour"],
        "input%5Fminute": user_config.setting["minute"],
        "input%5Fsex": sex,
        # "ASPSESSIONIDSUSTDSCT": "MGFAPLMCOGOMOKJIMAGPAFBA",
        "input%5Fpid": quote(f"{user_config.setting['area_province']}".encode("GB18030")),
        "input%5Fname": quote(f"{user_config.setting['name_prefix']}{name}".encode("GB18030")),
        "input%5Fcid": quote(f"{user_config.setting['area_region']}".encode("GB18030")),
        "input%5Fming": quote(f"{name}".encode("GB18030")),
        "input%5Fxing": quote(f"{user_config.setting['name_prefix']}".encode("GB18030")),
        "Hm_lpvt_668a2b1ccec82d575177212da2570e5d": int(time.time())
    }
    cookies_dict.update(origin_cookies_dict)
    cookies = "; ".join([f'{k}={v}' for k, v in cookies_dict.items()])
    return cookies


def get_params_data(name):
    data = dict()
    data['isbz'] = "1"
    data['xing'] = user_config.setting["name_prefix"].encode("GB18030")
    data['ming'] = name.encode("GB18030")
    # 表示女，1表示男
    if user_config.setting["sex"] == "男":
        data['sex'] = "1"
    else:
        data['sex'] = "0"
    # 日期类型，0表示公历，1表示农历
    data['data_type'] = "0"
    data['year'] = user_config.setting["year"]
    data['month'] = user_config.setting["month"]
    data['day'] = user_config.setting["day"]
    data['hour'] = user_config.setting["hour"]
    data['minute'] = user_config.setting["minute"]
    data['pid'] = user_config.setting["area_province"].encode("GB18030")
    data['cid'] = user_config.setting["area_region"].encode("GB18030")
    # 喜用五行，0表示自动分析，1表示自定喜用神
    data['wxxy'] = "0"
    data['xishen'] = "金".encode("GB18030")
    data['yongshen'] = "金".encode("GB18030")
    data['check_agree'] = "agree".encode("GB18030")
    data['act'] = "submit"
    params_data = urlencode(data)
    return params_data


def compute_name_score(name_postfix):
    """调用接口，执行计算，返回结果
    """
    result_data = {}
    url = sys_config.REQUEST_URL
    headers = {
        "Content-Type": "application/x-www-form-urlencoded",
        # "Cookie": get_cookies(name_postfix),
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:65.0) Gecko/20100101 Firefox/65.0"
    }
    params_data = get_params_data(name_postfix)

    r = requests.post(url, data=params_data, headers=headers)
    r.encoding = 'GB18030'
    if r.status_code != 200:
        if r.status_code == 500:
            time.sleep(1)
            return compute_name_score(name_postfix)
        else:
            raise Exception("the status code not is 200!")

    soup = BeautifulSoup(r.text, 'html.parser')
    full_name = get_full_name(name_postfix)
    for node in soup.find_all("div", class_="chaxun_b"):
        if "姓名五格评分" not in node.get_text():
            continue

        score_fonts = node.find_all("font")
        result_data['wuge_score'] = score_fonts[0].text.replace("分", "").strip()
        result_data['bazi_score'] = score_fonts[1].text.replace("分", "").strip()
        result_data['total_score'] = float(result_data['wuge_score']) + float(result_data['bazi_score'])
        result_data['full_name'] = full_name
        return result_data

    raise RequestContentExcept("No score found for the wuge and bazi")


def compute_and_writefile(name_postfix, fout):
    try:
        name_data = compute_name_score(name_postfix)
        write_to_file(fout, name_data)
    except RequestContentExcept:
        print("RequestContentExcept!!!", file=sys.stderr)
        exit(1)
    except Exception as e:
        print('error, ', e.args, type(e).__name__)
        print(f"error: {name_postfix}")
        exit(1)


def get_full_name(name_postfix):
    return f"{user_config.setting['name_prefix']}{name_postfix}"


def write_to_file(fout, name_data):
    fout.write(name_data['full_name'] + "\t\t"
               + str(name_data['bazi_score']) + "\t"
               + str(name_data['wuge_score']) + "\t"
               + str(name_data['total_score']) + "\n")
    fout.flush()


def process(output_fpath):
    """计算并且将结果输出到文件
    """
    # 输出文件路径
    fout = open(output_fpath, "w", encoding="utf-8")
    # 获得所有可用的名字列表
    all_name_postfixs = get_name_postfixs()
    # 测试用的名字列表
    # all_name_postfixs = ["三", "晴瑶", "家卫"]

    cnt = 1
    for name_postfix in all_name_postfixs:
        compute_and_writefile(name_postfix, fout)
        print(f"process the {cnt}th---")
        cnt += 1

    fout.close()


# def get_first_cookies_info():
#     url = sys_config.REQUEST_URL
#     headers = {
#         "Content-Type": "application/x-www-form-urlencoded",
#         "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:65.0) Gecko/20100101 Firefox/65.0"
#     }
#
#     r = requests.get(url, headers=headers)
#     r.encoding = 'GB18030'
#     if r.status_code != 200:
#         raise Exception()
#
#     return r.cookies.get_dict()


if __name__ == "__main__":
    # origin_cookies_dict = get_first_cookies_info()
    print("begin................................")
    output_fpath = f"./outputs/{user_config.setting['output_fname']}"
    process(output_fpath)
    print("over................................")
