package goroutineStudy

import (
	"fmt"
	"time"
)

func CTest01() {
	//创建一个管道
	ch := make(chan int, 10) //管道的容量是10

	//给管l道中写入数据
	ch <- 10
	ch <- 20
	ch <- 30
	ch <- 40

	fmt.Println("len(ch) = ", len(ch))
	fmt.Println("cap(ch) = ", cap(ch))
	fmt.Println("ch = ", ch)

	//从管道中读取数据
	num := <-ch
	fmt.Println("num = ", num)   //10
	fmt.Println("再读取一个数据", <-ch) //20
	fmt.Println("再读取一个数据", <-ch) //30
	fmt.Println("再读取一个数据", <-ch) //40
	close(ch)
}

func CTest02() {
	ch := make(chan int, 10) //管道的容量是10

	//继续批量存储数据
	ch <- 50
	ch <- 150
	ch <- 250
	fmt.Println("len(ch) = ", len(ch))
	fmt.Println("cap(ch) = ", cap(ch))
	fmt.Println("ch = ", ch)

	////遍历管道,需要使用 close(ch) 关闭管道
	//close(ch)
	//for v := range ch {
	//	fmt.Println("v = ", v)
	//}

	////遍历管道,需要使用 close(ch) 关闭管道
	//close(ch)
	//for {
	//	val, ok := <-ch
	//	if !ok {
	//		fmt.Println("读取完毕")
	//		break
	//	} else {
	//		fmt.Println("var = ", val) //不断读取管道中的数据
	//	}
	//}

	//遍历管道,
	//注意要先保存len(ch),因为ch读取后长度会减少
	length := len(ch)
	for i := 0; i < length; i++ {
		val, ok := <-ch
		if !ok {
			fmt.Println("读取完毕")
			break
		} else {
			fmt.Println("var = ", val) //不断读取管道中的数据
		}
	}

}

func CTest03() {
	ch1 := make(chan string, 3)
	ch1 <- "a" //写入管道
	a := <-ch1 //读取管道
	fmt.Println("读取管道", a)

	ch2 := make(chan<- string, 3) //管道只能写入
	ch2 <- "b"                    //写入管道
	//b := <-ch2                 //读取管道
	//fmt.Println("读取管道", b) //读取管道

	ch3 := make(<-chan string, 3) //管道只能读取
	// ch3 <- "c" //写入管道
	c := <-ch3             //读取管道
	fmt.Println("读取管道", c) //读取管道
}

// 只读管道
func readChan(ch <-chan int) {
	for {
		num := <-ch
		if num == 0 {
			break
		}
		fmt.Println(num)
		time.Sleep(1000 * time.Millisecond)
	}
	wg.Done()
}

// 只写管道
func writeChan(ch chan<- int) {
	for i := 1; i <= 5; i++ {
		ch <- i
		time.Sleep(time.Millisecond * 1000) // 100毫秒就是0.1秒
	}
	close(ch)
	wg.Done()
}

func CTest04() {
	var ch = make(chan int, 1000)
	wg.Add(1)
	go writeChan(ch) // 只写
	wg.Add(1)
	go readChan(ch) // 只读
	wg.Wait()
}

func SelectTest() {
	ch1 := make(chan int, 10)
	ch2 := make(chan int, 10)

	//循环输入管道
	for i := 0; i < 10; i++ {
		ch1 <- i
		ch2 <- i
	}

OuterLoop:
	for {
		select {
		case val1 := <-ch1:
			fmt.Println("Received from ch1:", val1)
		case val2 := <-ch2:
			fmt.Println("Received from ch2:", val2)
		default:
			//
			fmt.Println("No value received, waiting for next timeout")
			break OuterLoop
		}
	}

}
