import json
import sys
import subprocess
import hashlib
import os

if len(sys.argv)!=2:
    print("please input imageID!!")
    exit(0)
if os.geteuid() != 0:
    print("Use root permission to execute the script!!!")
    exit(1)
inspect_info = subprocess.check_output(['docker','inspect',sys.argv[1]])
inspect_info = str(inspect_info, 'utf-8')

data=json.loads(inspect_info)
imageID=data[0]["Id"]
#适用于overlay2虚拟文件系统
print("镜像content描述信息:")
print("/var/lib/docker/image/overlay2/imagedb/content/sha256/"+imageID[7:])
print("----------------------------------------------------------------------\n")
diffIDs=data[0]["RootFS"]["Layers"]

print(f"diffIDs:")
for i in range(len(diffIDs)):
    print(f"第{i+1}层diffID: {diffIDs[i]}")
print("----------------------------------------------------------------------\n")
ChainIDs=[]
parentChainID=""

for diffID in diffIDs:
    if parentChainID=="":
        parentChainID=diffID
        ChainIDs.append(diffID)
    else:
        data=parentChainID+" "+diffID
        ChainID="sha256:"+hashlib.sha256(data.encode('utf-8')).hexdigest()
        parentChainID=ChainID
        ChainIDs.append(ChainID)
print(f"ChainIDs:")
for i in range(len(ChainIDs)):
    print(f"第{i+1}层ChainID: {ChainIDs[i]}")
print("----------------------------------------------------------------------\n")
cacheIDs=[]

for ChainID in ChainIDs:
    filePath="/var/lib/docker/image/overlay2/layerdb/sha256/"+ChainID[7:]+"/cache-id"

    with open(filePath,"r") as f:
        cacheIDs.append(f.read())

for i in range(len(cacheIDs)):
    print(f"第{i+1}层存储位置: /var/lib/docker/overlay2/{cacheIDs[i]}")
print("----------------------------------------------------------------------")



