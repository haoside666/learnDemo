import subprocess
import os
repository_path="/home/haoside/Desktop/Docker-Accelerator-data/second/repository"
def get_all_commit(project_root_path):
    commit_info = bytes.decode(
        subprocess.check_output("git log | grep -E '^commit [0-9a-f]{40}'", shell=True, cwd=project_root_path))
    commits = commit_info.strip().split('\n')
    commits = [commit.split()[1] for commit in commits]
    return commits

if __name__ == "__main__":
    project_name_path = "../Dataset/PartThree/new_project_name_all"
    with open(project_name_path, "r") as file:
        for project_name in file:
            project_name = project_name.strip()
            project_root_path = f"{repository_path}/{project_name.replace('/', '##')}"
            # Get all commit numbers
            commits = get_all_commit(project_root_path)
            with open(f"./temp/dockerfile_commit_num.txt", "a") as file:
                file.write('{} {}\n'.format(project_name, len(commits)))
