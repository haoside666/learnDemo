package main
import (
    "errors"
    "fmt"
)
// 定义除数为0的错误
var errDivisionByZero = errors.New("division by zero")
func div(dividend, divisor int) (int, error) {
    // 判断除数为0的情况并返回
    if divisor == 0 {
        return 0, errDivisionByZero
    }
    // 正常计算，返回空错误
    return dividend / divisor, nil
}

func test1(){
	fmt.Println(div(1, 0))
}
// 声明一个解析错误
type ParseError struct {
    Filename string // 文件名
    Line     int    // 行号
}
// 实现error接口，返回错误描述
func (e *ParseError) Error() string {
    return fmt.Sprintf("%s:%d", e.Filename, e.Line)
}
// 创建一些解析错误
func newParseError(filename string, line int) error {
    return &ParseError{filename, line}
}
func test2() {
    var e error
    // 创建一个错误实例，包含文件名和行号
    e = newParseError("main.go", 1)
    // 通过error接口查看错误描述
    fmt.Println(e.Error())
    
    fmt.Printf("%T\n",e)
    // 根据错误接口具体的类型，获取详细错误信息
    switch detail := e.(type) {
		case *ParseError: // 这是一个解析错误
		    fmt.Printf("Filename: %s Line: %d\n", detail.Filename, detail.Line)
		default: // 其他类型的错误
		    fmt.Println("other error")
    }
}
    
func main() {
    test2()
}
