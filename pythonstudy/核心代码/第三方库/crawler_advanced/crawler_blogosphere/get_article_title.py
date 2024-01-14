import requests
from bs4 import BeautifulSoup

url = "https://www.cnblogs.com/AggSite/AggSitePostList"
headers = {
    "content-type": "application/json; charset=UTF-8",
    "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36",
}

for page in range(1, 101):
    print(f"#############################{page}#############################")
    data = {"CategoryType": "SiteHome", "ParentCategoryId": 0, "CategoryId": 808, "PageIndex": page,
            "TotalPostCount": 2000, "ItemListActionName": "AggSitePostList"}

    r = requests.post(url, json=data, headers=headers)
    if r.status_code != 200:
        print("error: the status code not is 200!")
        raise Exception()
    html_doc = r.text
    soup = BeautifulSoup(html_doc, "html.parser")
    post_item_texts = soup.find_all("div", class_="post-item-text")
    for post_item_text in post_item_texts:
        link = post_item_text.find("a", class_="post-item-title")
        print(link["href"], link.text)
