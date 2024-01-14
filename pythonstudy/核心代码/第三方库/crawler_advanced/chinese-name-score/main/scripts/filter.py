# -*- coding: utf-8 -*-

for line in open("../outputs/names_boys_source_wgl_hasguang.txt"):
    name = str(line).strip()

    if name == "":
        continue

    if "于光" in name:
        print(line[:-1])
