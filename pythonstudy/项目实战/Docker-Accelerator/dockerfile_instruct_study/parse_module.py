import re


def sort_merged_list(merged_row):
    sorted_rows = sorted(merged_row, key=lambda x: x[1], reverse=True)
    return sorted_rows


def merge_same_item(parsed_row):
    d = {}
    for line in parsed_row:
        key = line[0]
        value = line[1]
        if key in d:
            d[key] = d[key] + value
        else:
            d[key] = value

    merged_row = []
    for k, v in d.items():
        merged_row.append([k, v])
    return merged_row


def from_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        imageName = line[0].strip()
        imageName = imageName.replace('"', '')
        # 去除前缀
        pattern = re.compile(r'--platform=[0-9a-zA-Z/]+ ')
        m = re.search(pattern, imageName)
        if m != None:
            imageName = imageName[m.span()[1]:]
        l = imageName.split()
        # 只保留image name和tag
        imageName = l[0]
        if "@" not in imageName and imageName.count(":") == 0:
            imageName = imageName + ":latest"
        parsed_row.append([imageName, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def strip_backslash(s):
    if len(s) > 1 and s[-1] == "\\" and s[-2] == "\\":
        s = s[:len(s) - 2].strip()
    if s == "": return s
    if s[-1] == "\\":
        s = s[:len(s) - 1].strip()
    elif s[-1] == ";":
        s = s[:len(s) - 1].strip()
    return s


def get_type(s):
    if s[0] == "-":
        return 0
    if "=" in s:
        return 1
    if "<" in s or "?" in s or s[0] == "_":
        return 3
    if ".tar" in s or ".zip" in s or ".txt" in s or ".conf" in s or ".deb" in s or ".jar" in s or ".js" in s:
        return 3
    if ".so" in s or ".dll" in s:
        return 3
    if "Microsoft" in s:
        return 3
    return 2
    # pattern = re.compile(r'[a-zA-Z]+[\w.\\\-\:/]*')
    # m = re.search(pattern, s)
    # if m != None:
    #     return 2
    # return 3


def check_assignment_format(s):
    if s.count("=") != 1:
        return False
    key, value = s.split("=")
    if key == "" or value == "":
        return False
    if "@" in key or "?" in key:
        return False
    if key[0] == "<":
        if key[-1] != ">":
            return False
    pattern = re.compile(r'\w')
    m = re.search(pattern, value)
    if m == None:
        return False
    return True


def get_types_and_exit_position(argv_list):
    types = []
    for argv in argv_list:
        types.append(get_type(argv))
    exit_pos = 0
    for i in range(len(types) - 1):
        if types[i + 1] > types[i]:
            exit_pos = exit_pos + 1
        else:
            break
    exit_pos = exit_pos + 1
    return [types, exit_pos]


def handle_quota(s):
    if '"' in s or "'" in s or "`" in s:
        double_quote_count = s.count('"')
        single_quote_count = s.count("'")
        backtick_count = s.count("`")
        if double_quote_count != 0:
            pattern = r'("[^"]*")'
            s = re.sub(pattern, lambda m: m.group(1).replace(' ', '___'), s)
        if single_quote_count != 0:
            pattern = r"('[^']*')"
            s = re.sub(pattern, lambda m: m.group(1).replace(' ', '___'), s)
        if backtick_count != 0:
            pattern = r"(`[^']*`)"
            s = re.sub(pattern, lambda m: m.group(1).replace(' ', '___'), s)
        return s.replace("'", "").replace('"', "").replace("`", "")
    else:
        return s


def second_classify(s):
    if s == "": return 3
    if "^" in s:
        return 3
    if ":" in s:
        if "+" in s:
            return 2
        elif ".exe" not in s and ".bat" not in s and ".ps1" not in s:
            return 3

    if "*" in s or "%" in s or "|" in s or "@" in s:
        return 3
    if "lib" in s or "Dockerfile" in s:
        return 3
    if s[0] == "#":
        return 3
    pattern = re.compile(r'[a-zA-Z]')
    m = re.search(pattern, s)
    if m == None:
        return 3
    return 2


def run_parse(filtered_rows, instruct):
    all_data = [[] for i in range(4)]
    for line in filtered_rows:
        argv = line[0].strip().replace("&", "").replace("\\,", ",")
        argv = handle_quota(strip_backslash(argv))
        err = False

        argv_list = argv.split()
        if "" in argv_list:
            continue
        types, exit_pos = get_types_and_exit_position(argv_list)
        length = len(argv_list)
        for i in range(exit_pos - 1):
            value = strip_backslash(argv_list[i])
            if types[i] == 0:
                if value.count("-") != len(value):
                    all_data[types[i]].append([value, line[1]])
            elif types[i] == 1:
                if check_assignment_format(value):
                    all_data[types[i]].append([value, line[1]])
                else:
                    err = True
                    break
            elif types[i] == 2:
                classify_type = second_classify(value)
                all_data[classify_type].append([value, line[1]])
            elif types[i] == 3:
                all_data[types[i]].append([value, line[1]])
        if err: continue
        # 去除最后的\
        data = " ".join([strip_backslash(argv_list[i]) for i in range(exit_pos - 1, length)])
        last_type = types[exit_pos - 1]
        value = argv_list[exit_pos - 1]
        data = data
        if last_type == 0:
            if value.count("-") != len(value):
                all_data[last_type].append([data, line[1]])
        elif last_type == 1:
            if check_assignment_format(value):
                all_data[last_type].append([data, line[1]])
            else:
                continue
        elif last_type == 2:
            classify_type = second_classify(value)
            all_data[classify_type].append([data, line[1]])
        elif last_type == 3:
            all_data[last_type].append([data, line[1]])
    with open(f"./{instruct}/data/split1.txt", 'w', encoding="utf-8") as file:
        for row in all_data[0]:
            file.write(f'{row[0]},{row[1]}' + '\n')
    with open(f"./{instruct}/data/split2.txt", 'w', encoding="utf-8") as file:
        for row in all_data[1]:
            file.write(f'{row[0]},{row[1]}' + '\n')
    with open(f"./{instruct}/data/split3.txt", 'w', encoding="utf-8") as file:
        for row in all_data[2]:
            file.write(f'{row[0]},{row[1]}' + '\n')
    with open(f"./{instruct}/data/split4.txt", 'w', encoding="utf-8") as file:
        for row in all_data[3]:
            file.write(f'{row[0]},{row[1]}' + '\n')


def cmd_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = line[0].strip()
        if argv[0] == "[" and argv[-1] == "]":
            argv = argv[1:len(argv) - 1]
            argv_list = argv.split(",")
            data = "[" + ",".join([strip_backslash(i) for i in argv_list]) + "]"
            parsed_row.append([data, line[1]])
        else:
            argv = handle_quota(argv)
            argv_list = [*filter(lambda x: x != "", argv.split())]
            argv_list = [*map(lambda x: x.replace("___", " ").strip(), argv_list)]
            data = "[" + ",".join([*map(lambda x: f'"{x}"', argv_list)]) + "]"
            parsed_row.append([data, line[1]])

    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def label_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = line[0].replace("'", "").replace('"', '').replace("\\", "").strip()
        if argv != "":
            parsed_row.append([argv, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def expose_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = line[0].strip().replace("/udp", "").replace("/tcp", "")
        argv_list = argv.split()
        argv_list = [*filter(lambda x: x.isdigit(), argv_list)]
        for item in argv_list:
            parsed_row.append([item, line[1]])

    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def env_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = strip_backslash(line[0].strip()).replace("\\,", ",")
        argv = handle_quota(argv)
        if "=" in argv:
            argv_list = argv.split()
            for item in argv_list:
                if check_assignment_format(item):
                    parsed_row.append([item, line[1]])
        else:
            argv_list = argv.split()
            length = len(argv_list)
            if length % 2 == 0:
                for i in range(length // 2):
                    item = argv_list[2 * i] + "=" + argv_list[2 * i + 1]
                    if check_assignment_format(item):
                        parsed_row.append([item, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def add_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        pattern = re.compile(r'--(chmod|chown)=[\w:]+')
        argv = re.sub(pattern, "", line[0].strip()).strip()
        parsed_row.append([argv, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def copy_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        pattern = re.compile(r'--(chmod|chown|from)=[+\w:.\-/]+')
        argv = re.sub(pattern, "", line[0].strip()).strip()
        argv = argv.replace("--link", "").strip()
        parsed_row.append([argv, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def user_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = strip_backslash(line[0])
        index = argv.find(":")
        if index != -1:
            argv = argv[:index]
        parsed_row.append([argv, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def workdir_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = line[0]
        argv = argv.replace('"', "").replace("'","").replace("[", "").replace("]", "").strip()
        if argv != "/":
            argv = argv[:len(argv) - 1] if argv[-1] == "/" else argv
        parsed_row.append([argv, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')


def arg_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = line[0]
        argv = argv.replace('"', "").replace("'","").strip()
        argv = strip_backslash(argv)
        argv_list=argv.split()
        length=len(argv_list)
        if length==1:
            if check_assignment_format(argv):
                parsed_row.append([argv, line[1]])
        elif length==2:
            argv="=".join(argv_list)
            if check_assignment_format(argv):
                parsed_row.append([argv, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')

def onbuild_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        argv = line[0]
        argv = strip_backslash(argv)
        if argv[-1]=="&" and argv[-2]=="&":
            argv = argv[:len(argv) - 2].strip()
        parsed_row.append([argv,line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')

def healthcheck_parse(filtered_rows, instruct):
    parsed_row = []
    for line in filtered_rows:
        pattern = re.compile(r'--(interval|timeout|start-period|start-interval|retries)=\w+')
        argv = re.sub(pattern, "", line[0].strip()).strip()
        argv = strip_backslash(argv)
        parsed_row.append([argv, line[1]])
    merged_row = merge_same_item(parsed_row)
    sorted_rows = sort_merged_list(merged_row)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')

def stopsignal_parse(filtered_rows, instruct):
    sorted_rows = sort_merged_list(filtered_rows)
    with open(f"./{instruct}/output_{instruct.lower()}.txt", 'w', encoding="utf-8") as file:
        for row in sorted_rows:
            file.write(f'{row[0]},{row[1]}' + '\n')



if __name__ == "__main__":
    l = ["8000-8005", "PORT", "8080", "12534", "\\", "<port>", "[<port>/<protocol>...]"]
    l = [*filter(lambda x: x.isdigit(), l)]
    print(l)
    s = "--from=/usr/src/target/spring-rest-data-demo-2.0.0.BUILD.jar /spring-rest-data-demo-2.0.0.BUILD.jar"
    pattern = re.compile(r'--(chmod|chown|from)=[+\w:.\-/]+')
    print(re.sub(pattern, "", s))

    # argv_list=["-abc","a-b=c","./a.sh"]
    # print(get_types_and_exit_position(argv_list))
    # argv_list = [";", "-abc","a-b=c","./a.sh"]
    # print(get_types_and_exit_position(argv_list))
    # argv_list = ["./a.sh",";", "-abc", "a-b=c"]
    # print(get_types_and_exit_position(argv_list))
