package simple_factory

import (
	"fmt"
)

type API interface {
	Say(name string) string
}

func NewAPI(t int) API {
	if t == 1 {
		return new(hiAPI)
	} else if t == 2 {
		return new(helloAPI)
	}
	return nil
}

type hiAPI struct{}

func (*hiAPI) Say(name string) string {
	return fmt.Sprintf("hi,%s", name)
}

type helloAPI struct{}

func (*helloAPI) Say(name string) string {
	return fmt.Sprintf("hello,%s", name)
}

func TestType1() {
	api := NewAPI(1)
	s := api.Say("Tom")
	fmt.Println(s)
	if s != "hi,Tom" {
		fmt.Println("Type1 test fail")
	}
}

func TestType2() {
	api := NewAPI(2)
	s := api.Say("Tom")
	fmt.Println(s)
	if s != "hello,Tom" {
		fmt.Println("Type2 test fail")
	}
}

func Test() {
	TestType1()
	TestType2()
}
