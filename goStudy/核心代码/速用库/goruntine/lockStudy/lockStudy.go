package lockStudy

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

var x int64
var wg sync.WaitGroup

// 互斥锁
var lock sync.Mutex

// 不加锁，由于发生竞态导致最后结果不为140000
func add() {
	for i := 0; i < 70000; i++ {
		lock.Lock()
		x = x + 1
		lock.Unlock()
	}
	wg.Done()
}
func LockTest01() {
	wg.Add(2)
	go add()
	go add()
	wg.Wait()
	fmt.Println(x)
}

// 读写锁
var rwlock sync.RWMutex

func write() {
	rwlock.Lock() // 加写锁
	lock.Lock()
	x = x + 1
	lock.Unlock()
	rwlock.Unlock() // 解写锁
	wg.Done()

}

func read() {
	rwlock.RLock() // 加读锁
	lock.Lock()
	fmt.Println(x)
	lock.Unlock()
	rwlock.RUnlock() // 解读锁
	wg.Done()
}

func LockTest02() {
	runtime.GOMAXPROCS(1)
	start := time.Now()
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go write()
	}

	for i := 0; i < 300; i++ {
		wg.Add(1)
		go read()
	}

	wg.Wait()
	end := time.Now()
	fmt.Println(end.Sub(start))
}
