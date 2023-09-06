package prototype

import "fmt"

// 抽象原型角色：声明用于复制自己的方法
type Prototype interface {
	Clone() Prototype
}

// 具体原型角色：实现Clone()方法并定义自己的属性和方法
type ConcretePrototype struct {
	name string
	age  int
}

func (cp *ConcretePrototype) Clone() Prototype {
	return &ConcretePrototype{
		name: cp.name,
		age:  cp.age,
	}
}

func (p *ConcretePrototype) GetName() string {
	return p.name
}

func (p *ConcretePrototype) SetName(name string) {
	p.name = name
}

func (p *ConcretePrototype) GetAge() int {
	return p.age
}

func (p *ConcretePrototype) SetAge(age int) {
	p.age = age
}

// ---------------------------------------测试--------------------------------------
func Test() {
	// 我们只需要调用一次构造方法，后面都是复制的
	original := &ConcretePrototype{name: "Original", age: 18}
	copy1 := original.Clone().(*ConcretePrototype)
	copy2 := original.Clone().(*ConcretePrototype)

	fmt.Printf("Original name: %s, age: %d\n", original.GetName(), original.GetAge())
	fmt.Printf("Copy 1 name: %s, age: %d\n", copy1.GetName(), copy1.GetAge())
	fmt.Printf("Copy 2 name: %s, age: %d\n", copy2.GetName(), copy2.GetAge())

	copy1.SetName("Copy 1")
	copy2.SetName("Copy 2")
	copy1.SetAge(20)
	copy2.SetAge(22)

	fmt.Printf("Original name: %s, age: %d\n", original.GetName(), original.GetAge())
	fmt.Printf("Copy 1 name: %s, age: %d\n", copy1.GetName(), copy1.GetAge())
	fmt.Printf("Copy 2 name: %s, age: %d\n", copy2.GetName(), copy2.GetAge())
}
