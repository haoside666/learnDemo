import time

from selenium.webdriver import Chrome
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support.expected_conditions import title_contains
from selenium.webdriver.common.by import By

drive = Chrome()
drive.get("https://www.baidu.com")

drive.find_element_by_id("kw").send_keys("python" + Keys.ENTER)
WebDriverWait(drive, 10).until(title_contains("python"))

while True:
    h3_list = drive.find_elements(By.CSS_SELECTOR, "h3.t")
    for h3 in h3_list:
        print(h3.text)

    drive.find_element(By.XPATH, '//*[@id="page"]/div/a[last()]').click()
    time.sleep(3)
