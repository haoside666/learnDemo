import json


def get_project_name_by_json(filename):
    with open(filename,"r") as file:
        data=file.read()
        items=json.loads(data)
        l=set()
        for item in items:
            l.add(item["github_full_name"])
    with open("../Dataset/PartThree/new_project_name_all", "w") as file:
        file.write('\n'.join(l))

def get_dict_by_json(filename):
    with open(filename,"r") as file:
        data=file.read()
        items=json.loads(data)
        l=set()
        for item in items:
            l.add(item["docker_name"]+" "+item["github_full_name"])
    with open("./temp/temp.txt", "w") as file:
        file.write('\n'.join(l))




if __name__=="__main__":
    filename= "./github_name_top_1000.json"
    # get_project_name_by_json(filename)
    get_dict_by_json(filename)


