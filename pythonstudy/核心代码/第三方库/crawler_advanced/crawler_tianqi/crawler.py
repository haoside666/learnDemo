import requests
from bs4 import BeautifulSoup
import pandas as pd

root_url = "https://lishi.tianqi.com"
region = 'beijing'


def get_weather_info():
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
    }
    weather_info = {"date": [], "max_temperature": [], "lowest_temperature": [], "weather": [], "wind_direction": []}
    for year in range(2020, 2024):
        for month in range(1, 13):
            url = f'{root_url}/{region}/{year}{str(month).zfill(2)}.html'
            r = requests.get(url, headers=headers)
            if r.status_code != 200:
                raise Exception("error")
            r.encoding = "utf-8"
            soup = BeautifulSoup(r.text, "html.parser")
            thrui = soup.find("ul", class_="thrui")
            for li in thrui.find_all("li"):
                divs = li.find_all("div")
                weather_info["date"].append(divs[0].text)
                weather_info["max_temperature"].append(divs[1].text)
                weather_info["lowest_temperature"].append(divs[2].text)
                weather_info["weather"].append(divs[3].text)
                weather_info["wind_direction"].append(divs[4].text)
    return weather_info


def write_to_xlsx(weather_info):
    df = pd.DataFrame(weather_info)

    # 设置列名
    df.columns = ['date', 'max_temperature', 'lowest_temperature', 'weather', 'wind_direction']

    # 显示DataFrame
    df.to_excel("./天气数据.xlsx", index=False)


weather_info = get_weather_info()
write_to_xlsx(weather_info)
