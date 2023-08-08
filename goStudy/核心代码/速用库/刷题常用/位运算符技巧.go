package bitTech

import (
	"fmt"
	"math"
)

func BitTech01() {
	//乘以2的幂
	x := 3
	x = x << 1 //x=x*2
	x = x << 6 //x=x*64
	//计算两个数的中位数
	a := math.MaxInt
	b := math.MaxInt
	c := ((b - a) >> 2) + a //注意不能写成(a+b/2)会出现溢出
	fmt.Println(c)
	i := 7
	i = i ^ -1 + 1 //取相反数  i^-1 取反码
	fmt.Println(i)
	// (i % 2) == 0
	if (i & 1) == 0 {
		fmt.Println("i为偶数!")
	} else {
		fmt.Println("i为奇数!")
	}

}
