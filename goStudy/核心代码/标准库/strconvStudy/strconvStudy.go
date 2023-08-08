package strconvStudy

import (
	"fmt"
	"strconv"
	"strings"
)

// StrconvTest1
func StrconvTest1() {
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

// base1原进制，base2变换后的进制，minLen是指变化后最小的长度(如100，若minLen<=3输出100，若minLen>3,则在前面补0)
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

// StrconvTest2
func StrconvTest2() {
	fmt.Println(mySysConvert("128", 10, 2, 10))
}

// StrconvTest3
func StrconvTest3() {
	//返回字符串s在go语法下的双引号字面值表示，控制字符、不可打印字符会进行转义。
	s := strconv.Quote(`"Fran & Freddie's Diner  ☺"`)
	fmt.Println(s)
	fmt.Println(`"Fran & Freddie's Diner  ☺"`)
}
