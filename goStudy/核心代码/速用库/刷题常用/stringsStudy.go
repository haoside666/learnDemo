package main

import (
	"fmt"
)

func reverseSlice[T bool | int | int8 | int16 | int32 | int64 | uint8 | uint16 | uint32 | uint64 | uintptr | float32 | float64 | complex64 | complex128 | string](slices []T) []T {
	length := len(slices)
	reverseAfterSlice := slices
	for i := 0; i < length/2; i++ {
		reverseAfterSlice[i], reverseAfterSlice[length-1-i] = reverseAfterSlice[length-1-i], reverseAfterSlice[i]
	}
	return reverseAfterSlice
}


func reverseString(s string) string {
	ss:=""
	for i := len(str) - 1; i >= 0; i-- {
		ss
	}
	return reversedStr.String()
}

func test() {
	fmt.Println(strings.Contains("aaababcd", "abc"))
	fmt.Println(strings.Count("aabbcc", "a"))
	fmt.Println(len(strings.Fields("ab  bd  cd")))
	fmt.Println(strings.Fields("ab  bd  cd"))
	fmt.Println(len(strings.Split("ab  bd  cd", " ")))
	fmt.Println(strings.Split("ab  bd  cd", " "))
	fmt.Println(strings.ToLower("After"))
	fmt.Println(strings.ToUpper("After"))
	//Trim函数把s字符串开头或者结尾里面包含字符集的字符全部过滤掉
	fmt.Println(strings.Trim(" abc def   ", " ")) //==strip()
	//
	s := []string{"foo", "bar", "baz"}
	fmt.Println(strings.Join(s, ","))

	fmt.Println(strings.Map(func(r rune) rune {
		switch {
		case r >= 'A' && r <= 'Z':
			return r - 'A' + 'a'
		case r >= 'a' && r <= 'z':
			return r - 'a' + 'A'
		}
		return r
	}, "Twas brillig And THE slithy gopher..."))
	fmt.Println(strings.Replace("oink oink oink", "k", "ky", -1))
}


func main() {
	test()
}