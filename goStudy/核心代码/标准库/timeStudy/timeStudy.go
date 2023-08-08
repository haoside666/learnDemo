package timeStudy

import (
	"fmt"
	"time"
)

// TimeTest1 时间戳
func TimeTest1() {
	now := time.Now() //获取当前时间
	fmt.Printf("current time:%v\n", now)
	year := now.Year()     //年
	month := now.Month()   //月
	day := now.Day()       //日
	hour := now.Hour()     //小时
	minute := now.Minute() //分钟
	second := now.Second() //秒
	fmt.Printf("%d-%02d-%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second)
}

// TimeTest2 时间戳
func TimeTest2() {
	now := time.Now()            //获取当前时间
	timestamp1 := now.Unix()     //时间戳
	timestamp2 := now.UnixNano() //纳秒时间戳
	fmt.Printf("current timestamp1:%v\n", timestamp1)
	fmt.Printf("current timestamp2:%v\n", timestamp2)
}

// TimeTest3 时间间隔
// const (
//
//	Nanosecond  Duration = 1  					纳秒
//	Microsecond          = 1000 * Nanosecond		微秒
//	Millisecond          = 1000 * Microsecond		毫秒
//	Second               = 1000 * Millisecond
//	Minute               = 60 * Second			分钟
//	Hour                 = 60 * Minute			小时
//
// )
func TimeTest3() {
	time.Sleep(time.Nanosecond)
	fmt.Println("一纳秒到!")
	time.Sleep(time.Microsecond)
	fmt.Println("一微秒到!")
	time.Sleep(time.Millisecond)
	fmt.Println("一毫秒到!")
	time.Sleep(time.Second)
	fmt.Println("一秒到!")
}

// TimeTest4 时间操作
func TimeTest4() {
	now := time.Now()
	later := now.Add(time.Hour) // 当前时间加1小时后的时间
	fmt.Println(later)
	fmt.Println(later.Sub(now)) // 时间差
	fmt.Println(later.Before(now))
	fmt.Println(later.After(now))

}

// TimeTest5 ticker定时器，Timer只执行一次
func TimeTest5() {
	ticker := time.Tick(time.Second) //定义一个1秒间隔的定时器
	for i := range ticker {
		fmt.Println(i) //每秒都会执行的任务
	}
}

// TimeTest6
func TimeTest6() {
	now := time.Now()
	fmt.Println(now)
	// 加载时区
	loc, err := time.LoadLocation("Asia/Shanghai")
	if err != nil {
		fmt.Println(err)
		return
	}
	// 按照指定时区和指定格式解析字符串时间
	timeObj, err := time.ParseInLocation("2006/01/02 15:04:05", "2019/08/04 14:15:20", loc)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(timeObj)
	fmt.Println(timeObj.Sub(now))
}
