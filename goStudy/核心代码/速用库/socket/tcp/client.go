package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	// 客户端
	conn, err := net.Dial("tcp", ":8080")
	if err != nil {
		fmt.Println("连接服务器失败", err)
		return
	}
	fmt.Println("连接服务器成功", conn)

	for {
		// 输入数据切片类型
		fmt.Println("请发送数据 -> 客户端")
		var input []byte
		fmt.Scanln(&input)

		// 给服务器发送数据
		cnt, err := conn.Write([]byte(input))
		if err != nil {
			fmt.Println("给服务器发送数据失败", err)
			return
		}

		fmt.Println("给服务器发送数据成功", cnt)

		// 读取服务器发送的数据
		buf := make([]byte, 1024)
		n, err := conn.Read(buf)
		if err != nil {
			fmt.Println("读取服务器发送的数据失败", err)
			return
		}

		fmt.Println("读取服务器发送的数据成功", string(buf[:n]))

		time.Sleep(time.Second * 2)
	}
	// 关闭连接
	defer conn.Close()
}
