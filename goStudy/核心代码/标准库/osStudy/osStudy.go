package main
import (
    "fmt"
    "os/exec"
)
//在环境变量 PATH 指定的目录中搜索可执行文件
func main() {
    f, err := exec.LookPath("ls")
    if err != nil {
        fmt.Println(err)
    }
    fmt.Println(f)
}
