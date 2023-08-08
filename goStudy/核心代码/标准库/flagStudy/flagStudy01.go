package main
// 查看用法: ./main -help
// ./main -mode string
// 导入系统包
import (
    "flag"
    "fmt"
)

func parse(){
    // 定义命令行参数
    var mode = flag.String("mode", "", "process mode")
    // 解析命令行参数
    flag.Parse()
    // 输出命令行参数
    fmt.Println(*mode)
}

func main() {
    parse()
}
