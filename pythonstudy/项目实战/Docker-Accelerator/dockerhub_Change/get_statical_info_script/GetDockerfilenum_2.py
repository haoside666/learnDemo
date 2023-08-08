import os
import json

def get_dir_list(root_dir_path):
    l=os.listdir(root_dir_path)
    return l



if __name__=="__main__":
    root_dir_path = "../res/github"
    if os.path.exists(f"./data/gdChange/dockerfile_num.txt"):
        os.remove(f"./data/gdChange/dockerfile_num.txt")
    for path in get_dir_list(root_dir_path):
        namespace_path = f"{root_dir_path}/{path}"
        for path1 in os.listdir(namespace_path):
            repository_path = f"{namespace_path}/{path1}"
            name=path+"/"+path1
            with open(f"{repository_path}/tags_time_order.json","r") as file:
                data = file.read()
                items = json.loads(data)
                nums=len(items)
            with open(f"./data/gdChange/dockerfile_num.txt","a") as file:
                file.write('{} {}\n'.format(name,nums))



