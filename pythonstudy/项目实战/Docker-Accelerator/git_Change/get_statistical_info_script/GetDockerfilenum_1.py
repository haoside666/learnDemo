import os
import subprocess
repository_path="/home/haoside/Desktop/Docker-Accelerator-data/second/repository"
output_path="/home/haoside/Desktop/Docker-Accelerator-data/second/output"


def readDockerfilenum():
    root_dir_path = output_path
    l=[]
    for path in os.listdir(root_dir_path):
        project_root_path = f"{root_dir_path}/{path}"
        name = path.replace("##", "/")
        nums = len(os.listdir(project_root_path))
        l.append(f'{name} {nums}')
        with open(f"./data/PartThree/dockerfile_num.txt", "w") as file:
            file.write('\n'.join(l))



if __name__=="__main__":
    readDockerfilenum()


