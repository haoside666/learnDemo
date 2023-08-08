package syncStudy

import (
	"fmt"
	"strconv"
	"sync"
	"time"
)

// 控制并发任务的同步
// sync.WaitGroup
//
//	(wg * WaitGroup) Add(delta int)	计数器+delta
//	(wg *WaitGroup) Done()	计数器-1
//	(wg *WaitGroup) Wait()	阻塞直到计数器变为0
//
// sync.Once 保证某种行为只会被执行一次。 常应用于单例模式，例如初始化配置、保持数据库连接等
// func (o *Once) Do(f func())
// sync.Map
var wg sync.WaitGroup

func hello() {
	defer wg.Done()
	fmt.Println("Hello Goroutine!")
}
func WaitGroupTest() {
	wg.Add(1)
	go hello() // 启动另外一个goroutine去执行hello函数
	fmt.Println("main goroutine done!")
	wg.Wait()
}

var (
	config map[string]string
	once   sync.Once
)

func loadConfig() {
	// 模拟从配置文件中加载配置信息
	fmt.Println("load config...")
	time.Sleep(time.Second)
	config = make(map[string]string)
	config["host"] = "127.0.0.1"
	config["port"] = "8080"
}
func getConfig() map[string]string {
	once.Do(loadConfig)
	return config
}
func SyncOnceTest() {
	// 第一次调用GetConfig会执行loadConfig函数，初始化config变量
	fmt.Println(getConfig())
	// 第二次调用GetConfig不会执行loadConfig函数，直接返回已初始化的config变量
	fmt.Println(getConfig())
}

var m = make(map[string]int)

func get(key string) int {
	return m[key]
}

func set(key string, value int) {
	m[key] = value
}

// Map不是并发安全的
func SyncMapTest() {
	wg := sync.WaitGroup{}
	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func(n int) {
			key := strconv.Itoa(n)
			set(key, n)
			fmt.Printf("k=:%v,v:=%v\n", key, get(key))
			wg.Done()
		}(i)
	}
	wg.Wait()
}

var m2 = sync.Map{}

func SyncMapTest2() {
	wg := sync.WaitGroup{}
	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func(n int) {
			key := strconv.Itoa(n)
			m2.Store(key, n)
			value, _ := m2.Load(key)
			fmt.Printf("k=:%v,v:=%v\n", key, value)
			wg.Done()
		}(i)
	}
	wg.Wait()
}
