package main

import (
	"fmt"
	"strings"
	"unicode"
)

type strList []string

const az string = "abcdefghijklmnopqrstuvwxyz"
const AZ string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
const digit string = "0123456789"

func In(r rune, s string) bool {
	for _, c := range s {
		if r == c {
			return true
		}
	}
	return false
}

func TestFunc(f func(r rune) bool) {
	for i := 1; i < 128; i++ {
		if f(int32(i)) {
			fmt.Printf("%d ", i)
		}
	}
	fmt.Println()
}

func unicodeTest() {
	//判断是不是大小写字母
	TestFunc(unicode.IsLetter)
	//判断是不是小写字母
	TestFunc(unicode.IsLower)
	//判断是不是大写字母
	TestFunc(unicode.IsUpper)
	//判断是不是数字
	TestFunc(unicode.IsDigit)
	//判断是不是控制字符
	TestFunc(unicode.IsControl)
	//判断是不是定义的空格字符 如'\t', '\n', '\v', '\f', '\r', ' ', U+0085 (NEL), U+00A0 (NBSP)
	TestFunc(unicode.IsSpace)
}

func GeneralFunc(s string, condition func(r rune) bool, successDoThing func(r rune) string, failureDoThing func(r rune) string) string {
	s1 := ""
	for _, c := range s {
		if condition(c) {
			s1 += successDoThing(c)
		} else {
			s1 += failureDoThing(c)
		}
	}
	return s1
}

func example01() {
	s := "hello world!"
	s1 := GeneralFunc(s, func(r rune) bool {
		return In(r, "aeiou")
	}, func(r rune) string {
		a := string(r)
		return a + a
	}, func(r rune) string {
		return string(r)
	})
	fmt.Println(s1)
}

type myType = rune

func GeneralFunc2(s string, condition func(r rune) bool, successDoThing func(r rune) interface{}, failureDoThing func(r rune) interface{}, result *interface{}) {
	var sum myType
	for _, c := range s {
		if condition(c) {
			value := successDoThing(c).(myType)
			sum += value
		} else {
			value := failureDoThing(c).(myType)
			sum += value
		}
	}
	*result = sum
}

func example02() {
	s := "hello world!"
	var result interface{}
	GeneralFunc2(s, func(r rune) bool {
		return In(r, "aeiou")
	}, func(r rune) interface{} {
		temp := string(r)
		var t interface{} = temp + temp
		return t
	}, func(r rune) interface{} {
		temp := string(r)
		var t interface{} = temp
		return t
	}, &result)
	fmt.Println(result)
}

func stringToSet(s string) strList {
	ss := strings.Split(s, "")
	var m = map[string]int{}
	for _, v := range ss {
		m[v]++
	}
	set := strList{}
	for k := range m {
		set = append(set, k)
	}
	return set
}

func strListTostring(ss strList) string {
	s := ""
	for _, s1 := range ss {
		s += s1
	}
	return s
}

func example03() {
	s := "110%"

	length := len(s)
	s = strListTostring(stringToSet(s))
	var result interface{}
	GeneralFunc2(s, func(r rune) bool {
		return In(r, az+AZ+digit)
	}, func(r rune) interface{} {
		var t interface{} = r
		return t
	}, func(r rune) interface{} {
		var t interface{} = 0
		return t
	}, &result)

	fmt.Println(result.(myType) % myType(length))
	fmt.Println(length)
}

func main() {
	example03()

}
