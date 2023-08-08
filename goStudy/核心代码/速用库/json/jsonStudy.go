/*
json序列化与反序列化
json序列化:

	json.Marshal(data)  data可以为结构体，切片，map等

json反序列化:

	json.Unmarshal([]byte(s), &data) ==>针对字符串
	// 使用 json.NewDecoder 将 file 转换为 json.Decoder
	decoder := json.NewDecoder(file)
	err := decoder.Decode(&data)
*/
package jsonStudy

import (
	"encoding/json"
	"fmt"
	"os"
)

type any interface{}

type M struct {
	Name     string  `json:"姓名"`
	Age      int     `json:"年龄"`
	Birthday string  `json:"生日"`
	Sal      float64 `json:"薪水"`
	Skill    string  `json:"技能"`
}

func TestStruct() {
	m := M{
		Name:     "牛魔王",
		Age:      20,
		Birthday: "2011-11-11",
		Sal:      800000.00,
		Skill:    "牛魔权",
	}
	//将M序列化
	data, err := json.Marshal(&m) //使用json中的Marshal方法
	if err != nil {
		fmt.Printf("序列化失败:err:%v\n", err)
	}
	//输出序列化后的结果
	fmt.Printf("序列化后的结果:%v\n", string(data)) //字符串需要转化
}

func TestMap() {
	var a map[string]any
	//key为字符串，值为任意类型
	//使用map先make
	a = make(map[string]any)
	a["name"] = "红孩儿"
	a["age"] = 19
	a["address"] = "wuhan"

	data, err := json.Marshal(a) //使用json中的Marshal方法
	//map是引用传递，所以不需要取地址符号
	if err != nil {
		fmt.Printf("序列化失败:err:%v\n", err)
	}
	//输出序列化后的结果
	fmt.Printf("序列化后的结果:%v\n", string(data)) //字符串需要转化
}

func TestSlice() {
	//复杂化，一个切片中有很多map
	var slice []map[string]any

	s := make(map[string]any)
	u := make(map[string]any)
	s["name"] = "张三"
	s["age"] = 30
	s["address"] = "wuhan"
	slice = append(slice, s)

	u["name"] = "李四"
	u["age"] = 18
	u["address"] = "wuhan"
	u["sex"] = "男"
	slice = append(slice, u)

	data, err := json.Marshal(slice) //使用json中的Marshal方法
	//map是引用传递，所以不需要取地址符号
	if err != nil {
		fmt.Printf("序列化失败:err:%v\n", err)
	}
	//输出序列化后的结果
	fmt.Printf("序列化后的结果:%v\n", string(data)) //字符串需要转化
}

func TestNum() {
	var num float64 = 12313.122
	data, err := json.Marshal(num) //使用json中的Marshal方法
	if err != nil {
		fmt.Printf("序列化失败:err:%v\n", err)
	}
	fmt.Printf("普通数字序列化后的结果:%v\n", string(data)) //字符串需要转化
}

func AntiStruct() {
	s := `{"姓名":"牛魔王","年龄":20,"生日":"2011-11-11","薪水":800000,"技能":"牛魔权"}`
	var m M

	err := json.Unmarshal([]byte(s), &m)
	//必须要使用引用传递才可以改变函数外面的值
	if err != nil {
		fmt.Printf("unmarshal err=%v\n", err)
	}
	fmt.Printf("反序列化后,m=%v \n", m)
	fmt.Println("Name:=", m.Name)
}

func AntiMap() {
	s := `{"address":"wuhan","age":19,"name":"红孩儿"}`
	var m map[string]any

	err := json.Unmarshal([]byte(s), &m)
	//必须要使用引用传递才可以改变函数外面的值
	if err != nil {
		fmt.Printf("unmarshal err=%v\n", err)
	}
	fmt.Printf("反序列化后,m=%v \n", m)
}

func AntiSlice() {
	s := `[{"address":"wuhan","age":30,"name":"张三"},{"address":"wuhan","age":18,"name":"李四","sex":"男"}]`
	var slice []map[string]any
	err := json.Unmarshal([]byte(s), &slice)
	if err != nil {
		fmt.Printf("unmarshal err=%v\n", err)
	}
	fmt.Printf("反序列化后,slice=%v \n", slice)
}

func AntiNum() {
	s := `12313.122`
	var num float64
	err := json.Unmarshal([]byte(s), &num)
	if err != nil {
		fmt.Printf("unmarshal err=%v\n", err)
	}
	fmt.Printf("反序列化后,num=%v \n", num)

}

// 读取孩子名字和年龄
func TestFileJson() {
	filePath := "./jsonStudy/1.json"
	file, err := os.Open(filePath)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	var data map[string]any
	decoder := json.NewDecoder(file)
	err = decoder.Decode(&data)
	if err != nil {
		fmt.Println("Error decoding JSON:", err)
		return
	}
	//注意不能写[]any，[]any!=[]interface{}
	if childrens, ok := data["children"].([]interface{}); ok {
		for i, m := range childrens {
			if item, ok2 := m.(map[string]interface{}); ok2 {
				fmt.Printf(" children%d name:%v,age:%v\n", i+1, item["name"], item["age"])
			}
		}
	}

}

type Website struct {
	Name   string `xml:"name,attr"`
	Url    string
	Course []string
}

func WriteJson() {
	info := []Website{
		{"Golang", "http://c.biancheng.net/golang/", []string{"http://c.biancheng.net/cplus/", "http://c.biancheng.net/linux_tutorial/"}},
		{"Java", "http://c.biancheng.net/java/", []string{"http://c.biancheng.net/socket/", "http://c.biancheng.net/python/"}},
	}
	// 创建文件
	filePtr, err := os.Create("./jsonStudy/info.json")
	if err != nil {
		fmt.Println("文件创建失败", err.Error())
		return
	}
	defer filePtr.Close()
	// 创建Json编码器
	encoder := json.NewEncoder(filePtr)
	err = encoder.Encode(info)
	if err != nil {
		fmt.Println("编码错误", err.Error())
	} else {
		fmt.Println("编码成功")
	}
}
