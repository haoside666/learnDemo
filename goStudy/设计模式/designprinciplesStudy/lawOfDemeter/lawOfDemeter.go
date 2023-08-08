// 一个对象应当对其他对象尽可能少的了解，从而降低各个对象之间的耦合，提高系统的可维护性。
// 例如在一个程序中，各个模块之间相互调用时，通常会提供一个统一的接口来实现。
// 这样其他模块不需要了解另外一个模块的内部实现细节，这样当一个模块内部的实现发生改变时，不会影响其他模块的使用。
package main

import "fmt"

type Customer struct {
	id            int
	Name          string
	Type          int
	OrdersService OrdersService
}

type OrdersService interface {
	GetOrdersForCustomer(customer *Customer) []*Order
}

type Order struct {
	// 可以添加其他字段和初始化逻辑
	customId int
	orderId  int
	num      int
	name     string
	money    float64
}

// 普通用户没有折扣
type CustomOrder struct {
}

// 超级用户有折扣
type SuperCustomOrder struct {
	discount float64
}

func (c *CustomOrder) GetOrdersForCustomer(customer *Customer) []*Order {
	fmt.Println("custom order")
	return nil
}

func (c *SuperCustomOrder) GetOrdersForCustomer(customer *Customer) []*Order {
	fmt.Println("super custom order")
	fmt.Println("discount:", c.discount)
	return nil
}

var (
	TypeMapTable = map[int]OrdersService{
		1: &CustomOrder{},
		2: &SuperCustomOrder{
			discount: 0.6,
		},
	}
)

func main() {
	c := &Customer{
		Name: "xiaohong",
		Type: 1,
	}
	c.OrdersService = TypeMapTable[c.Type]
	c.OrdersService.GetOrdersForCustomer(c)
	c.Type = 2
	c.OrdersService = TypeMapTable[c.Type]
	c.OrdersService.GetOrdersForCustomer(c)
}
