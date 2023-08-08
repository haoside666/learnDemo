package main  
  
import "fmt"  
  
type A struct {  
    Name string  
}  
  
type B struct {  
    Value int  
}  
  
type C struct {  
    *A  
    *B  
}  
  
func main() {  
    // 创建A和B的实例  
    a := &A{Name: "John"}  
    b := &B{Value: 42}  
  
    // 创建C的实例，并将A和B的指针分配给相应的字段  
    c := &C{A: a, B: b}  
  
    // 通过C的字段访问A和B的结构体字段  
    fmt.Println(c.Name)         // 输出：John  
    fmt.Println(c.Value)        // 输出：42  
}