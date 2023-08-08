import pandas as pd
def get_table():

    d={}
    with open("data/PartOne/dockerfile_num.txt", "r") as file:
        lines=file.readlines()
        for line in lines:
            l = line.split()
            project_name=l[0]
            dockerfile_num=int(l[1])
            d[project_name]=[0,0,0,0,0,0,0]
            d[project_name][0]=dockerfile_num


    with open("data/PartOne/dockerfile_commit_num.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l = line.split()
            project_name = l[0]
            commit_num = int(l[1])
            d[project_name][1] = commit_num

    with open("data/PartOne/dockerfile_commit_num_db_strip.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l = line.split()
            project_name = l[0]
            commit_num = int(l[1])
            d[project_name][2] = commit_num

    with open("data/PartOne/dockerfile_record_strip.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l=line.split()
            project_name=l[0]
            record_num=int(l[1])
            d[project_name][3]=record_num

    with open("data/PartOne/gitchange_add.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l = line.split()
            project_name = l[0]
            add_num = int(l[1])
            d[project_name][4] = add_num

    with open("data/PartOne/gitchange_delete.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l = line.split()
            project_name = l[0]
            delete_num = int(l[1])
            d[project_name][5] = delete_num

    with open("data/PartOne/gitchange_modify.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l = line.split()
            project_name = l[0]
            modify_num = int(l[1])
            d[project_name][6] = modify_num
    l=[]
    for k,v in d.items():
        v.insert(0,k)
        l.append(v)
    df = pd.DataFrame(l,columns=["project_name", "dockerfile_num", "total_commit_num","db_commit_num","record_num","add_num","delete_num","modify_num"],index=range(1,len(l)+1))

    # 计算元素的百分比
    df['percentage(add)'] = df['add_num'] / df['record_num'] * 100  # 计算百分比
    df['percentage(delete)'] = df['delete_num'] / df['record_num'] * 100  # 计算百分比
    df['percentage(modify)'] = df['modify_num'] / df['record_num'] * 100  # 计算百分比
    # df.to_excel("./data/PartThree/three_part_statistical_info.xlsx",header=["project_name", "dockerfile_num", "total_commit_num","db_commit_num","record_num","add_num","delete_num","modify_num","percentage(add)","percentage(delete)","percentage(modify)"],index_label=range(1,len(l)+1))
    print(df.describe())
    print("-----------------------------------------\nmean():")
    print(df.mean())
    print("-----------------------------------------\nmedian():")
    print(df.median())
    #
    # with open("./data/PartThree/cmd_info.txt", "r") as file:
    #     lines = file.readlines()
    #     l = []
    #     for line in lines:
    #         l1 = line.split()
    #         l1[1] = int(l1[1])
    #         l.append(l1)
    #
    # df = pd.DataFrame(l, columns=["cmd", "count(cmd)"])
    # # 计算元素的百分比
    # total = df['count(cmd)'].sum()  # 计算总和
    # df['percentage'] = df['count(cmd)'] / total * 100  # 计算百分比
    # df.to_excel("./data/PartThree/three_part_cmd_info.xlsx", header=["cmd", "count(cmd)", "percentage"])
    #
    # with open("./data/PartThree/mType_info.txt", "r") as file:
    #     lines = file.readlines()
    #     l = []
    #     for line in lines:
    #         l1 = line.split()
    #         l1[1] = int(l1[1])
    #         l.append(l1)
    #
    # df = pd.DataFrame(l, columns=["mType", "count(mType)"])
    # # 计算元素的百分比
    # total = df['count(mType)'].sum()  # 计算总和
    # df['percentage'] = df['count(mType)'] / total * 100  # 计算百分比
    # df.to_excel("./data/PartThree/three_part_mType_info.xlsx", header=["cmd", "count(mType)", "percentage"])

if __name__=="__main__":
    get_table()