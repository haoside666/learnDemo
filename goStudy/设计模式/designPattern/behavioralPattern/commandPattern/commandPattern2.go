package main

import "fmt"

type Cooker struct{}

func (c *Cooker) MakeChicken() {
	fmt.Println("烤串师傅烤了鸡肉串儿")
}

func (c *Cooker) MakeChuaner() {
	fmt.Println("烤串师傅烤了羊肉串儿")
}

type Cmd interface {
	Make()
}

type CmdCookChicken struct {
	cooker *Cooker
}

func (c *CmdCookChicken) Make() {
	c.cooker.MakeChicken()
}

type CmdCookChuaner struct {
	cooker *Cooker
}

func (c *CmdCookChuaner) Make() {
	c.cooker.MakeChuaner()
}

type WaiterMM struct {
	CmdList []Cmd //收集的命令集合
}

func (w *WaiterMM) Notify() {
	if w.CmdList == nil {
		return
	}

	for _, cmd := range w.CmdList {
		cmd.Make()
	}
}

func main() {
	cooker := new(Cooker)
	cmdChicken := CmdCookChicken{cooker}
	cmdChuaner := CmdCookChuaner{cooker}

	mm := new(WaiterMM)
	mm.CmdList = append(mm.CmdList, &cmdChicken)
	mm.CmdList = append(mm.CmdList, &cmdChuaner)

	mm.Notify()
}
