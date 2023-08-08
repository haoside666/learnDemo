import re
import os


def get_library_list():
    with open(f"./res/library.txt", 'r', encoding="utf-8") as file:
        library_list = [line.strip() for line in file]
    return library_list


def from_extract(rows, instruct):
    library_list = get_library_list()
    d1 = {}
    d2 = {}
    num1 = {}
    num2 = {}
    for line in rows:
        pattern = re.compile(r':.*?:')
        argv = re.sub(pattern, ":", line[0])
        name = argv.split(":")[0]
        name = name.replace("docker.io/", "").replace("library/", "")
        if name in library_list:
            if name in d1:
                d1[name].append(line)
            else:
                d1[name] = [line]
        else:
            if name in d2:
                d2[name].append(line)
            else:
                d2[name] = [line]

    for k, v in d1.items():
        num1[k] = sum([i[1] for i in v])
    for k, v in d2.items():
        num2[k] = sum([i[1] for i in v])
    t1 = sorted(num1.items(), key=lambda item: item[1], reverse=True)
    t2 = sorted(num2.items(), key=lambda item: item[1], reverse=True)

    if not os.path.exists(f"./{instruct}/extract"):
        os.mkdir(f"./{instruct}/extract")
    with open(f"./{instruct}/extract/library.txt", "w") as file:
        for t in t1:
            name = t[0]
            file.write(f"-----------------------{name}:{t[1]}---------------------------\n")
            file.write("\n".join([f'{item[0]},{item[1]}' for item in d1[name]]) + "\n")

    with open(f"./{instruct}/extract/not_library.txt", "w") as file:
        for t in t2:
            name = t[0]
            file.write(f"-----------------------{name}:{t[1]}---------------------------\n")
            file.write("\n".join([f'{item[0]},{item[1]}' for item in d2[name]]) + "\n")


def run_extract(rows, instruct):
    return


def cmd_extract(rows, instruct):
    return


def label_extract(rows, instruct):
    return


def expose_extract(rows, instruct):
    return


def env_extract(rows, instruct):
    return


def add_extract(rows, instruct):
    return


def copy_extract(rows, instruct):
    return


def user_extract(rows, instruct):
    return


def workdir_extract(rows, instruct):
    return


def arg_extract(rows, instruct):
    return


def onbuild_extract(rows, instruct):
    return


def healthcheck_extract(rows, instruct):
    return


if __name__ == "__main__":
    dict1 = {'a': "abc", 'b': "ab", 'c': "a", 'd': "abcde", 'e': "abcd"}
    dict2 = {'a': 3, 'b': 2, 'c': 1, 'd': 5, 'e': 4}

    # for i in dict2.items():
    #     print(i[0])
    # #key用来选取参与比较的元素
    # sorted_dict2 = sorted(dict2.items(), key=lambda x: dict1[x[0]])
    # print(sorted_dict2)
    print(sorted(dict1.items(), key=lambda item: dict2[item[0]]))
