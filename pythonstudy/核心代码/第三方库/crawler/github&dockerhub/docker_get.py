import requests
import os

count = 0


def get_data(page):
    headers = {
        "Accept": "application/json",
        "Accept-Encoding": "gzip, deflate, br",
        "Accept-Language": "zh,zh-CN;q=0.9,en;q=0.8",
        "Cache-Control": "no-cache",
        "Connection": "keep-alive",
        "Content-Type": "application/json",
        "Cookie": "docker-id=; _gcl_au=1.1.301236461.1684936068; _fbp=fb.1.1684936069780.1462173888; _mkto_trk=id:790-SSB-375&token:_mch-docker.com-1684936070309-84912; _ga=GA1.2.459997761.1684936070; _gid=GA1.2.1527832586.1684936071; fullstoryStart=false; ajs_anonymous_id=c23c6e3b-751d-4434-8b83-6a39ed563ee4; NPS_383366e9_last_seen=1684936071244; OptanonAlertBoxClosed=2023-05-24T13:47:52.086Z; OptanonConsent=isGpcEnabled=0&datestamp=Wed+May+24+2023+21%3A47%3A52+GMT%2B0800+(%E4%B8%AD%E5%9B%BD%E6%A0%87%E5%87%86%E6%97%B6%E9%97%B4)&version=202209.1.0&isIABGlobal=false&hosts=&consentId=618dfa51-7de0-499e-810b-d7365bb8eec0&interactionCount=1&landingPath=NotLandingPage&groups=C0003%3A1%2CC0001%3A1%2CC0002%3A1%2CC0004%3A1; _ga_XJWPQMJYHQ=GS1.1.1684936069.1.1.1684936086.43.0.0",
        "Host": "hub.docker.com",
        "Pragma": "no-cache",
        "Referer": "https://hub.docker.com/search?q=&image_filter=store&page=2",
        "Search-Version": "v3",
        "sec-ch-ua": "\"Chromium\";v=\"112\", \"Google Chrome\";v=\"112\", \"Not:A-Brand\";v=\"99\"",
        "sec-ch-ua-mobile": "?0",
        "sec-ch-ua-platform": "\"Windows\"",
        "Sec-Fetch-Dest": "empty",
        "Sec-Fetch-Mode": "cors",
        "Sec-Fetch-Site": "same-origin",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36",
        "X-DOCKER-API-CLIENT": "docker-hub/v2674.0.0"
    }
    "https://hub.docker.com/api/content/v1/products/search?page={item}" \
                         "&page_size=100&source=community&q=github.com"
    url = "https://hub.docker.com/api/content/v1/products/search"
    params = {
        "image_filter": "store",
        "page": page,
        "page_size": "25",
        "q": ""
    }
    response = requests.get(url, headers=headers, params=params)
    parse_data(response.json())

def parse_data(json_data):
    items = json_data['summaries']
    for item in items:
        global count
        count +=1
        docker_name = item['name']
        print(f"当前采集第{count}条数据：{docker_name}")
        with open('docker_name.txt','a',encoding='utf-8') as f:
            f.write(docker_name+'\n')


if __name__ == '__main__':
    page = 20

    for num in range(1,page+1):
        print(f"收集第{num}页")
        get_data(num)