import re
def from_filter(item):
    baseimage=item[0]
    if "$" in baseimage or "{" in baseimage or "}" in baseimage:
        return False
    baseimage=baseimage.replace('"','')
    pattern = re.compile(r'\b(as|AS)\b')
    m = re.search(pattern, baseimage)
    if m!=None:
        baseimage= baseimage[:m.span()[0]].strip()
    if "@" in baseimage:
        return True
    else:
        return baseimage.count(":")<=1

def run_filter(item):
    command = item[0].strip()
    if "$" in command or command=="" or command[0]=="#":
        return False
    if "{" in command or "[" in command or "(" in command:
        return False
    if "}" in command or "]" in command or ")" in command:
        return False

    if '"' in command or "'" in command or "`" in command:
        double_quote_count = command.count('"')
        single_quote_count = command.count("'")
        backtick_count = command.count("`")
        if double_quote_count % 2 != 0 or single_quote_count % 2 != 0 or backtick_count % 2 != 0:
            return False

    pattern = re.compile(r'\w')
    m = re.search(pattern, command)
    if m==None:
        return False
    return True

def cmd_filter(item):
    command = item[0].strip()
    if "$" in command:
        return False
    if command.count("[")!=command.count("]"):
        return False
    return True




if __name__=="__main__":
    l1=["$BUILD_BASE",1]
    l2=["yoheimuta/protolint:latest as protolint",1]
    l3=["alpine:latest@sha256:7df6db5aa61ae9480f52f0b3a06a140ab98d427f86d8d5de0bedab9b8df6b1c0",2]
    l4=['"hurlenko/filebrowser:v2.11.0"',3]
    l=[l1,l2,l3,l4]
    for i in l:
        print(from_filter(i))
    print([*filter(from_filter,l)])
