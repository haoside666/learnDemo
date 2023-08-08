package logStudy

import (
	"fmt"
	"log"
	"os"
)

// LogTest1
// logger会打印每条日志信息的日期、时间，默认输出到系统的标准错误。
// Fatal系列函数会在写入日志信息后调用os.Exit(1)。
// Panic系列函数会在写入日志信息后panic。
func LogTest1() {
	log.Println("这是一条很普通的日志。")
	v := "很普通的"
	log.Printf("这是一条%s日志。\n", v)
	log.Fatalln("这是一条会触发fatal的日志。")
	log.Panicln("这是一条会触发panic的日志。")
}

// LogTest2 配置logger标志位
// const (
//
//	// 控制输出日志信息的细节，不能控制输出的顺序和格式。
//	// 输出的日志在每一项后会有一个冒号分隔：例如2009/01/23 01:23:23.123123 /a/b/c/d.go:23: message
//	Ldate         = 1 << iota     // 日期：2009/01/23
//	Ltime                         // 时间：01:23:23
//	Lmicroseconds                 // 微秒级别的时间：01:23:23.123123（用于增强Ltime位）
//	Llongfile                     // 文件全路径名+行号： /a/b/c/d.go:23
//	Lshortfile                    // 文件名+行号：d.go:23（会覆盖掉Llongfile）
//	LUTC                          // 使用UTC时间
//	LstdFlags     = Ldate | Ltime // 标准logger的初始值
//
// )
func LogTest2() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Println("这是一条修改配置后的日志")
}

// LogTest3 配置日志
func LogTest3() {
	log.SetPrefix("[info] ")
	log.Println("这是一条设置前缀后的日志")
}

// LogTest4 设置日志输出位置
func LogTest4() {
	logFile, err := os.OpenFile("./1.log", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		fmt.Println("open log file failed, err:", err)
		return
	}
	log.SetOutput(logFile)
	log.Println("这是一条普通的日志")
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Println("这是一条修改配置后的日志")
	log.SetPrefix("[info] ")
	log.Println("这是一条设置前缀后的日志")
}

// LogTest5 创建logger
// func New(out io.Writer, prefix string, flag int) *Logger
func LogTest5() {
	logger := log.New(os.Stdout, "<New>", log.Lshortfile|log.Ldate|log.Ltime)
	logger.Println("这是自定义的logger记录的日志。")
}
