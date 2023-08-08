import os
import subprocess
import multiprocessing
import db_object
import dockerhubChangeClass
import DockerfileChangeParse
import json
import config
import global_config_var
import logging
import argparse
import time


def parse_options():
    parser = argparse.ArgumentParser(description='Get the Dockerfile change.')
    parser.add_argument('--conf', help='Enter the path to the configuration file (file format is json)', required=True,
                        metavar="config_file_path")
    args = parser.parse_args()
    return args


def process(argv):
    command = f"diff -u {argv[0]}/linux_amd64 {argv[1]}/linux_amd64"
    program_path = sharedNamespace.program_path
    project_root_path = sharedNamespace.project_root_path
    tags = sharedNamespace.tags
    # diff 返回值:没有发现不同返回值为0，发现不同返回值为1，返回值为2则表明出现了错误
    sp1 = subprocess.run(command, capture_output=True, shell=True, cwd=program_path)
    if sp1.returncode == 2:
        print("-----------------------------------------------------------", flush=True)
        print(sp1.args, flush=True)
        print(sp1.stderr.decode('utf-8', 'ignore'), flush=True)
        print("-----------------------------------------------------------", flush=True)
        exit(1)
    else:
        text = sp1.stdout.decode('utf-8', 'ignore')
        if text == "":
            return []
        d = {}
        namespace_paths = project_root_path[:project_root_path.rfind("/")]

        d["namespace"] = os.path.basename(namespace_paths)
        d["repository"] = os.path.basename(project_root_path)
        d["newTag"] = os.path.basename(argv[0])
        d["newTagID"] = tags.index(argv[0])
        d["oldTag"] = os.path.basename(argv[1])
        d["oldTagID"] = tags.index(argv[1])
        d["addition"] = ""
        l = []
        data = dockerhubChangeClass.DockerhubChange()

        records = DockerfileChangeParse.handle_internal_change(text)
        for record in records:
            d.update(record)
            data.fill_data_by_dict(d)
            l.append(data.data_to_tuple())
        return l


def get_dir_list(root_dir_path):
    l = os.listdir(root_dir_path)
    return l


def get_dockerhub_diff_argv(tags):
    gitDiffArgv = []
    for i in range(len(tags) - 1):
        gitDiffArgv.append((f'{tags[i]}', f'{tags[i + 1]}'))
    return gitDiffArgv


if __name__ == "__main__":
    start = time.time()

    logger = logging.getLogger('my_logger')
    # Gets environment variable parameters
    args = parse_options()
    config_file_path = args.conf
    # Configuring global information
    config.set_config_info(config_file_path)
    # Initialization
    manager = multiprocessing.Manager()
    sharedNamespace = manager.Namespace()
    db = db_object.db()
    # Set the shared Namespace
    sharedNamespace.program_path = os.getcwd()
    # set root_dir_path
    root_dir_path = global_config_var.root_dir_path

    logger.info(f"The root directory for processing files is {root_dir_path}")
    for path in get_dir_list(root_dir_path):
        namespace_path = f"{root_dir_path}/{path}"
        for path1 in os.listdir(namespace_path):
            repository_path = f"{namespace_path}/{path1}"
            logger.info(f"repository_path:{repository_path}")
            with open(f"{repository_path}/tags_time_order.json", "r") as file:
                data = file.read()
                items = json.loads(data)
                tags = [f"{repository_path}/{item['name']}" for item in items]
            dockerhubDiffArgv = get_dockerhub_diff_argv(tags)
            # Set the shared Namespace
            sharedNamespace.project_root_path = repository_path
            sharedNamespace.tags = tags
            pool = multiprocessing.Pool()
            results = pool.imap(process, dockerhubDiffArgv, chunksize=50)
            results = [*filter(lambda x: x != [], results)]
            for result in results:
                db.insert_all_data_to_dockerhubChange(result)
            pool.close()
            pool.join()
            logger.info(f"{repository_path} Finished processing")

    logger.info('Exiting the application')
    end = time.time()
    print(end - start, 's')
