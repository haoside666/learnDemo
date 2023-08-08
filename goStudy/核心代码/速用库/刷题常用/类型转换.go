package main

import (
	"fmt"
	"math"
	"strconv"
)
//类型转换
func fun1() {
	var sum int = 17
	var count int = 5
	var mean float32
	mean = float32(sum) / float32(count)
	fmt.Printf("mean 的值为: %f\n", mean)

	age, _ := strconv.Atoi("19")
	fmt.Printf("%d\n", age)

	//parse系列函数 字符串转其他类型
	s := "111"
	num, _ := strconv.ParseInt(s, 10, 64)
	fmt.Println(num)

	s1 := "true"
	num1, _ := strconv.ParseBool(s1)
	fmt.Println(num1)

	s2 := "111.123"
	num2, _ := strconv.ParseFloat(s2, 64)
	fmt.Println(num2)
	//Format系列函数 给定类型转换为字符串
	res1 := strconv.FormatBool(true)
	res2 := strconv.FormatFloat(3.14150, 'f', 3, 64) // prec为-1表示使用最少数量表示,最后的0就省略了,如果prec为1,表示小数点后1位
	res3 := strconv.FormatInt(12, 16)
	res4 := strconv.FormatUint(17, 16)
	fmt.Printf("类型为：%T,值为：%s\n", res1, res1)
	fmt.Printf("类型为：%T,值为：%s\n", res2, res2)
	fmt.Printf("类型为：%T,值为：%s\n", res3, res3)
	fmt.Printf("类型为：%T,值为：%s\n", res4, res4)

}
//进制转换
func mySysConvert(s string, base1 int, base2 int, minLen int) string {
	var decimal int64
	decimal, _ = strconv.ParseInt(s, base1, 64)
	result := strconv.FormatInt(decimal, base2)
	if minLen != -1 {
		if len(result) < minLen {
			result = strings.Repeat("0", minLen-len(result)) + result
		}
	}
	return result
}

//四舍五入
func round(val float64, precision int) float64 {
	p := math.Pow10(precision)
	return math.Round(val*p) / p
}

func ceil(val float64, precision int) float64 {
	p := math.Pow10(precision)
	return math.Ceil(val*p) / p
}

func floor(val float64, precision int) float64 {
	p := math.Pow10(precision)
	return math.Floor(val*p) / p
}

func fun2() {
	fmt.Println(math.Round(49.89))
	fmt.Println(math.Round(49.45))

	fmt.Println(math.Ceil(49.89))
	fmt.Println(math.Ceil(49.45))

	fmt.Println(math.Floor(49.89))
	fmt.Println(math.Floor(49.45))

	fmt.Println(round(49.891, 2))
	fmt.Println(round(49.456, 2))

	fmt.Println(ceil(49.891, 2))
	fmt.Println(ceil(49.456, 2))

	fmt.Println(floor(49.891, 2))
	fmt.Println(floor(49.456, 2))
}

func main() {
	fun2()

}
