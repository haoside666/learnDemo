import logging
import subprocess
import argparse
import DockerfileChangeParse
import multiprocessing
import re
import GetMonitorList
import db_object
import gitChangeClass
import OperateRepository
import time
import global_config_var
import config

def parse_options():
    parser = argparse.ArgumentParser(description='Get the Dockerfile change.')
    parser.add_argument('--conf',help='Enter the path to the configuration file (file format is json)',required=True,metavar="config_file_path")
    args = parser.parse_args()
    return args


def get_all_commit(project_root_path):
    commit_info = bytes.decode(
        subprocess.check_output("git log | grep -E '^commit [0-9a-f]{40}'", shell=True, cwd=project_root_path))
    commits = commit_info.strip().split('\n')
    commits = [commit.split()[1] for commit in commits]
    return commits


def get_git_diff_argv(commits):
    gitDiffArgv = []
    for i in range(len(commits) - 1):
        gitDiffArgv.append((commits[i], commits[i + 1]))
    return gitDiffArgv


def split_program_segment(text):
    pattern = re.compile(r"diff --git ")
    l = re.split(pattern, text)
    l = [*filter(lambda x: x != "", l)]
    return l

# Pre-test functions
# def output_info_to_file(filename, data):
#     with open(filename, "w") as f:
#         f.write(data)
#
#
# def output_split_info_to_file(filename, list_data):
#     data = "##############################split##################################\n".join(list_data)
#     with open(filename, "w") as f:
#         if data != "":
#             f.write("##############################split##################################\n" + data)
#
#
# def output_result_info_to_file(filename, dict_data):
#     data = ""
#     for k, v in dict_data.items():
#         if "Dockerfile" in k:
#             data = data + f"############{k}###########\n{v}"
#         else:
#             data = data + f"############{k}###########\n{v}\n"
#
#     with open(filename, "w") as f:
#         if data != "":
#             f.write(data)
#
#
# def output_all_result_info_to_file(filename, result):
#     if not bool(result[1]): return
#     data = f"---------------------{result[0]}-------------------------\n"
#     for k, v in result[1].items():
#         data = data + f"############{k}###########\n{v}\n"
#
#     with open(filename, "a") as f:
#         f.write(data)
#
#
# def output_all_record_info_to_file(filename, d):
#     data = str(d)
#     with open(filename, "a") as f:
#         f.write(data)


def process(argv):
    project_root_path = sharedNamespace.project_root_path
    command = f"git diff --src-prefix=./ --dst-prefix=./ {argv[0]} {argv[1]}"
    sp1 = subprocess.run(command, capture_output=True, shell=True, cwd=project_root_path)
    if sp1.returncode != 0:
        print("-----------------------------------------------------------", flush=True)
        print(sp1.args, flush=True)
        print(sp1.stderr.decode('utf-8', 'ignore'), flush=True)
        print("-----------------------------------------------------------", flush=True)
        exit(1)
    text = sp1.stdout.decode('utf-8','ignore')
    program_segments = split_program_segment(text)

    all_mlist = sharedNamespace.all_mlist
    d = {}
    for segment in program_segments:
        end = segment.find(" ")
        curr_obj = segment[:end]

        for monitor_list, original_list, composite_list, paths_original in all_mlist:
            if curr_obj in monitor_list:
                if "Dockerfile" in curr_obj:
                    d[curr_obj] = segment
                else:
                    for i in monitor_list:
                        if "Dockerfile" in i:
                            dockerfile_path = i
                            break
                    values = dockerfile_path
                    if curr_obj in original_list:
                        if curr_obj not in d:
                            l = [f'{i["original"]} {i["start_line"]}\n' for i in paths_original if
                                 curr_obj in i["processed"]]
                            values = values + "\n" + ''.join(l)
                            d[curr_obj] = values + "1"
                            values = dockerfile_path
                        else:
                            index = d[curr_obj].rfind("\n")
                            frequency = int(d[curr_obj][index:])
                            d[curr_obj] = d[curr_obj][index + 1] + f"{frequency + 1}"
                    else:
                        for i in composite_list:
                            for k, v in i.items():
                                if curr_obj in v:
                                    if k not in d:
                                        l = [f'{i["original"]} {i["start_line"]}\n' for i in paths_original if
                                             k in i["processed"]]
                                        values = values + "\n" + ''.join(l)
                                        d[k] = values + "1"
                                        values = dockerfile_path
                                    else:
                                        index = d[k].rfind("\n")
                                        frequency = int(d[k][index:])
                                        d[k] = d[k][:index + 1] + f"{frequency + 1}"
                break
    l = []
    l.append(f"{argv[0]}-{argv[1]}")
    l.append(d)
    return l


if __name__ == "__main__":
    start = time.time()
    logger = logging.getLogger('my_logger')
    # Gets environment variable parameters
    args = parse_options()
    config_file_path = args.conf
    #Configuring global information
    config.set_config_info(config_file_path)
    #Initialization
    manager = multiprocessing.Manager()
    sharedNamespace = manager.Namespace()
    db = db_object.db()
    data = gitChangeClass.GitChange()
    try:
        with open(global_config_var.project_name_path, "r") as file:
        # with open("./Dataset/PartThree/temp", "r") as file:
            for project_name in file:
                project_name = project_name.strip()
                logger.warning(f"project_name:{project_name}")
                # project_root_path = OperateRepository.clone_repository(project_name)
                project_root_path = OperateRepository.return_project_root_path(project_name)
                # Get the monitor list
                all_mlist = GetMonitorList.get_monitor_list(project_root_path, project_name)
                if not all_mlist:
                    logger.warning(f"There is no Dockerfile in {project_root_path}")
                    # OperateRepository.delete_repository(project_root_path)
                    with open(f"{global_config_var.logs_path}/Finished_project.log", "a") as file:
                        file.write('{}\n'.format(project_name))
                    logger.warning(f"{project_name} Finished processing")
                    continue
                # Get all commit numbers
                commits = get_all_commit(project_root_path)
                gitDiffArgv = get_git_diff_argv(commits)

                # Set the shared Namespace
                sharedNamespace.all_mlist = all_mlist
                sharedNamespace.project_root_path = project_root_path

                data.set_pAddress(f"https://github.com/{project_name}.git")
                d = {}
                # Use process pools to process data
                pool = multiprocessing.Pool(4)
                # For special large projects use apply_async method
                # for i in gitDiffArgv:
                #     result = pool.apply_async(process, (i,)).get()
                # For general projects use imap method
                results = pool.imap(process, gitDiffArgv, chunksize=5)
                for result in results:
                    if not bool(result[1]): continue
                    two_commit = result[0].split("-")
                    d["newCommit"] = two_commit[0]
                    d["newCommitID"] = commits.index(two_commit[0])
                    d["oldCommit"] = two_commit[1]
                    d["oldCommitID"] = commits.index(two_commit[1])
                    l = []
                    for k, v in result[1].items():
                        if "Dockerfile" in k:
                            d["rAddress"] = k
                            d["addition"] = ""
                            records = DockerfileChangeParse.handle_internal_change(v)
                            for record in records:
                                d.update(record)
                                data.fill_data_by_dict(d)
                                l.append(data.data_to_tuple())
                        else:
                            records = DockerfileChangeParse.handle_external_change(v)
                            for record in records:
                                d.update(record)
                                data.fill_data_by_dict(d)
                                l.append(data.data_to_tuple())
                    db.insert_all_data_to_gdChange(l)
                pool.close()
                pool.join()
                with open(f"{global_config_var.logs_path}/Finished_project.log", "a") as file:
                    file.write('{}\n'.format(project_name))
                logger.warning(f"{project_name} Finished processing")
                # OperateRepository.delete_repository(project_root_path)
    except FileNotFoundError:
        logger.error(f"{global_config_var.project_name_path} is error,path not exist!!")
        exit(2)
    except Exception as e:
        logger.error(e.args)
        exit(3)
    end = time.time()
    print(end - start, 's')