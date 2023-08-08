import json
import time
import traceback
from datetime import datetime

import requests


def post_query(query, page_number):
    try:
        response_result = requests.get(
            f"https://api.github.com/search/repositories?q={query}&page={page_number}",
            headers={"Authorization": "token " + current_token}
        )
        print("processing query === https://api.github.com/search/repositories?q="+query+"&page="+str(page_number))

        library_infos = response_result.json()

        if "message" in library_infos:
            print(library_infos)
            return None

        time.sleep(1)
        return library_infos

    except:
        metadata_error.write("https://api.github.com/search/repositories?q=" + query + "&page=" + str(page_number))
        print(traceback.format_exc())

    return None



if __name__ == '__main__':
    page = 20

    for num in range(1,page+1):
        print(f"收集第{num}页")
        query="language:Dockerfile stars:>100"
        post_query(query,num)