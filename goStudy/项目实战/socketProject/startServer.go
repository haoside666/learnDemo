package main

import (
	"encoding/json"
	"fmt"
	"github.com/gorilla/mux"
	"github.com/gorilla/websocket"
	"net/http"
)

type Data struct {
	Ip       string   `json:"ip"`
	User     string   `json:"user"`
	From     string   `json:"from"`
	Type     string   `json:"type"`
	Content  string   `json:"content"`
	UserList []string `json:"user_list"`
}

type connection struct {
	ws *websocket.Conn
	//sc消息，用于发送数据给客户端
	sc   chan []byte
	data *Data
}

type hub struct {
	c map[*connection]bool
	b chan []byte
	r chan *connection
}

var wu = &websocket.Upgrader{
	ReadBufferSize:  512,
	WriteBufferSize: 512,
	CheckOrigin: func(r *http.Request) bool {
		return true
	},
}

var user_list = []string{}

var h = hub{
	//所有用户信息
	c: make(map[*connection]bool),
	//全局用户信息队列
	b: make(chan []byte),
	//连接对象通道，用于交互信息
	r: make(chan *connection),
}

func (h *hub) run() {
	for {
		select {
		case c := <-h.r:
			//设置当前连接对象为激活状态，填充当前连接对象的data和sc信息
			h.c[c] = true
			c.data.Ip = c.ws.RemoteAddr().String()
			c.data.Type = "handshake"
			c.data.UserList = user_list
			data_b, _ := json.Marshal(c.data)
			c.sc <- data_b
		case data := <-h.b:
			//全局用户信息队列收到信息，填充每一个客户端所在sc信息
			for c := range h.c {
				select {
				//如果连接的客户端消息通道为空，则发送消息给该客户端
				case c.sc <- data:
				//如果通道满了(比如用户a刚创建，此时用户c发了一条消息,用户a创建的通道信息还没有广播出去，直接删除用户a,解决冲突问题)
				default:
					delete(h.c, c)
					close(c.sc)
				}
			}
		}
	}
}

func myws(w http.ResponseWriter, r *http.Request) {
	//收到http请求，判断是否支持webSocket,支持升级为webSocket,不支持退出当前会话
	ws, err := wu.Upgrade(w, r, nil)
	if err != nil {
		return
	}
	//初始化connection对象
	c := &connection{sc: make(chan []byte, 256), ws: ws, data: &Data{}}
	h.r <- c
	go c.writer()
	c.reader()
	defer func() {
		c.data.Type = "logout"
		user_list = del(user_list, c.data.User)
		c.data.UserList = user_list
		c.data.Content = c.data.User
		data_b, _ := json.Marshal(c.data)
		h.b <- data_b
		h.r <- c
	}()
}

func (c *connection) writer() {
	//若有sc信息，则发送给当前连接对象的客户端
	for message := range c.sc {
		c.ws.WriteMessage(websocket.TextMessage, message)
	}
	c.ws.Close()
}

func (c *connection) reader() {
	for {
		_, message, err := c.ws.ReadMessage()
		if err != nil {
			h.r <- c
			break
		}
		json.Unmarshal(message, &c.data)
		switch c.data.Type {
		case "login":
			//收到登录类型请求包，添加当前用户到用户列表，更新当前用户信息，转换当前用户信息，发送给服务器全局信息队列(或数组)
			c.data.User = c.data.Content
			c.data.From = c.data.User
			user_list = append(user_list, c.data.User)
			c.data.UserList = user_list
			data_b, _ := json.Marshal(c.data)
			h.b <- data_b
			//收到用户消息包，发送消息给全局队列
		case "user":
			c.data.Type = "user"
			data_b, _ := json.Marshal(c.data)
			h.b <- data_b
		case "logout":
			c.data.Type = "logout"
			user_list = del(user_list, c.data.User)
			data_b, _ := json.Marshal(c.data)
			h.b <- data_b
			h.r <- c
		default:
			fmt.Print("========default================")
		}
	}
}

func del(slice []string, user string) []string {
	count := len(slice)
	if count == 0 {
		return slice
	}
	if count == 1 && slice[0] == user {
		return []string{}
	}
	var n_slice = []string{}
	for i := range slice {
		if slice[i] == user && i == count-1 {
			return slice[:count-1]
		} else if slice[i] == user {
			n_slice = append(slice[:i], slice[i+1:]...)
			break
		}
	}
	fmt.Println(n_slice)
	return n_slice
}

func main() {
	router := mux.NewRouter()
	go h.run()
	router.HandleFunc("/ws", myws)
	if err := http.ListenAndServe("127.0.0.1:8080", router); err != nil {
		fmt.Println("err:", err)
	}
}
