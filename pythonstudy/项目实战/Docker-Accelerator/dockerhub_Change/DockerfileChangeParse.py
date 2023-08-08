import os
import re
import subprocess


def split_diff_segment(text):
    pattern = re.compile(r"@@ *.+ @@")
    l1=re.findall(pattern,text)
    l2 = re.split(pattern, text)
    l2.pop(0)
    return zip(l1,l2)


def handle_internal_change(text):
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
    changeList = []
    for t in split_diff_segment(text):
        #Get initial line number information
        num_pipe=[0]*2
        num_info=t[0][4:]
        index=0
        for i in range(len(num_info)):
            if not num_info[i].isdigit():
                index=i
                break
        num_pipe[0]=int(num_info[:index])
        num_info=num_info[num_info.find("+")+1:]
        for i in range(len(num_info)):
            if not num_info[i].isdigit():
                index=i
                break
        num_pipe[1]=int(num_info[:index])
        #Parse changes

        lines=t[1].replace("\r\n","\n").split("\n")
        lines.pop(0)
        for line in lines:
            d={}
            if line!="" and line[0] in "-+":
                s=line[1:]
                parrern = re.compile(r"\w+")
                m = re.search(parrern,s)
                if m:
                    op=m.group(0)
                    index=m.span()[1]
                else:
                    op=""

                if op in VALID_DIRECTIVES:
                    cmd=op
                    argv=s[index:].strip()
                else:
                    cmd="RUN"
                    argv=s.strip()

                if line[0]=="-":
                    num_pipe[0] = num_pipe[0] + 1
                    d["mType"]="add"
                    d["changeNum"]=num_pipe[0]

                else:
                    num_pipe[1] = num_pipe[1] + 1
                    d["mType"] = "delete"
                    d["changeNum"]=num_pipe[1]
                d["cmd"] =cmd
                if len(argv)>500:
                    argv=argv[:500]

                d["cmdArgv"] = argv
                changeList.append(d)
            else:
                num_pipe[0]=num_pipe[0]+1
                num_pipe[1] = num_pipe[1] + 1
    return changeList



if __name__ == "__main__":
    text = '''--- ./Dockerfile
+++e/dev/null
@@ -1,2 +0,0 @@
-FROMescratch
@@ -1 +0,0 @@
-FROMescratch
@@ -1,2 +1 @@
-FROMescratch
'''
    for i in handle_internal_change(text):
        print(i)

    # command = f"diff -u Dockerfile1 Dockerfile2"
    # sp1 = subprocess.run(command,capture_output=True,shell=True)
    # #diff 返回值:没有发现不同返回值为0，发现不同返回值为1，返回值为2则表明出现了错误
    # if sp1.returncode!=2:
    #     text=sp1.stdout.decode('utf-8', 'ignore')
    #     for i in handle_internal_change(text):
    #         print(i)
    # else:
    #     raise subprocess.SubprocessError(f"Command '{command}' returned non-zero exit status 2.")

