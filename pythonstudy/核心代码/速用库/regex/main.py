import argparse
import re

def test(filepath):
    with open(filepath, "r") as file:
        code = file.read()

    file.close()
    code = re.sub('(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/', "", code)
    print(code)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--filename', nargs=1, type=str, help="Enter file path")
    args = parser.parse_args()
    test(args.filename[0])
