
def handle_header():
    with open("./1.txt") as file:
        lines=file.readlines()
        length=len(lines)//2
        d={}
        for i in range(length):
            key=lines[2*i].replace(":","").strip()
            value=lines[2*i+1].strip()
            d[key]=value
        print(d)

def handle_header2():
    with open("./1.txt") as file:
        lines = file.readlines()
        length = len(lines) // 2
        d = {}
        for i in range(length):
            key = lines[2 * i].strip()
            value = lines[2 * i + 1].strip()
            d[key] = value

        for k,v in d.items():
            print(k,v)


if __name__=="__main__":
    handle_header2()
