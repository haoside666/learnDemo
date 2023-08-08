package ioStudy

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
)

// IoTest1
func IoTest1() {
	var buf [16]byte
	os.Stdin.Read(buf[:])
	os.Stdin.WriteString(string(buf[:]))
}

// IoTest2
// 文件操作API
// func Create(name string) (file *File, err Error)
//  根据提供的文件名创建新的文件，返回一个文件对象，默认权限是0666

//  func NewFile(fd uintptr, name string) *File
//  根据文件描述符创建相应的文件，返回一个文件对象

//  func Open(name string) (file *File, err Error)
//  只读方式打开一个名称为name的文件

//  func OpenFile(name string, flag int, perm uint32) (file *File, err Error)
//  打开名称为name的文件，flag是打开的方式，只读、读写等，perm是权限

//  func (file *File) Write(b []byte) (n int, err Error)
//  写入byte类型的信息到文件

//  func (file *File) WriteAt(b []byte, off int64) (n int, err Error)
//  在指定位置开始写入byte类型的信息

//  func (file *File) WriteString(s string) (ret int, err Error)
//  写入string信息到文件

//  func (file *File) Read(b []byte) (n int, err Error)
//  读取数据到b中

//  func (file *File) ReadAt(b []byte, off int64) (n int, err Error)
//  从off开始读取数据到b中

//  func Remove(name string) Error
//  删除文件名为name的文件

func IoTest2() {
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

// cat命令实现
func cat(r *bufio.Reader) {
	for {
		buf, err := r.ReadBytes('\n') //注意是字符
		if err == io.EOF {
			break
		}
		fmt.Fprintf(os.Stdout, "%s", buf)
	}
}

// IoTest3
func IoTest3() {
	flag.Parse() // 解析命令行参数
	if flag.NArg() == 0 {
		// 如果没有参数默认从标准输入读取内容
		cat(bufio.NewReader(os.Stdin))
	}
	// 依次读取每个指定文件的内容并打印到终端
	for i := 0; i < flag.NArg(); i++ {
		f, err := os.Open(flag.Arg(i))
		if err != nil {
			fmt.Fprintf(os.Stdout, "reading from %s failed, err:%v\n", flag.Arg(i), err)
			continue
		}
		cat(bufio.NewReader(f))
	}
}
