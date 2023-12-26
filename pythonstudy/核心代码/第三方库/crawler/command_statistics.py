import os

command_dict = {}
with open("./command_statistics/common_command.txt", "r", encoding="utf-8") as file:
    for line in file:
        key, value = tuple(line.split(maxsplit=1))

        key = key.strip()
        value = value.strip()
        command_dict[key] = value

print(command_dict)

filename="transfer.txt"

with open(f"./command_statistics/linux命令大全/category/{filename}", "r", encoding="utf-8") as file:
    l = []
    for line in file:
        l.append(line.split()[0].replace("命令", ""))

set1 = set(list(command_dict.keys()))
set2 = set(l)

common_elements = set1 & set2

union_list = []
for item in common_elements:
    value = command_dict[item]
    s = f'{item}\t\t{value}'
    union_list.append(s)
with open(f"./command_statistics/category/{filename}", "w",encoding="utf-8") as file:
    file.write("\n".join(union_list))


# with open(f"./command_statistics/RUN_statistic.txt", "r", encoding="utf-8") as file:
#     l = []
#     for line in file:
#         l.append(line.strip())
#
# set1 = set(list(command_dict.keys()))
# set2 = set(l)
# common_elements = set1 & set2
#
# union_list = []
# for item in common_elements:
#     value = command_dict[item]
#     s = f'{item}\t\t{value}'
#     union_list.append(s)
#
# with open(f"./command_statistics/common_command.txt", "w", encoding="utf-8") as file:
#     file.write("\n".join(union_list))
