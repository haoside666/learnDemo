# 模拟浏览器打开python官网,然后爬取首页的介绍文本 https://www.python.org/
# 导入Chrome驱动库
from selenium.webdriver import Chrome
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By

# 创建驱动对象
driver = Chrome()
# 请求网页
driver.get("https://www.python.org/")

# 显式等待
WebDriverWait(driver, 10).until(lambda d: "Python" in d.title)

print(driver.find_element(By.XPATH, '//*[@id="touchnav-wrapper"]/header/div/div[3]/p').text)
