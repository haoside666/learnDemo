package fmtStudy

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Print系列
func FmtTest01() {
	fmt.Print("在终端打印该信息。")
	name := "枯藤"
	fmt.Printf("我是：%s\n", name)
	fmt.Println("在终端打印单独一行显示")
}

// Fprint系列
// Fprint系列函数会将内容输出到一个io.Writer接口类型的变量w中，我们通常用这个函数往文件中写入内容。
func FmtTest02() {
	fmt.Fprintln(os.Stdout, "向标准输出写入内容")
	fileObj, err := os.OpenFile("./1.txt", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		fmt.Println("打开文件出错,err:", err)
		return
	}
	name := "枯藤"
	// 向打开的文件句柄中写入内容
	fmt.Fprintf(fileObj, "往文件中写如信息：%s", name)
}

// Sprint系列
// Sprint系列函数会把传入的数据生成并返回一个字符串。
func FmtTest03() {
	s1 := fmt.Sprint("枯藤")
	name := "枯藤"
	age := 18
	s2 := fmt.Sprintf("name:%s,age:%d", name, age)
	s3 := fmt.Sprintln("枯藤")
	fmt.Println(s1, s2, s3)
}

// Errorf
// Errorf函数根据format参数生成格式化字符串并返回一个包含该字符串的错误。
func FmtTest04() {
	err := fmt.Errorf("这是一个错误%s", "!")
	fmt.Println(err)
}

// 格式化占位符
// 通用占位符
// %v	值的默认格式表示
// %+v	类似%v，但输出结构体时会添加字段名
// %#v	值的Go语法表示
// %T	打印值的类型

// 整形
// %b	表示为二进制
// %c	该值对应的unicode码值
// %d	表示为十进制
// %o	表示为八进制
// %x	表示为十六进制，使用a-f
// %X	表示为十六进制，使用A-F
// %U	表示为Unicode格式：U+1234，等价于”U+%04X”
// %q	该值对应的单引号括起来的go语法字符字面值，必要时会采用安全的转义表示

// 浮点型
//%b	无小数部分、二进制指数的科学计数法，如-123456p-78
//%e	科学计数法，如-1234.456e+78
//%E	科学计数法，如-1234.456E+78
//%f	有小数部分但无指数部分，如123.456
//%F	等价于%f
//%g	根据实际情况采用%e或%f格式（以获得更简洁、准确的输出）
//%G	根据实际情况采用%E或%F格式（以获得更简洁、准确的输出）

// 字符串和[]byte
// %s	直接输出字符串或者[]byte
// %q	该值对应的双引号括起来的go语法字符串字面值，必要时会采用安全的转义表示
// %x	每个字节用两字符十六进制数表示（使用a-f
// %X	每个字节用两字符十六进制数表示（使用A-F）

func FmtTest05() {
	o := struct{ name string }{"枯藤"}
	fmt.Printf("%v\n", o)
	fmt.Printf("%#v\n", o)
	fmt.Printf("%T\n", o)
	fmt.Printf("100%%\n")
	n := 65
	fmt.Printf("%b\n", n)
	fmt.Printf("%c\n", n)
	fmt.Printf("%d\n", n)
	fmt.Printf("%o\n", n)
	fmt.Printf("%x\n", n)
	fmt.Printf("%X\n", n)
	f := 12.34
	fmt.Printf("%b\n", f)
	fmt.Printf("%e\n", f)
	fmt.Printf("%E\n", f)
	fmt.Printf("%f\n", f)
	fmt.Printf("%g\n", f)
	fmt.Printf("%G\n", f)

	s := "枯藤"
	fmt.Printf("%s\n", s)
	fmt.Printf("%q\n", s)
	fmt.Printf("%x\n", s)
	fmt.Printf("%X\n", s)
}

// 实现将十六进制数转换为字符串
func FmtTest06() {
	s := "61626364"
	s1 := ""
	for i := 0; i < len(s)/2; i++ {
		s1 = s[2*i : 2*i+2]
		if v, err := strconv.ParseInt(s1, 16, 8); err == nil {
			fmt.Printf("%c", v)
		}
	}
}

// 输入scan scanf scanln
func FmtTest07() {
	var (
		name    string
		age     int
		married bool
	)
	//Scan从标准输入扫描文本，读取由空白符分隔的值保存到传递给本函数的参数中，换行符视为空白符。
	fmt.Scan(&name, &age, &married)
	fmt.Printf("扫描结果 name:%s age:%d married:%t \n", name, age, married)
	fmt.Scanf("%s %d %t", &name, &age, &married)
	fmt.Printf("扫描结果 name:%s age:%d married:%t \n", name, age, married)
	//Scanln类似Scan，它在遇到换行时才停止扫描。
	fmt.Scanln(&name, &age, &married)
	fmt.Printf("扫描结果 name:%s age:%d married:%t \n", name, age, married)

}

// 输入 bufio
func FmtTest08() {
	//Reader方法
	reader := bufio.NewReader(os.Stdin) // 从标准输入生成读对象
	fmt.Print("请输入内容：")
	text, _ := reader.ReadString('\n') // 读到换行
	text = strings.TrimSpace(text)
	fmt.Printf("%#v\n", text)

	//Scan方法
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Buffer(make([]byte, 1000000), 1000000)
	var length int
	scanner.Scan()
	fmt.Sscan(scanner.Text(), &length)
	scanner.Scan()
	array1 := scanner.Text()
	_ = array1 // to avoid unused error // The first array as a string.
	scanner.Scan()
	array2 := scanner.Text()
	_ = array2 // to avoid unused error // The second array as a string.
}

//Fscan从文件中读取
//Sscan从字符串中读取
