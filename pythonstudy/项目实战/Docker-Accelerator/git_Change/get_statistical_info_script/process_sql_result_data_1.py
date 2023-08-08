

def gitchange_sql_result_handler(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

        new_lines = []
        for line in lines:
            line = line.strip()
            line = line.replace(r"| https://github.com/","")
            l=line.split('|')
            l=[*filter(lambda x:x.strip()!='',l)]

            project_name=l[0].replace(".git","").strip()
            num=l[1].strip()
            new_lines.append(f'{project_name} {num}')

    with open("./data/PartThree/mType_info.txt", 'w') as file:
            file.write('\n'.join(new_lines))

def dockerhubchange_sql_result_handler(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

        new_lines = []
        for line in lines:
            line = line.strip()
            l=line.split('|')
            l=[*filter(lambda x:x.strip()!='',l)]

            project_name=l[0].strip()
            num=l[1].strip()
            new_lines.append(f'{project_name} {num}')

    with open(filename, 'w') as file:
            file.write('\n'.join(new_lines))

if __name__=="__main__":
    gitchange_sql_result_handler("./temp/sql_mType_info.txt")
    # dockerhubchange_sql_result_handler(".")