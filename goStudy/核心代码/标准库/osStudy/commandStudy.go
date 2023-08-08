package main
import (
    "os"
    "os/exec"
    "log"
)
//在环境变量 PATH 指定的目录中搜索可执行文件
func main() {
    cmd := exec.Command("ls","-l")
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err := cmd.Run()
	if err != nil {
    	log.Fatalf("cmd.Run() failed: %v\n", err)
	}
}
