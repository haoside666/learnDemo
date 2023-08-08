package jsonStudy

import (
	"encoding/xml"
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func XmlTest() {
	p := Person{"smiel", 19}
	fmt.Println("person = ", p)
	if data, err := xml.Marshal(p); err != nil {
		fmt.Println("err = ", err)
		return
	} else {
		fmt.Println(string(data))
	}
}
