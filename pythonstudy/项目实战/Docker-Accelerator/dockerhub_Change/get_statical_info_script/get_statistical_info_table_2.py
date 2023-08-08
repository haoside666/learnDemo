import pandas as pd
import numpy as np
def get_table():
    with open("data/library/dockerfile_num.txt", "r") as file:
        lines=file.readlines()
        project_names=[]
        nums=[]
        for line in lines:
            l = line.split()
            project_names.append(l[0])
            nums.append(l[1]+" "+l[1])
        d=dict(zip(project_names,nums))

    with open("data/library/dockerfile_tag_num.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l = line.split()
            project_name = l[0]
            tag_num = l[1]
            d[project_name] = d[project_name] + f" {tag_num}"

    with open("data/library/dockerfile_record.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            l=line.split()
            project_name=l[0]
            record_num=l[1]
            d[project_name]=d[project_name]+f" {record_num}"
    l = []
    for k,v in d.items():
        l1=v.split()
        if len(l1)==2:
            l1.append('0')
            l1.append('0')
        l1=[*map(int,l1)]
        l1.insert(0,k)
        l.append(l1)
    df = pd.DataFrame(l,columns=["name", "dockerfile_num", "total_tag_num","db_tag_num","record_num"])
    print(df.describe())
    print("-----------------------------------------\nmean():")
    print(df.mean())
    print("-----------------------------------------\nmedian():")
    print(df.median())
    # df.to_excel("./data/gdChange/Three_part_statistical_info.xlsx",header=["name", "dockerfile_num", "total_tag_num","db_tag_num","record_num"],index_label=range(1,len(l)+1))
    #
    # with open("data/gdChange/cmd_info.txt", "r") as file:
    #     lines = file.readlines()
    #     l=[]
    #     for line in lines:
    #         l1=line.split()
    #         l1[1]=int(l1[1])
    #         l.append(l1)
    #
    # df = pd.DataFrame(l,columns=["cmd", "count(cmd)"])
    # # 计算元素的百分比
    # total = df['count(cmd)'].sum()  # 计算总和
    # df['percentage'] = df['count(cmd)'] / total * 100  # 计算百分比
    # df.to_excel("./data/gdChange/Three_part_cmd_info.xlsx",header=["cmd", "count(cmd)","percentage"])
    #
    # with open("data/gdChange/mType_info.txt", "r") as file:
    #     lines = file.readlines()
    #     l=[]
    #     for line in lines:
    #         l1=line.split()
    #         l1[1]=int(l1[1])
    #         l.append(l1)
    #
    # df = pd.DataFrame(l,columns=["mType", "count(mType)"])
    # # 计算元素的百分比
    # total = df['count(mType)'].sum()  # 计算总和
    # df['percentage'] = df['count(mType)'] / total * 100  # 计算百分比
    # df.to_excel("./data/gdChange/Three_part_mType_info.xlsx",header=["cmd", "count(mType)","percentage"])


if __name__=="__main__":
    get_table()