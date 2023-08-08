package main

import (
	"fmt"
)

func mapFunc(numbers []int, function func(int) int) []int {
	result := make([]int, len(numbers))

	for i, num := range numbers {
		result[i] = function(num)
	}

	return result
}

func main() {
	arr := []int{1, 2, 3, 4, 5}
	fmt.Println(mapFunc(arr, func(i int) int {
		return 2 * i
	}))
}