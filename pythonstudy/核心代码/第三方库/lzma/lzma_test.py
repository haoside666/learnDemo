import lzma
import tqdm
import json
def fun():
    with lzma.open('./outputs/gold.jsonl.xz', mode='wt') as out_file:
        with lzma.open('./inputs/gold.jsonl.xz', mode='rt') as file:
            all_lines = file.readlines()
            results = []
            for line in all_lines:
                data = json.loads(line.strip())
                result = data["type"]
                results.append(result)
            for result in tqdm.tqdm(results, total=len(all_lines), desc="Generating"):
                print(result)
                out_file.write('{}\n'.format(result))

def Wried_xz():
    with lzma.open('./test/test_o.xz', mode='wt') as out_file:
        results = [1,2,3,4,5,6,7,8,9,10]
        for result in tqdm.tqdm(results, total=len(results), desc="Generating"):
            print(result)
            out_file.write('{}\n'.format(result))
def Read_xz():
    with lzma.open('./test/test_o.xz', mode='rt') as file:
        all_lines = file.readlines()
        print(all_lines)

if __name__ == '__main__':
    Wried_xz()
    Read_xz()