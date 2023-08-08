import os
import filter_module
import parse_module
import extract_module

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


def get_extractfunc_by_instruct(instruct):
    func = None
    if instruct == "FROM":
        func = extract_module.from_extract
    elif instruct == "RUN":
        func = extract_module.run_extract
    elif instruct == "CMD" or instruct == "ENTRYPOINT" or instruct == "VOLUME" or instruct == "SHELL":
        func = extract_module.cmd_extract
    elif instruct == "LABEL" or instruct == "MAINTAINER":
        func = extract_module.label_extract
    elif instruct == "EXPOSE":
        func = extract_module.expose_extract
    elif instruct == "ENV":
        func = extract_module.env_extract
    elif instruct == "ADD":
        func = extract_module.add_extract
    elif instruct == "COPY":
        func = extract_module.copy_extract
    elif instruct == "USER":
        func = extract_module.user_extract
    elif instruct == "WORKDIR":
        func = extract_module.workdir_extract
    elif instruct == "ARG":
        func = extract_module.arg_extract
    elif instruct == "ONBUILD":
        func = extract_module.onbuild_extract
    elif instruct == "HEALTHCHECK":
        func = extract_module.healthcheck_extract

    return func


def get_parsefunc_by_instruct(instruct):
    func = None
    if instruct == "FROM":
        func = parse_module.from_parse
    elif instruct == "RUN":
        func = parse_module.run_parse
    elif instruct == "CMD" or instruct == "ENTRYPOINT" or instruct == "VOLUME" or instruct == "SHELL":
        func = parse_module.cmd_parse
    elif instruct == "LABEL" or instruct == "MAINTAINER":
        func = parse_module.label_parse
    elif instruct == "EXPOSE":
        func = parse_module.expose_parse
    elif instruct == "ENV":
        func = parse_module.env_parse
    elif instruct == "ADD":
        func = parse_module.add_parse
    elif instruct == "COPY":
        func = parse_module.copy_parse
    elif instruct == "USER":
        func = parse_module.user_parse
    elif instruct == "WORKDIR":
        func = parse_module.workdir_parse
    elif instruct == "ARG":
        func = parse_module.arg_parse
    elif instruct == "ONBUILD":
        func = parse_module.onbuild_parse
    elif instruct == "HEALTHCHECK":
        func = parse_module.healthcheck_parse
    elif instruct == "STOPSIGNAL":
        func = parse_module.stopsignal_parse

    return func


def get_filterfunc_by_instruct(instruct):
    if instruct == "FROM":
        func = filter_module.from_filter
    elif instruct == "RUN":
        func = filter_module.run_filter
    elif instruct == "CMD" or instruct == "ENTRYPOINT" or instruct == "VOLUME":
        func = filter_module.cmd_filter
    elif instruct == "HEALTHCHECK":
        func = lambda x: "CMD" in x[0]
    else:
        func = lambda x: "$" not in x[0]
    return func


# def get_all_dir_name(current_dir_name):
#     curPathDirList = []
#     files = os.listdir(current_dir_name)
#     for f in files:
#         if os.path.isdir(current_dir_name + "/" + f):
#             curPathDirList.append(f)
#     return curPathDirList


def get_rows_by_instruct(instruct):
    rows = []
    with open(f'./{instruct}/output_{instruct.lower()}.csv', 'r', encoding="utf-8") as file:
        lines = file.readlines()
        for line in lines:
            l = line.split(",")
            l1 = []
            l1.append(",".join(l[1:-1]))
            l1.append(int(l[-1].strip()))
            rows.append(l1)
    return rows


def get_handled_data(instruct):
    rows = []
    if instruct != "RUN":
        with open(f'./{instruct}/output_{instruct.lower()}.txt', 'r', encoding="utf-8") as file:
            lines = file.readlines()
            for line in lines:
                l = line.rsplit(",", 1)
                l[1] = int(l[1].strip())
                rows.append(l)
    return rows


def handle_instruct(instruct):
    print("handle instruct:", instruct)
    rows = get_rows_by_instruct(instruct)
    print("len(rows):", len(rows))
    filter_func = get_filterfunc_by_instruct(instruct)
    filtered_rows = [*filter(filter_func, rows)]
    print("len(filtered_rows):", len(filtered_rows))
    parse_func = get_parsefunc_by_instruct(instruct)
    parse_func(filtered_rows, instruct)


def extract_instruct(instruct):
    print("extract instruct:", instruct)
    rows = get_handled_data(instruct)
    extract_func = get_extractfunc_by_instruct(instruct)
    if extract_func != None:
        extract_func(rows, instruct)


if __name__ == "__main__":
    for instruct in VALID_DIRECTIVES:
        # handle_instruct(instruct)
        extract_instruct(instruct)
