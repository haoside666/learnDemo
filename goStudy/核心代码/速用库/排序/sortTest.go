package main

import (
	"fmt"
	"sort"
	"strings"
)


func reverseSlice[T bool | int | int8 | int16 | int32 | int64 | uint8 | uint16 | uint32 | uint64 | uintptr | float32 | float64 | complex64 | complex128 | string](slices []T) []T {
	length := len(slices)
	reverseAfterSlice := slices
	for i := 0; i < length/2; i++ {
		reverseAfterSlice[i], reverseAfterSlice[length-1-i] = reverseAfterSlice[length-1-i], reverseAfterSlice[i]
	}
	return reverseAfterSlice
}

func sortfunc() {
	s := "ilILililiIIILLLLi"
	l := strings.Split(s, "")
	sort.Slice(l, func(i, j int) bool {
		m := map[string]int{"i": 1, "I": 2, "l": 3, "L": 4}
		return m[l[i]] < m[l[j]]
	})
	if len(s)%2 == 0 {
		fmt.Println(strings.Join(l, ""))
	} else {
		fmt.Println(strings.Join(reverseSlice(l), ""))
	}

}

func main() {
	sortfunc()
}
