from urllib.parse import *


def parse_form_info(form_infos):
    print("-" * 40)
    for form_info in form_infos.strip().split("\n"):
        decoded_url = unquote(form_info, encoding="gb2312")
        print(decoded_url)


def parse_cookie(cookies):
    print("-" * 40)
    for form_info in cookies.split("; "):
        decoded_url = unquote(form_info, encoding="gb2312")
        print(decoded_url)


def fun():
    form_infos = '''
    isbz: 1
    xing: %D5%C5
    ming: %BA%C6%D1%F3
    sex: 1
    data_type: 0
    year: 2024
    month: 1
    day: 9
    hour: 7
    minute: 40
    pid: %B1%B1%BE%A9
    cid: %B1%B1%BE%A9
    wxxy: 0
    xishen: %BD%F0
    yongshen: %BD%F0
    check_agree: agree
    act: submit
    '''
    parse_form_info(form_infos)


def fun2():
    form_infos = '''
    isbz: 1
    xing: %D5%C5
    ming: %C8%FD
    sex: 1
    data_type: 0
    year: 2024
    month: 1
    day: 9
    hour: 7
    minute: 40
    pid: %B1%B1%BE%A9
    cid: %B1%B1%BE%A9
    wxxy: 0
    xishen: %BD%F0
    yongshen: %BD%F0
    check_agree: agree
    act: submit
    '''
    parse_form_info(form_infos)


def parse_cookies():
    with open("./cookies.txt", "r") as file:
        for line in file:
            cookies = line.strip()
            if len(cookies) == 0:
                continue
            parse_cookie(cookies)


def get_origin_cookies(cookies_dict):
    cookies = "; ".join([f'{k}={v}' for k, v in cookies_dict.items()])
    return cookies


if __name__ == "__main__":
    parse_cookies()
    # cookies_dict = {
    #     "Hm_lvt_668a2b1ccec82d575177212da2570e5d": 1704851927,
    #     "input%5FRenYue": "",
    #     "input%5Fday": 9,
    #     "input%5Fdata%5Ftype": 0,
    #     "iscookies": "yes",
    #     "input%5Fzty": "",
    #     "input%5Fmonth": 1,
    #     "input%5Fyear": 2024,
    #     "input%5Fhour": 7,
    #     "input%5Fminute": 40,
    #     "input%5Fsex": 1,
    #     "ASPSESSIONIDSUSTDSCT": "MGFAPLMCOGOMOKJIMAGPAFBA",
    #     "input%5Fpid": "",
    #     "input%5Fname": quote("李四".encode("gb2312")),
    #     "input%5Fcid": "",
    #     "input%5Fming": quote("四".encode("gb2312")),
    #     "input%5Fxing": quote("李".encode("gb2312")),
    #     "Hm_lpvt_668a2b1ccec82d575177212da2570e5d": 1704873263
    # }

    # print(get_origin_cookies(cookies_dict))

