package main

import (
	"fmt"
	"time"
)

// 1.timer基本使用,默认只触发一次
func TimerStudy() {
	timer1 := time.NewTimer(time.Second)
	var t1 time.Time
	defer timer1.Stop()
	go func() {
		for {
			select {
			case t1 = <-timer1.C:
				fmt.Println(t1)
				fmt.Println("One second has passed.")
				//重置定时器的间隔时间
				timer1.Reset(time.Second)
			}
		}
	}()
	time.Sleep(10 * time.Second)
}

// 2.验证timer只能响应1次
func TimerStudy02() {
	timer2 := time.NewTimer(time.Second)
	for {
		<-timer2.C
		fmt.Println("时间到")
	}

}

// 3.timer实现延时的功能
func TimerStudy03() {
	time.Sleep(time.Second)
	timer3 := time.NewTimer(2 * time.Second)
	<-timer3.C
	fmt.Println("2秒到")
	<-time.After(3 * time.Second)
	fmt.Println("3秒到")
}

// 4.停止定时器
func TimerStudy04() {
	timer4 := time.NewTimer(time.Microsecond)
	go func() {
		<-timer4.C
		fmt.Println("定时器执行了")
	}()
	for i := 0; i < 100; i++ {
		fmt.Printf(" ") //用来等待定时器执行，多试几次，两种情况都会出现
	}
	b := timer4.Stop()
	if b {
		fmt.Println("timer4已经关闭")
	}
}

// 5.重置定时器
func TimerStudy05() {
	timer5 := time.NewTimer(3 * time.Second)
	timer5.Reset(1 * time.Second)
	fmt.Println(time.Now())
	fmt.Println(<-timer5.C)
}

// 6.ticker基本使用,到时间就执行，无次数限制
func TickerStudy01() {
	ticker := time.NewTicker(time.Second)
	var t1 time.Time
	go func() {
		for {
			select {
			case t1 = <-ticker.C: //返回的是Time对象
				fmt.Println(t1)
				fmt.Println("One second has passed.")
			}
		}
	}()
	time.Sleep(10 * time.Second)
}
