import subprocess
repository_path = "/home/haoside/Desktop/Docker-Accelerator-data/second/repository"

def clearNotExistCommit():
    d={}
    with open("../get_statistical_info_script/data/PartThree/dockerfile_commit_num.txt", "r") as file:
        for line in file:
            key,value=line.split()
            d[key]=value

    l=[]

    with open("../get_statistical_info_script/data/PartThree/dockerfile_num.txt","r") as file:
        for line in file:
            project_name=line.split()[0]
            l.append(f'{project_name} {d[project_name]}')
    with open("../get_statistical_info_script/data/PartThree/dockerfile_commit_num.txt", "w") as file:
        file.write('\n'.join(l))



if __name__=="__main__":
    clearNotExistCommit()