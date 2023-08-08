import requests
import os

count = 0


def get_data(page):
    headers = {'Accept': 'application/json', 'Accept-Encoding': 'gzip, deflate, br',
               'Accept-Language': 'zh-CN,zh;q=0.9',
               'Authorization': 'Bearer eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCIsImtpZCI6InhYa3BCdDNyV3MyRy11YjlscEpncSJ9.eyJodHRwczovL2h1Yi5kb2NrZXIuY29tIjp7ImVtYWlsIjoienlqMjAwMUB6anV0LmVkdS5jbiIsInJvbGVzIjpbXSwic2Vzc2lvbl9pZCI6IjlmZGY1YjgzLWUyYjAtNGIzZC1hMzE0LTA0ZDdmNTc4ZTJjMyIsInNvdXJjZSI6ImF1dGgwIiwidXNlcm5hbWUiOiJoYW9zaWRlIiwidXVpZCI6IjhmNDQ1NmFjLWEyYTItNDk2OC04YzgyLTE4ZmNlYWRjNTgzZSJ9LCJpc3MiOiJodHRwczovL2xvZ2luLmRvY2tlci5jb20vIiwic3ViIjoiYXV0aDB8OGY0NDU2YWMtYTJhMi00OTY4LThjODItMThmY2VhZGM1ODNlIiwiYXVkIjpbImh0dHBzOi8vaHViLmRvY2tlci5jb20iLCJodHRwczovL2RvY2tlci1wcm9kLnVzLmF1dGgwLmNvbS91c2VyaW5mbyJdLCJpYXQiOjE2ODYzOTYwNTMsImV4cCI6MTY4NjM5OTY1MywiYXpwIjoibHZlOUdHbDhKdFNVcm5lUTFFVnVDMGxiakhkaTluYjkiLCJzY29wZSI6Im9wZW5pZCBwcm9maWxlIGVtYWlsIG9mZmxpbmVfYWNjZXNzIn0.JakXQ20AzPUpADwDFXPhVfhbypy7iAuwyzwtLCAU1f97YuYcBdduEnt3bL4pBUfHU6Qf19nARY8VigYKAaUCFe5XKVSev8YEvY2fSlv5ei1fGSeeLoOGWacVvw8aLTFjRqGDFicWYzDhFHla46fANJ8o6aLhsw8kUzNHYdBF2oyDP1XaHIm_MxhNMgYczQ7Xl1OtU69VUkKwAF4jGAQtdR_qgGzi2Ba3TIKqHtWG-NVJLVyuhMb_t3BcfoawMBUlez0U57l5BTAjFNJfOPfOVFnNsYqtk3PdGpTVfsiZ3hZaVEcunBmilIYRu7Onjcz3cNcjkjrF0svPGImtBLIiQw',
               'Cache-Control': 'no-cache', 'Connection': 'keep-alive', 'Content-Type': 'application/json',
               'Cookie': '_gcl_au=1.1.1880686724.1680857441; _mkto_trk=id:790-SSB-375&token:_mch-docker.com-1680857441181-65361; _fbp=fb.1.1680857442215.723866359; ajs_anonymous_id=1831408d-afc0-4d9d-a5ef-841b7976fe58; _hjSessionUser_3169877=eyJpZCI6ImMwMDQ2MDA5LWFlYWUtNTc5NS1iODgyLTBkMTMwM2UxOGIzMyIsImNyZWF0ZWQiOjE2ODA4NTc0NDE2NTMsImV4aXN0aW5nIjp0cnVlfQ==; ajs_user_id=8f4456aca2a249688c8218fceadc583e; NPS_383366e9_last_seen=1681347556271; OptanonAlertBoxClosed=2023-04-13T00:59:17.082Z; NPS_383366e9_surveyed=true; fs_uid=#o-1E6Z8E-na1#5264411498106880:6292514441539584:::#/1712832040; _ga=GA1.1.166986684.1680857441; ln_or=eyIzNzY1MjEwIjoiZCJ9; fullstoryStart=false; _legacy_auth0.lve9GGl8JtSUrneQ1EVuC0lbjHdi9nb9.is.authenticated=true; auth0.lve9GGl8JtSUrneQ1EVuC0lbjHdi9nb9.is.authenticated=true; docker-id=haoside; _ga_XJWPQMJYHQ=GS1.1.1686390438.76.1.1686390459.39.0.0; OptanonConsent=isGpcEnabled=0&datestamp=Sat+Jun+10+2023+17%3A47%3A39+GMT%2B0800+(%E4%B8%AD%E5%9B%BD%E6%A0%87%E5%87%86%E6%97%B6%E9%97%B4)&version=202209.1.0&isIABGlobal=false&hosts=&consentId=e2178464-b3c9-4dee-953c-87fdc2974873&interactionCount=2&landingPath=NotLandingPage&groups=C0003%3A1%2CC0001%3A1%2CC0002%3A1%2CC0004%3A1%2CSPD_BG%3A1&AwaitingReconsent=false&geolocation=US%3BCA',
               'Host': 'hub.docker.com', 'Pragma': 'no-cache',
               'Referer': 'https://hub.docker.com/search?q=&image_filter=official', 'Search-Version': 'v3',
               'Sec-Ch-Ua': '\"Not.A/Brand\";v=\"8\", \"Chromium\";v=\"114\", \"Google Chrome\";v=\"114\"',
               'Sec-Ch-Ua-Mobile': '?0', 'Sec-Ch-Ua-Platform': '\"Windows\"', 'Sec-Fetch-Dest': 'empty',
               'Sec-Fetch-Mode': 'cors', 'Sec-Fetch-Site': 'same-origin',
               'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36',
               'X-Docker-Api-Client': 'docker-hub/v2758.0.0'}

    url = "https://hub.docker.com/api/content/v1/products/search"
    params = {
        "image_filter": "official",
        "page": page,
        "page_size": "25",
        "q": ""
    }
    response = requests.get(url, headers=headers, params=params)
    a = response.json()
    print(a)
    # parse_data(response.json())


# def parse_data(json_data):
#     items = json_data['summaries']
#     for item in items:
#         global count
#         count +=1
#         docker_name = item['name']
#         print(f"当前采集第{count}条数据：{docker_name}")
#         with open('docker_name.txt','a',encoding='utf-8') as f:
#             f.write(docker_name+'\n')


if __name__ == '__main__':
    page = 1

    for num in range(1, page + 1):
        print(f"收集第{num}页")
        get_data(num)

