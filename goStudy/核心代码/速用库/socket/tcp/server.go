package main

import (
	"fmt"
	"io"
	"net"
	"strings"
)

//服务器端
//1.监听(设置ip和端口以及网络协议类型)
//2.for循环接受客户端的连接请求
//3.数据处理

func main() {
	// 创建监听
	ip := "127.0.0.1"
	port := 8080
	address := fmt.Sprintf("%s:%d", ip, port) //Sprintf格式化并返回一个字符串而不打印它

	listener, err := net.Listen("tcp", address)

	if err != nil {
		fmt.Println("监听失败", err)
		return
	}
	defer listener.Close()
	fmt.Println("监听成功", address)

	// 清除终端
	fmt.Println("\033[2J")

	for {
		//listerner表示监听器，用于接收客户端的连接请求
		conn, err := listener.Accept() // 表示接受客户端的连接请求
		if err != nil {
			fmt.Println("接受客户端连接失败", err)
			return
		}
		fmt.Println("接受客户端连接成功", conn)

		go func() {
			for {
				// 读取客户端发送的数据
				buf := make([]byte, 1024) // 创建一个切片，用于存储客户端发送的数据
				n, err := conn.Read(buf)  // 读取客户端发送的数据
				if err != nil {
					if err == io.EOF {
						fmt.Printf("客户端(%v)退出\n", conn)
						return
					} else {
						fmt.Println("读取客户端发送的数据失败,退出\n", err)
						return
					}
				}
				fmt.Println("读取客户端发送的数据成功", string(buf[:n]))

				// 数据转化为大写
				upper := strings.ToUpper(string(buf[:n]))
				fmt.Println("转化为大写成功", upper)

				// 将数据转化为小写
				lower := strings.ToLower(string(buf[:n]))
				fmt.Println("转化为小写成功", lower)

				// 将数据写回给客户端
				conn.Write([]byte("upper:" + upper + "\n"))
				conn.Write([]byte("lower:" + lower + "\n"))

				// 给客户端发送数据
				conn.Write([]byte("hello, client"))
			}
			// 关闭连接
			conn.Close()
		}()
	}
}
