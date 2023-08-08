package main

import (
	"fmt"
	"math"
)

func Max(nums ...int) int {
	var maxNum int = math.MinInt
	for _, num := range nums {
		if num > maxNum {
			maxNum = num
		}
	}
	return maxNum
}

func Min(nums ...int) int {
	var minNum int = math.MaxInt
	for _, num := range nums {
		if num < minNum {
			minNum = num
		}
	}
	return minNum
}

func compare(x int, y int, z int) int {
	// write code here
	return Max(x, y, z) - Min(x, y, z)

}

func test() {
	fmt.Println(compare(1, 2, 3))
}

func main() {
	test()
}