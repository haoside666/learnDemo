package adapter

import (
	"fmt"
)

// Target 是适配的目标接口
type Target interface {
	Request() string
}

// Adaptee 是被适配的目标接口
type Adaptee interface {
	SpecificRequest() string
}

// AdapteeImpl 是被适配的目标类
type adapteeImpl struct{}

// NewAdaptee 是被适配接口的工厂函数
func NewAdaptee() Adaptee {
	return &adapteeImpl{}
}

// SpecificRequest 是目标类的一个方法
func (*adapteeImpl) SpecificRequest() string {
	return "adaptee method"
}

// Adapter 是转换Adaptee为Target接口的适配器
type adapter struct {
	Adaptee
}

// NewAdapter 是Adapter的工厂函数
func NewAdapter(adaptee Adaptee) Target {
	return &adapter{
		Adaptee: adaptee,
	}
}

// Request 实现Target接口
func (a *adapter) Request() string {
	return a.SpecificRequest()
}

// ---------------------------------------测试--------------------------------------
func Test() {
	adaptee := NewAdaptee()
	target := NewAdapter(adaptee)
	res := target.Request()
	fmt.Println(res)
}
