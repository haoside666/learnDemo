package main

import (
	"github.com/gorilla/websocket"
	"log"
	"net/http"
	"strings"
)

// 其中CheckOringin是一个函数，该函数用于拦截或放行跨域请求。函数返回值为bool类型，即true放行，false拦截
var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
	CheckOrigin: func(r *http.Request) bool {
		return true
	},
}

//1.创建Upgrader,用于升级实例
//2.升级为websocket连接并获得一个conn实例
//3.ReadMessage 和 WriteMessage 用于读取和发送消息

func handleWebsocket(w http.ResponseWriter, r *http.Request) {
	//将http协议升级为websocket协议，前提为放行状态
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println(err)
		return
	}
	defer conn.Close()

	for {
		messageType, p, err := conn.ReadMessage()
		if err != nil {
			log.Println(err)
			return
		}
		log.Printf("received: %s", p)

		//lower := strings.ToLower(fstr)
		//字符串转大写
		//fstr := *(*string)(unsafe.Pointer(&p)) 强转，大数据性能更高，但可能存在安全隐患
		fstr := string(p)
		upperStr := strings.ToUpper(fstr)

		//err = conn.WriteMessage(messageType, *(*[]byte)(unsafe.Pointer(&upperStr)))
		err = conn.WriteMessage(messageType, ([]byte)(upperStr))
		if err != nil {
			log.Println(err)
			return
		}
	}
}

func main() {
	http.HandleFunc("/ws", handleWebsocket)
	log.Fatal(http.ListenAndServe(":8080", nil))
}
