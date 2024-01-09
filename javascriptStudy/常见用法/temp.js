const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('请输入一些值，以空格分隔：', (inputString) => {
    // 使用 split(' ') 将输入字符串按空格分割成数组
    const inputs = inputString.split(' ');

    var list = []
    cnt = 0
    for (let i = 0; i < 5; i++) {
        const time = inputs[i];
        if (time == "DNF") {
            cnt += 1
        }else{
            list[i] = time
        }
    }
    list.sort((a, b) => a - b)
    // console.log(list)
    // console.log(cnt)
    switch (cnt) {
        case 0:
        case 1:
            output=((parseFloat(list[1])+parseFloat(list[2])+parseFloat(list[3]))/3).toFixed(2)
            break;
        // case 1:
        //     output=((parseFloat(list[1])+parseFloat(list[2])+parseFloat(list[3]))/3).toFixed(2)
        //     break;
        default:
            output = "DNF"
            break;
    }
    console.log(output)
    rl.close();
});

