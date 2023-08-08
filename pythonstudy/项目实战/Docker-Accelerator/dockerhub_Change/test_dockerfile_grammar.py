import dockerfile
import os
import global_config_var

error_file_path=f"{global_config_var.logs_path}/test_error.txt"
def get_copy_path(item,Dockerfile_path):
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
        # Check directives
        for directive in parsed:
            if directive.cmd not in VALID_DIRECTIVES:
                # Not valid dockerfile
                with open(error_file_path,"a") as file:
                    file.write('-------------------------------------------------------\n')
                    file.write('Dockerfile_path:{}\ndockerfile instruction is abnormal:\nfound invalid directive {}\n'.format(Dockerfile_path,directive.cmd))
                    file.write('\n------------------------------------------------------\n')
                continue
    except:
        raise

def read_dockerfile(dockerfile_path):
    try:
        with open(dockerfile_path, "r") as file:
            data = file.read()
            item = dockerfile.parse_string(data)
            return get_copy_path(item, dockerfile_path)
    except FileNotFoundError as e1:
        raise
    except Exception as e2:
        with open(error_file_path, "a") as file:
            file.write('-------------------------------------------------------\n')
            file.write('Dockerfile_path:{}\ndockerfile parse is abnormal:{}\n'.format(dockerfile_path,e2.args[0]))
            file.write('\n------------------------------------------------------\n')
        return [[],[]]
    except:
        print("An exception occurred reading Dockerfile")
        return []

def get_all_dockerfile_path(project_root_path):
    l=[]
    for root, dirs, files in os.walk(project_root_path, topdown=False):
        for name in files:
            if name!="tags_time_order.json":
                l.append(os.path.join(root,name))
    return l


if __name__=="__main__":
    if os.path.exists(error_file_path):
        os.remove(error_file_path)
    root_dir_path=global_config_var.root_dir_path
    for path in os.listdir(root_dir_path):
        namespace_path=f"{root_dir_path}/{path}"
        for path1 in os.listdir(namespace_path):
            repository_path=f"{namespace_path}/{path1}"
            allDockerfilePath = get_all_dockerfile_path(repository_path)
            if allDockerfilePath:
                for dockerfile_path in allDockerfilePath:
                    read_dockerfile(dockerfile_path)
