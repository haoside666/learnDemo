package main

import "fmt"

// 抽象的主题
type BeautyWoman interface {
	//对男人抛媚眼
	MakeEyesWithMan()
	//和男人浪漫的约会
	HappyWithMan()
}

type PanJinLian struct{}

func (p *PanJinLian) MakeEyesWithMan() {
	fmt.Println("潘金莲对本官抛了个媚眼")
}

func (p *PanJinLian) HappyWithMan() {
	fmt.Println("潘金莲和本官共度了浪漫的约会")
}

type wangPo struct {
	woman BeautyWoman
}

func NewProxy2(woman BeautyWoman) BeautyWoman {
	return &wangPo{woman}
}

func (p *wangPo) MakeEyesWithMan() {
	p.woman.MakeEyesWithMan()
}

func (p *wangPo) HappyWithMan() {
	p.woman.HappyWithMan()
}

// 西门大官人
func main() {
	//大官人想找金莲，让王婆来安排
	wangpo := NewProxy2(new(PanJinLian))
	//王婆命令潘金莲抛媚眼
	wangpo.MakeEyesWithMan()
	//王婆命令潘金莲和西门庆约会
	wangpo.HappyWithMan()
}
