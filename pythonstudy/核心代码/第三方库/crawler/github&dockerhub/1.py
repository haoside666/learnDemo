import json
import os.path
import time
import traceback
from datetime import datetime

import requests


def post_query(query, page_number):
    try:
        response_result = requests.get(
            f"https://api.github.com/search/repositories?q={query}&page={page_number}",
            headers={"Authorization": "token " + "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"}
        )
        # print_logs("processing query === https://api.github.cm/search/repositories?q="+query+"&page="+str(page_number))
        # print("processing query === https://api.github.com/search/repositories?q="+query+"&page="+str(page_number))

        library_infos = response_result.json()
        js=json.dumps(library_infos)
        with open("../output.json", "a") as file:
            file.write(js)
            file.write("\n------------------------------------------------------------------\n")

        items=library_infos["items"]
        l=[]
        for i in items:
            l.append(i["full_name"])
        return l

    except:
        # metadata_error.write("https://api.github.com/search/repositories?q=" + query + "&page=" + str(page_number))
        print(traceback.format_exc())
        raise


if __name__=="__main__":
    if os.path.exists("../output.txt"):
        os.remove("../output.txt")
    query="stars:>100 +language:Dockerfile&type=Repositories"

    s=set()
    for num in range(30):
        for i in post_query(query,num):
            s.add(i)

    with open("../output.txt", "a") as file:
        file.write('\n'.join(s))
    print("exit")