import subprocess
import argparse
import re
import os
import sys
import commitInfoChangeClass
import config
import db_object
import OperateRepository
import multiprocessing
import logging
import time
import global_config_var


def parse_options():
    parser = argparse.ArgumentParser(description='Get the Dockerfile change.')
    parser.add_argument('--conf',help='Enter the path to the configuration file (file format is json)',required=True,metavar="config_file_path")
    args = parser.parse_args()
    return args

def get_program_segment(project_root_path):
    command = "git log --stat"
    sp1 = subprocess.run(command, capture_output=True, shell=True, cwd=project_root_path)
    if sp1.returncode != 0:
        print("-----------------------------------------------------------", flush=True)
        print(sp1.args, flush=True)
        print(sp1.stderr.decode('utf-8', 'ignore'), flush=True)
        print("-----------------------------------------------------------", flush=True)
        exit(1)
    text = sp1.stdout.decode('utf-8', 'ignore')
    return text


def split_program_segment(text):
    pattern = re.compile(r"commit [0-9a-f]{40}\n")
    heads = re.findall(pattern, text)
    heads = [*map(lambda x:x.strip(), heads)]
    bodys = re.split(pattern, text)
    bodys = [*filter(lambda x: x != "", bodys)]
    return (heads, bodys)



def process(project_name):
    # project_root_path = OperateRepository.clone_repository(project_name)
    project_root_path = OperateRepository.return_project_root_path(project_name)
    print(f"project_name:{project_name}",file=sys.stderr,flush=True)
    text = get_program_segment(project_root_path)
    heads,bodys=split_program_segment(text)

    l=[]
    data = commitInfoChangeClass.CommitInfoChange()
    d = {}
    d["projectName"]=os.path.basename(project_name)
    for i in range(len(heads)):
        head=heads[i]
        body=bodys[i]
        d["commitID"] = head.replace("commit ", "")
        pattern = re.compile("Author:.*")
        author = re.search(pattern, body).group()
        d["commitAuthor"]=author.replace("Author:","").strip()

        pattern = re.compile("Date:.*")
        m = re.search(pattern, body)
        date=m.group()
        date = date.replace("Date:","").strip()
        d["commitDate"]=date[:date.rfind(" ")]
        body=body[m.span()[1]:]


        pattern = re.compile(".*?\| +\d+ [\+-]+")
        m = re.search(pattern, body)
        if m:
            d["message"]=body[:m.span()[0]].strip()
            items = re.findall(pattern, body)
            for item in items:
                index=item.find("|")
                d["filePath"]=item[:index].strip()
                temp=item[index+1:].strip()
                d["changeNum"]=int(temp.find(" "))
                data.fill_data_by_dict(d)
                l.append(data.data_to_tuple())
        else:
            d["message"]=body.strip()
            d["filePath"]=""
            d["changeNum"]=""
            data.fill_data_by_dict(d)
            l.append(data.data_to_tuple())
    # OperateRepository.delete_repository(project_root_path)
    print(f"{project_name} Finished parsing",file=sys.stderr,flush=True)
    return l



if __name__ == "__main__":
    start = time.time()
    logger = logging.getLogger('my_logger')
    # Gets environment variable parameters
    args = parse_options()
    config_file_path = args.conf
    # Configuring global information
    config.set_config_info(config_file_path)
    # Initialization
    db = db_object.db()
    try:
        with open(global_config_var.project_name_path, "r") as file:
            project_names=file.readlines()
            project_names = [*map(lambda x: x.strip(), project_names)]
            # Use process pools to process data
            pool = multiprocessing.Pool(4)
            results = pool.imap(process, project_names, chunksize=5)
            for result in results:
                while len(result) > 100:
                    db.insert_all_data_to_commitInfoChange(result[:100])
                    result = result[100:]
                db.insert_all_data_to_commitInfoChange(result)
            pool.close()
            pool.join()
    except FileNotFoundError:
        logger.error(f"{global_config_var.project_name_path} is error,path not exist!!")
        exit(2)
    except Exception as e:
        print(e.args,file=sys.stderr)
        exit(3)
    logger.info('Exiting the application')
    end = time.time()
    print(end - start, 's')

