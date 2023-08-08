import os

repository_path="/home/haoside/Desktop/Docker-Accelerator-data/second/repository"
output_path="/home/haoside/Desktop/Docker-Accelerator-data/second/output"

def readExistOutputProject():
    root_dir_path = output_path
    l=[path.replace("##", "/") for path in os.listdir(root_dir_path)]
    with open(f"./temp/exist_output_project.txt", "w") as file:
        file.write('\n'.join(l))

def readExistRepositoryProject():
    root_dir_path = repository_path
    l=[path.replace("##", "/") for path in os.listdir(root_dir_path)]
    with open(f"./temp/exist_repository_project.txt", "w") as file:
        file.write('\n'.join(l))

def splitProject():
    with open(f"../Dataset/PartThree/exist_project.txt", "r") as file:
        exist_name=[*map(lambda x:x.strip(),file.readlines())]

    with open("../Dataset/PartThree/new_project_name_all", "r") as file:
        all_name=[*map(lambda x:x.strip(),file.readlines())]

    for i in exist_name:
        if i in all_name:
            all_name.remove(i)

    with open("../Dataset/PartThree/new_project_name_strip", "w") as file:
        file.write('\n'.join(all_name))

    with open("../Dataset/PartThree/very_very_big_Project", "r") as file:
        for line in file:
            size,name=line.split()
            exist_name.remove(name)
    with open("../Dataset/PartThree/new_project_name_split01", "w") as file:
        file.write('\n'.join(exist_name))


def clearFinishProject():
    with open("./temp/Finished_project.txt","r") as file:
        finish_name=[*map(lambda x:x.strip(),file.readlines())]
    # with open("./temp/library_exist_project.txt","r") as file:
    #     library_name=[*map(lambda x:x.strip(),file.readlines())]
    # for i in finish_name:
    #     if i in library_name:
    #         library_name.remove(i)
    # print(library_name)
    with open("../Dataset/PartThree/new_project_name_strip", "r") as file:
        split01_name=[*map(lambda x:x.strip(),file.readlines())]
    for i in finish_name:
        split01_name.remove(i)
    with open("../Dataset/PartThree/new_project_name_split03_unfinish", "w") as file:
        file.write('\n'.join(split01_name))


if __name__=="__main__":
    readExistRepositoryProject()
    # splitProject()
    # clearFinishProject()