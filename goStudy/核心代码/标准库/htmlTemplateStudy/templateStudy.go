package templateStudy

import (
	"fmt"
	"html/template"
	"net/http"
)

func sayHello(w http.ResponseWriter, r *http.Request) {
	// 解析指定文件生成模板对象
	tmpl, err := template.ParseFiles("./hello.html")
	if err != nil {
		fmt.Println("create template failed, err:", err)
		return
	}
	// 利用给定数据渲染模板，并将结果写入w
	tmpl.Execute(w, "world")
}

// TemplateTest1 测试hello模板
func TemplateTest1() {
	http.HandleFunc("/", sayHello)
	err := http.ListenAndServe(":8888", nil)
	if err != nil {
		fmt.Println("HTTP server failed,err:", err)
		return
	}
}

type UserInfo struct {
	Name   string
	Gender string
	Age    int
}

func testStruct(w http.ResponseWriter, r *http.Request) {
	tmpl, err := template.ParseFiles("./structTest.html")
	if err != nil {
		fmt.Println("create template failed, err:", err)
		return
	}
	// 利用给定数据渲染模板，并将结果写入w
	user := UserInfo{
		Name:   "枯藤",
		Gender: "男",
		Age:    18,
	}
	tmpl.Execute(w, user)
}

// TemplateTest2
func TemplateTest2() {
	http.HandleFunc("/", testStruct)
	err := http.ListenAndServe(":8888", nil)
	if err != nil {
		fmt.Println("HTTP server failed,err:", err)
		return
	}
}
