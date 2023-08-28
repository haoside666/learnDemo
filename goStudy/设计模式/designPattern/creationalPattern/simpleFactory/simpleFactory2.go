package main

//工厂（Factory）角色：简单工厂模式的核心，它负责实现创建**所有**实例的内部逻辑。工厂类可以被外界直接调用，创建所需的产品对象。
//抽象产品（AbstractProduct）角色：简单工厂模式所创建的所有对象的父类，它负责描述所有实例所共有的公共接口。
//具体产品（Concrete Product）角色：简单工厂模式所创建的具体实例对象。
import "fmt"

// ======= 抽象层 =========
// 水果类(抽象接口)
type Fruit2 interface {
	Show() //接口的某方法
}

// ======= 基础类模块 =========
type Apple2 struct {
	Fruit2 //为了易于理解显示继承(此行可以省略)
}

func (apple *Apple2) Show() {
	fmt.Println("我是苹果")
}

type Banana2 struct {
	Fruit2
}

func (banana *Banana2) Show() {
	fmt.Println("我是香蕉")
}

type Pear2 struct {
	Fruit2
}

func (pear *Pear2) Show() {
	fmt.Println("我是梨")
}

//type CreateFruit func() Fruit2

// 使用字典或者map去除if else结构
var (
	CreateFruitMap = map[string]Fruit2{
		"apple":  new(Apple2),
		"banana": new(Banana2),
		"pear":   new(Pear2),
	}
)

// ========= 工厂模块  =========
// 一个工厂， 有一个生产水果的机器，返回一个抽象水果的指针
type Factory2 struct{}

func (fac *Factory2) CreateFruit(kind string) Fruit2 {
	return CreateFruitMap[kind]
}

// ==========业务逻辑层==============
func main() {
	factory := new(Factory2)

	apple := factory.CreateFruit("apple")
	apple.Show()

	banana := factory.CreateFruit("banana")
	banana.Show()

	pear := factory.CreateFruit("pear")
	pear.Show()
}
