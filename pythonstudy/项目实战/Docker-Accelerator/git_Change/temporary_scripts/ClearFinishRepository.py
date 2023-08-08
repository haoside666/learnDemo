import subprocess
repository_path = "/home/haoside/Desktop/Docker-Accelerator-data/second/repository"

def clearFinishRepository():
    with open("../Dataset/PartThree/new_project_name_strip", "r") as file:
        for project_name in file:
            project_name=project_name.strip()
            project_root_path = f"{repository_path}/{project_name.replace('/', '##')}"
            command = f"rm -rf {project_root_path}"
            print(command)
            sp1 = subprocess.run(command, capture_output=True, shell=True)
            while sp1.returncode != 0:
                print("-----------------------------------------------------------")
                print(sp1.stderr.decode('utf-8', 'ignore'))
                print("-----------------------------------------------------------")
                sp1 = subprocess.run(command, capture_output=True, shell=True)


if __name__=="__main__":
    clearFinishRepository()