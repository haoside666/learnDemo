package main

import (
	"fmt"
)

type any interface{}
func filter[T bool | int | int8 | int16 | int32 | int64 | uint | uint8 | uint16 | uint32 | uint64 | uintptr | float32 | float64 | complex64 | complex128 | string | any](numbers []T, condition func(T) bool) []T {
	filtered := []T{}

	for _, num := range numbers {
		if condition(num) {
			filtered = append(filtered, num)
		}
	}

	return filtered
}

func test1() {
	numbers := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

	// 过滤函数，用于判断一个整数是否为偶数
	isEven := func(n int) bool {
		return n%2 == 0
	}

	// 过滤整数切片中的偶数
	filteredNumbers := filter(numbers, isEven)

	// 打印过滤后的结果
	fmt.Println(filteredNumbers)
}

func main() {
	test1()

}