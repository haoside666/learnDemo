package decorator

import "fmt"

type Component interface {
	Calc() int
}

type ConcreteComponent struct{}

func (*ConcreteComponent) Calc() int {
	return 0
}

type AddDecorator struct {
	Component
	num int
}

func WarpAddDecorator(c Component, num int) Component {
	return &AddDecorator{
		Component: c,
		num:       num,
	}
}

func (d *AddDecorator) Calc() int {
	return d.Component.Calc() + d.num
}

// ---------------------------------------测试--------------------------------------
func Test() {
	var c Component = &ConcreteComponent{}
	c = WarpAddDecorator(c, 10)
	res := c.Calc()

	fmt.Printf("res %d\n", res)

}
