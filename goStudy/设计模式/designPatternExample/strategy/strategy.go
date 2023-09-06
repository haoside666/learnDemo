package strategy

import "fmt"

type PaymentStrategy interface {
	Pay(*PaymentContext)
}

type PaymentContext struct {
	Name, CardID string
	Money        int
	payment      PaymentStrategy
}

func NewPaymentContext(name, cardid string, money int, payment PaymentStrategy) *PaymentContext {
	return &PaymentContext{
		Name:    name,
		CardID:  cardid,
		Money:   money,
		payment: payment,
	}
}

func (p *PaymentContext) Pay() {
	p.payment.Pay(p)
}

type Cash struct{}

func (*Cash) Pay(ctx *PaymentContext) {
	fmt.Printf("Pay $%d to %s by cash", ctx.Money, ctx.Name)
}

type Bank struct{}

func (*Bank) Pay(ctx *PaymentContext) {
	fmt.Printf("Pay $%d to %s by bank account %s", ctx.Money, ctx.Name, ctx.CardID)
}

// ---------------------------------------测试--------------------------------------
func ExamplePayByCash() {
	ctx := NewPaymentContext("Ada", "", 123, &Cash{})
	ctx.Pay()
}

func ExamplePayByBank() {
	ctx := NewPaymentContext("Bob", "0002", 888, &Bank{})
	ctx.Pay()
}

func Test() {
	ExamplePayByCash()
	fmt.Println("\n-----------------------------")
	ExamplePayByBank()
}
