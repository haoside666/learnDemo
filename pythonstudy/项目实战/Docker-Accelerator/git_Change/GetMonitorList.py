import sys

import dockerfile
import os
import fnmatch
import subprocess
import global_config_var
import logging
from shutil import copyfile

logger = logging.getLogger('my_logger')
def get_copy_path(item, curr_path, project_name):
    VALID_DIRECTIVES = [
        'FROM',
        'RUN',
        'CMD',
        'LABEL',
        'MAINTAINER',
        'EXPOSE',
        'ENV',
        'ADD',
        'COPY',
        'ENTRYPOINT',
        'VOLUME',
        'USER',
        'WORKDIR',
        'ARG',
        'ONBUILD',
        'STOPSIGNAL',
        'HEALTHCHECK',
        'SHELL'
    ]
    try:
        parsed = item
        paths_info = []
        paths = []
        paths_original = []
        # Check directives
        for directive in parsed:
            if directive.cmd not in VALID_DIRECTIVES:
                # Not valid dockerfile
                with open(f"{global_config_var.logs_path}/error.log", "a") as file:
                    file.write('-------------------------------------------------------\n')
                    file.write(
                        'project_name:{}\ndockerfile instruction is abnormal:\nfound invalid directive {}\n'.format(
                            project_name, directive.cmd))
                    file.write('\n------------------------------------------------------\n')
                continue

            if directive.cmd == 'COPY':
                processed = "COPY "
                argument = []
                for i in range(len(directive.value) - 1):
                    path = curr_path + "/" + directive.value[i]
                    s = str(os.path.abspath(path))
                    l = []

                    if s[-2:] == "/*": s = s[:-2]
                    if "*" in s:
                        for root, dirs, files in os.walk(curr_path, topdown=False):
                            for name in files:
                                l.append(os.path.join(root, name))
                            for name in dirs:
                                l.append(os.path.join(root, name))
                        filtered_list = fnmatch.filter(l, s)
                        paths.append({s: filtered_list})
                        argument.append(s)
                    elif os.path.isdir(s):
                        for root, dirs, files in os.walk(s, topdown=False):
                            for name in files:
                                l.append(os.path.join(root, name))
                            for name in dirs:
                                l.append(os.path.join(root, name))
                        paths.append({str(os.path.abspath(path)): l})
                        argument.append(str(os.path.abspath(path)))
                    else:
                        paths.append(s)
                        argument.append(s)
                processed = processed + ' '.join(argument) + ' ' + directive.value[-1]
                paths_original.append(
                    {"processed": processed, "original": directive.original, "start_line": directive.start_line})
        paths_info.append(paths)
        paths_info.append(paths_original)
        return paths_info
    except:
        logger.error(
            f"project_name is {project_name},An exception is thrown when executing the get_copy_path function")
        exit(3)


def read_dockerfile(Dockerfile_path, project_name):
    try:
        with open(Dockerfile_path + "/Dockerfile", "r") as file:
            data = file.read()
            item = dockerfile.parse_string(data)
            return get_copy_path(item, Dockerfile_path, project_name)
    except FileNotFoundError:
        logger.error(f"project_name is {project_name},f{Dockerfile_path}/Dockerfile is not exist!!")
        exit(2)
    except Exception as e:
        with open(f"{global_config_var.logs_path}/error.log", "a") as file:
            file.write('-------------------------------------------------------\n')
            file.write('project_name:{}\ndockerfile parse is abnormal:{}\n'.format(project_name, e.args[0]))
            file.write('\n------------------------------------------------------\n')
        return [[], []]


def get_all_dockerfile_path(project_root_path):
    l = []
    for root, dirs, files in os.walk(project_root_path, topdown=False):
        for name in files:
            if name == "Dockerfile":
                l.append(os.path.join(root))
    return l


def get_monitor_list_by_paths(project_root_path, path, paths_info):
    split_result = []
    monitor_list = set()
    original_list = set()
    composite_list = []
    paths = paths_info[0]
    for i in paths:
        if isinstance(i, dict):
            for k, v in i.items():
                keys = k.replace(project_root_path, ".")
                values = []
                for value in v:
                    value = value.replace(project_root_path, ".")
                    monitor_list.add(value)
                    values.append(value)
                composite_list.append({keys: values})
        else:
            i = i.replace(project_root_path, ".")
            monitor_list.add(i)
            original_list.add(i)
    DockerfilePath = path + "/Dockerfile"
    monitor_list.add(DockerfilePath)
    original_list.add(DockerfilePath)

    split_result.append(monitor_list)
    split_result.append(original_list)
    split_result.append(composite_list)
    paths_original = []
    for d in paths_info[1]:
        d["processed"] = d["processed"].replace(project_root_path, ".")
        paths_original.append(d)
    split_result.append(paths_original)
    return split_result


def copy_all_dockerfile_to_library(allDockerfile, project_root_path, project_name):
    dirs = f"{global_config_var.output_path}/" + project_name.replace("/", "##")
    if os.path.exists(dirs):
        logger.info("The project dockerfile has already been copied, no need to copy!")
    else:
        try:
            os.mkdir(dirs)
            for path in allDockerfile:
                src_path = path + "/Dockerfile"
                dst_path = dirs + "/" + src_path.replace(project_root_path + "/", "").replace('/', '##')
                copyfile(src_path, dst_path)
        except Exception as e:
            logger.error(
                f"project_name is {project_name},An exception ({e.args}) is thrown when executing the copy_all_dockerfile_to_library function")
            command = f"rm -rf {dirs}"
            logger.warning("executive command:" + command)
            sp1 = subprocess.run(command, capture_output=True, shell=True)
            while sp1.returncode != 0:
                logger.info("-----------------------------------------------------------")
                logger.info(sp1.stderr.decode('utf-8', 'ignore'))
                logger.info("-----------------------------------------------------------")
                sp1 = subprocess.run(command, capture_output=True, shell=True)
            exit(1)
    return


def get_monitor_list(project_root_path, project_name):
    # Get the paths of all dockerfiles in the project
    allDockerfilePath = get_all_dockerfile_path(project_root_path)
    if allDockerfilePath:
        copy_all_dockerfile_to_library(allDockerfilePath, project_root_path, project_name)
        all_mlist = []
        for path in allDockerfilePath:
            paths_info = read_dockerfile(path, project_name)
            path = path.replace(project_root_path, ".")
            all_mlist.append(get_monitor_list_by_paths(project_root_path, path, paths_info))
        return all_mlist
    else:
        return []


if __name__ == "__main__":
    project_root_path = f"{global_config_var.repository_path}/cloud-custodian##cloud-custodian"
    project_name = "cloud-custodian/cloud-custodian"
    for i in get_monitor_list(project_root_path, project_name):
        print(i)
