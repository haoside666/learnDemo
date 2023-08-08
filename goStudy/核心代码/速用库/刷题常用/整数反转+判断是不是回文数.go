package main

import (
	"fmt"
	"strconv"
)
func reverseInteger(num int) int {
	reversed := 0
	for num != 0 {
		digit := num % 10
		reversed = reversed*10 + digit
		num /= 10
	}
	return reversed
}
func isPalindrome(num int) bool {
	str := strconv.Itoa(num) 
	length := len(str)
	for i := 0; i < length/2; i++ {
		if str[i] != str[length-1-i] {
			return false
		}
	}
	return true
}
func main() {
    var x int
    fmt.Scan(&x)
	for !isPalindrome(x){
		x=reverseInteger(x)+x
	}
    fmt.Println(x)
}