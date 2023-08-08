import logging
import subprocess
import os
import global_config_var
import multiprocessing

logger = logging.getLogger('my_logger')


def clone_repository(project_name):
    project_root_path = f"{global_config_var.repository_path}/{project_name.replace('/', '##')}"
    # Do not clone if the folder exists
    if os.path.exists(project_root_path):
        logger.info("The clone project already exists, no cloning required!")
        return project_root_path
    else:
        command = f"git clone https://github.com/{project_name}.git {project_root_path}"
        logger.info("executive command:" + command)
        sp1 = subprocess.run(command, capture_output=True, shell=True)
        while sp1.returncode != 0:
            logger.info("-----------------------------------------------------------")
            logger.info(sp1.stderr.decode('utf-8', 'ignore'))
            logger.info("-----------------------------------------------------------")
            sp1 = subprocess.run(command, capture_output=True, shell=True)
        return project_root_path


def delete_repository(project_root_path):
    command = f"rm -rf {project_root_path}"
    logger.warning("executive command:" + command)
    sp1 = subprocess.run(command, capture_output=True, shell=True)
    while sp1.returncode != 0:
        logger.info("-----------------------------------------------------------")
        logger.info(sp1.stderr.decode('utf-8', 'ignore'))
        logger.info("-----------------------------------------------------------")
        sp1 = subprocess.run(command, capture_output=True, shell=True)
    return


def return_project_root_path(project_name):
    project_root_path = f"{global_config_var.repository_path}/{project_name.replace('/', '##')}"
    return project_root_path


if __name__ == "__main__":
    logger.setLevel(logging.INFO)
    console_handler = logging.StreamHandler()
    console_handler.setFormatter(logging.Formatter('%(asctime)s | %(levelname)s | %(message)s'))
    logger.addHandler(console_handler)

    with open(global_config_var.project_name_path, "r") as file:
        lines = file.readlines()
        lines = [*map(lambda x: x.strip(), lines)]
        pool = multiprocessing.Pool(3)
        results = pool.imap(clone_repository, lines, chunksize=5)
        for result in results:
            logger.info("-----project_root_path:" + result)
        pool.close()
        pool.join()
        # for project_name in file:
        #     project_root_path=clone_repository(project_name.strip())
