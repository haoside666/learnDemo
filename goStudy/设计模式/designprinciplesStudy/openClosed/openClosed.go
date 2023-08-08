// 开闭原则，类的改动是通过增加代码进行的，而不是修改源代码。
// 使用interface,下面例子显示了两者的差别
// 一个软件实体如类、模块和函数应该对扩展开放，对修改关闭。
package main

import "fmt"

// 我们要写一个类,Banker银行业务员
type Banker struct {
}

// 存款业务
func (this *Banker) Save() {
	fmt.Println("进行了 存款业务...")
}

// 转账业务
func (this *Banker) Transfer() {
	fmt.Println("进行了 转账业务...")
}

// 支付业务
func (this *Banker) Pay() {
	fmt.Println("进行了 支付业务...")
}

// 随着业务的增加,导致业务员模块越来越臃肿
func test() {
	banker := &Banker{}

	banker.Save()
	banker.Transfer()
	banker.Pay()
}

// 抽象的银行业务员
type AbstractBanker interface {
	DoBusi() //抽象的处理业务接口
}

// 存款的业务员
type SaveBanker struct {
	AbstractBanker
}

func (sb *SaveBanker) DoBusi() {
	fmt.Println("进行了存款")
}

// 转账的业务员
type TransferBanker struct {
	AbstractBanker
}

func (tb *TransferBanker) DoBusi() {
	fmt.Println("进行了转账")
}

// 支付的业务员
type PayBanker struct {
	AbstractBanker
}

func (pb *PayBanker) DoBusi() {
	fmt.Println("进行了支付")
}

func BankerBusiness(banker AbstractBanker) {
	//通过接口来向下调用，(多态现象)
	banker.DoBusi()
}

func test2() {
	//进行存款
	BankerBusiness(&SaveBanker{})

	//进行存款
	BankerBusiness(&TransferBanker{})

	//进行存款
	BankerBusiness(&PayBanker{})
}

func main() {

}
