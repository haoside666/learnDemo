package main

import (
	"bufio"
	"fmt"
	"strings"
)

func bufioTest1() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Buffer(make([]byte, 1000000), 1000000)

	scanner.Scan()
	s := scanner.Text()
	_ = s // to avoid unused error
	scanner.Scan()
	krap := scanner.Text()
	_ = krap // to avoid unused error

	// fmt.Fprintln(os.Stderr, "Debug messages...")
	fmt.Println(strings.Replace(s, krap, "", -1)) 
}

func bufioTest2() {
	s := strings.NewReader("ABC DEF GHI JKL")
	bs := bufio.NewScanner(s)
	bs.Split(bufio.ScanWords)
	for bs.Scan() {
		fmt.Println(bs.Text())
	}
}

func bufioTest3() {
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

func main() {
	bufioTest1()
}