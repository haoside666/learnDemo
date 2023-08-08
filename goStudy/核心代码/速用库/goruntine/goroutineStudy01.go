package goroutineStudy

import (
	"fmt"
	"runtime"
	"strconv"
	"sync"
	"time"
)

func test() {
	for i := 1; i <= 10; i++ {
		fmt.Println("test hello word" + strconv.Itoa(i))
		time.Sleep(time.Second)
	}
}
func FirstTest01() {
	//每隔一秒输出一个hello word,输出十次，使用goroutine
	//test() //调用
	go test()
	fmt.Println("")
	for i := 1; i <= 5; i++ {
		fmt.Println("main hello word" + strconv.Itoa(i))
		time.Sleep(time.Second)
	}
}

var wg sync.WaitGroup

func FirstTest02() {
	//交叉打印两个数组
	//1.定义两个数组
	var a = [5]int{1, 2, 3, 4, 5}
	var b = [5]int{6, 7, 8, 9, 10}

	//2.定义一个函数，实现两个数组的交叉打印
	wg.Add(1)
	go func() {
		for i := 0; i < len(a); i++ {
			fmt.Println("a=", a[i])
			time.Sleep(1 * time.Second)
		}
		wg.Done()
	}()
	go func() {
		for i := 0; i < len(b); i++ {
			fmt.Println("b=", b[i])
			time.Sleep(1 * time.Second)
		}
	}()

	wg.Wait()
	fmt.Println("主线程退出")
}

