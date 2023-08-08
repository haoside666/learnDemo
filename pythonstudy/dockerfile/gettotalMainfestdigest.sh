#!/usr/bin/python3
import json
import sys
if len(sys.argv)!=2:
    print("please input filename!!")
    exit(0)
with open(sys.argv[1], "r") as f_r:
    str=f_r.read()
    data = json.loads(str)
    manifests=[]
    manifest={}
    for i in data['manifests']:
        manifest['digest']=i['digest']
        manifest['mediaType'] = i['mediaType']
        manifest['platform'] = i['platform']
        manifest['size'] = i['size']
        manifests.append(manifest.copy())

    data1={}
    data1['manifests']=manifests
    data1['mediaType']=data['mediaType']
    data1['schemaVersion']=data['schemaVersion']
    output = json.dumps(data1)
    output=output.replace("/","\/")
    output=output.replace(" ","")
    output=output.replace("\t","")
    output=output.replace("\n","")
with open("2.json", "w") as f_w:
    f_w.write(output)
