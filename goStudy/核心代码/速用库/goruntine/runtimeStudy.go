package main

import (
	"fmt"
	"runtime"
	"time"
)

// runtime
// Gosched让出CPU时间片，重新等待安排任务
// Goexit退出当前协程
// GOMAXPROCS 用于设置可以并行计算的CPU核数最大值，并返回之前的值

func FirstCPU() {
	//获取cpu的数目
	cpuNum := runtime.NumCPU()
	fmt.Println("cpuNum = ", cpuNum)

	//可以设置最大的CPU数目
	runtime.GOMAXPROCS(cpuNum)
	fmt.Println("num = ", cpuNum)
}


func goschedTest1() {
	go func(s string) {
		for i := 0; i < 50; i++ {
			fmt.Println(s)
		}
	}("world")
	// 主协程
	for i := 0; i < 50; i++ {
		// Gosched让出时间片
		runtime.Gosched() //注释这一行查看前后效果
		fmt.Println("hello")
	}
}

func goexitTest2() {
	go func() {
		defer fmt.Println("A.defer")
		func() {
			defer fmt.Println("B.defer")

			// 结束协程
			runtime.Goexit() //这里直接退出了，后续没有执行

			defer fmt.Println("C.defer")
			fmt.Println("B")
		}()
		fmt.Println("A")
	}()
	time.Sleep(time.Second)
}

func a() {
	begin := time.Now()
	for i := 1; i < 100; i++ {
		time.Sleep(time.Microsecond)
	}
	fmt.Println(time.Now().Sub(begin))
}

func b() {
	begin := time.Now()
	for i := 1; i < 100; i++ {
		time.Sleep(time.Microsecond)
	}
	fmt.Println(time.Now().Sub(begin))
}

func gomaxprocsTest3() {
	//默认为机器上的CPU核心数
	fmt.Println(runtime.GOMAXPROCS(8)) //设置为1,CPU核数最大值为1，==>并行 大于1==>并发
	go a()
	go b()
	time.Sleep(time.Second)
}

func main() {
	gomaxprocsTest3()
}
