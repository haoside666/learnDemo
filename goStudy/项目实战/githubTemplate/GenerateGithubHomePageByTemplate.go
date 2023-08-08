package main

import (
	"encoding/json"
	"fmt"
	"html/template"
	"os"
	"strings"
)

type Repo struct {
	Name        string `json:"Name"`
	URL         string `json:"URL"`
	Description string `json:"Description"`
}

type TemplateA struct {
	Name                    string   `json:"Name"`
	SelfDescription         string   `json:"SelfDescription"`
	Motto                   string   `json:"Motto"`
	GithubName              string   `json:"GithubName"`
	StudyContent            string   `json:"StudyContent"`
	StudyContentDescription string   `json:"StudyContentDescription"`
	RecentProjects          []Repo   `json:"RecentProjects"`
	LearnTechAbility        []string `json:"LearnTechAbility"`
	Email                   string   `json:"Email"`
}

func ReadConfig(filePath string) (data TemplateA, err error) {
	var file *os.File
	file, err = os.Open(filePath)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	decoder := json.NewDecoder(file)
	err = decoder.Decode(&data)
	if err != nil {
		fmt.Println("Error decoding JSON:", err)
		return
	}
	return
}

var (
	funcs = template.FuncMap{
		"join": strings.Join,
	}
)

func main() {
	data, err1 := ReadConfig("./config.json")
	if err1 == nil {
		fmt.Println("读取配置文件成功!")
		//fmt.Printf("%#v", data)
	}
	//注意new(模板名)，应该和第一个文件名相同。new和ParseFiles都会产生模板，模板要相关联才能建立成功。
	tmpl := template.Must(template.New("README.md.tpl").Funcs(funcs).ParseFiles("./README.md.tpl"))
	file, err2 := os.OpenFile("./README.md", os.O_TRUNC|os.O_WRONLY|os.O_CREATE, 0664)
	if err2 != nil {
		fmt.Println("create README.md failed, err:", err2)
		return
	}
	if err3 := tmpl.Execute(file, data); err3 != nil {
		fmt.Println("parse template failed, err:", err3)
	}

}
