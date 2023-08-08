package fileStudy

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
)

func OsFileTest() {
	file, err := os.Open("./data.txt")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	reader := bufio.NewReader(file)

	for {
		line, err := reader.ReadString('\n')
		//if err != nil {
		if err == io.EOF {
			fmt.Println(err)
			break
		}
		fmt.Printf("%s", line)
	}
}

func OpenFileTest() {
	filePath := "./1.txt"
	file, err := os.OpenFile(filePath, os.O_WRONLY|os.O_CREATE, 0664)
	if err != nil {
		fmt.Println("文件打开失败", err)
	}
	//及时关闭file句柄
	defer file.Close()

	//写入文件时，使用带缓存的 *Writer
	write := bufio.NewWriter(file)
	for i := 0; i < 5; i++ {
		write.WriteString(strconv.FormatInt(int64(i+1), 10) + "\n")
	}
	//Flush将缓存的文件真正写入到文件中
	write.Flush()
}

func PathExists(path string) (bool, error) { //传送路径path
	_, err := os.Stat(path)
	if err == nil {
		return true, nil
	}
	if os.IsNotExist(err) {
		return false, nil
	}
	return false, err
}


func FileTest() {
	//创建文件
	file, err := os.OpenFile("./1.txt", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 664)
	if err != nil {
		fmt.Println(err)
		return
	}
	//写入文件
	for i := 0; i < 5; i++ {
		file.WriteString("ab")
		file.Write([]byte("cd"))
	}
	// 关闭文件
	file.Close()
	//读取文件
	file, err = os.Open("./1.txt")
	if err != nil {
		fmt.Println("open file failed!, err:", err)
		return
	}
	// 关闭文件
	defer file.Close()
	reader := bufio.NewReader(file)
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			if line != "" {
				fmt.Println(line)
			}
			return
		}
		fmt.Println(line)
	}
}

// 自己编写一个函数，接收两个文件路径 srcFileName dstFileName
func CopyFile(dstFileName string, srcFileName string) (written int64, err error) {
	srcFile, err := os.Open(srcFileName)
	if err != nil {
		fmt.Printf("open file err=%v\n", err)
	}
	defer srcFile.Close()
	//通过srcfile ,获取到 Reader
	reader := bufio.NewReader(srcFile)

	//打开dstFileName
	dstFile, err := os.OpenFile(dstFileName, os.O_WRONLY|os.O_CREATE, 0666)
	if err != nil {
		fmt.Printf("open file err=%v\n", err)
		return
	}

	//通过dstFile, 获取到 Writer
	writer := bufio.NewWriter(dstFile)
	defer dstFile.Close()
	return io.Copy(writer, reader)
}
