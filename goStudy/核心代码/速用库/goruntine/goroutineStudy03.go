package main

import (
	"fmt"
	"runtime"
	"sync"
	"sync/atomic"
	"time"
)

func running() {
	var times int
	// 构建一个无限循环
	for {
		times++
		fmt.Println("tick", times)
		time.Sleep(time.Second)
	}

}

func test1() {
	go running()

	var input string
	fmt.Scanln(&input)
}

var counter int = 0

func Count(lock *sync.Mutex) {
	lock.Lock()
	counter++
	fmt.Println(counter)
	lock.Unlock()
}

func test2() {
	lock := &sync.Mutex{}
	for i := 0; i < 10; i++ {
		go Count(lock)
	}
	for {
		lock.Lock()
		c := counter
		lock.Unlock()
		runtime.Gosched()
		if c >= 10 {
			break
		}
	}
}

var (
	count int64
	wg    sync.WaitGroup
)

func incCount() {
	defer wg.Done()
	for i := 0; i < 10; i++ {
		value := count
		runtime.Gosched()
		value++
		count = value
	}
}

func incCounter(id int) {
	defer wg.Done()
	for i := 0; i < 10; i++ {
		atomic.AddInt64(&count, 1) //安全的对counter加1
		runtime.Gosched()
	}
}

func test3() {
	wg.Add(2)
	go incCount()
	go incCount()
	wg.Wait()
	fmt.Println(count)
}

var (
	shutdown int64
)

func doWork(name string) {
	defer wg.Done()
	for {
		fmt.Printf("Doing %s Work\n", name)
		time.Sleep(250 * time.Millisecond)
		if atomic.LoadInt64(&shutdown) == 1 {
			fmt.Printf("Shutting %s Down\n", name)
			break
		}
	}
}

func test4() {
	wg.Add(2)
	go doWork("A")
	go doWork("B")
	time.Sleep(1 * time.Second)
	fmt.Println("Shutdown Now")
	atomic.StoreInt64(&shutdown, 1)
	wg.Wait()
}

func main() {
	
}
