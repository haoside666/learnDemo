import os
import re
import global_config_var

def get_all_dockerfile_path(project_root_path):
    l=[]
    for root, dirs, files in os.walk(project_root_path, topdown=False):
        for name in files:
            if name!="tags_time_order.json":
                l.append(os.path.join(root,name))
    return l


def preprocess_dockerfile(dockerfile_path):
    with open(dockerfile_path, "r") as file:
        data = file.read()
        pattern = re.compile(r"\|\d.*?(RUN|\/bin\/bash -[a-zA-Z]+ pipefail -c (#\(nop\))*)[ ]*")
        data = re.sub(pattern, "RUN ", data)
        pattern = re.compile(r"\/bin\/bash -[a-zA-Z]+ pipefail -c (#\(nop\))*[ ]*")
        data=re.sub(pattern,"",data)
        data = data.replace("RUN RUN","RUN")
    with open(dockerfile_path,"w") as file:
        file.write(data)

def rename_dockerfile():
    root_dir_path = "./res/dockerfile/library"
    for path in os.listdir(root_dir_path):
        project_root_path = f"{root_dir_path}/{path}"
        os.rename(f"{project_root_path}/tags_time_order.txt",f"{project_root_path}/tags_time_order.json")



if __name__=="__main__":
    root_dir_path = global_config_var.root_dir_path
    print(os.path.abspath(root_dir_path))
    for path in os.listdir(root_dir_path):
        namespace_path = f"{root_dir_path}/{path}"
        for path1 in os.listdir(namespace_path):
            repository_path = f"{namespace_path}/{path1}"
            allDockerfilePath = get_all_dockerfile_path(repository_path)
            if allDockerfilePath:
                for dockerfile_path in allDockerfilePath:
                    preprocess_dockerfile(dockerfile_path)

