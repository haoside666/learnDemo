package refilectStudy

import (
	"encoding/json"
	"fmt"
	"reflect"
)

type Enum int

const (
	Zero Enum = 0
)

// TypeOf获取类型对象，Name获取类型名称，Kind获取类型种类，Elem()获取这个指针指向的元素类型
func ReflectTest01() {
	var a int
	typeOfA := reflect.TypeOf(a)
	fmt.Println(typeOfA)
	fmt.Println(typeOfA.Name(), typeOfA.Kind())

	type cat struct{}
	typeOfA = reflect.TypeOf(cat{})
	fmt.Println(typeOfA)
	fmt.Println(typeOfA.Name(), typeOfA.Kind())

	typeOfA = reflect.TypeOf(Zero)
	fmt.Println(typeOfA)
	fmt.Println(typeOfA.Name(), typeOfA.Kind())

	ins := &cat{}
	typeOfA = reflect.TypeOf(ins)
	fmt.Println(typeOfA, typeOfA.Elem())
	fmt.Println(typeOfA.Name(), typeOfA.Kind())
	fmt.Println(typeOfA.Elem().Name(), typeOfA.Elem().Kind())
}

// NumField返回结构体成员字段数量,Field返回索引对应的结构体字段的信息
func ReflectTest02() {
	type cat struct {
		Name string
		Type int `json:"123" id:"100"`
	}
	ins := cat{Name: "mimi", Type: 1}
	typeOfCat := reflect.TypeOf(ins)

	// 遍历结构体所有成员
	for i := 0; i < typeOfCat.NumField(); i++ {
		// 获取每个成员的结构体字段类型
		fieldType := typeOfCat.Field(i)
		fmt.Printf("name: %v  tag: '%v'\n", fieldType.Name, fieldType.Tag)
	}

	// 通过字段名, 找到字段类型信息
	if catType, ok := typeOfCat.FieldByName("Type"); ok {
		// 从tag中取出需要的tag
		fmt.Println(catType.Tag.Get("json"), catType.Tag.Get("id"))
	}
}

func ReflectTest03() {
	var a int = 1024
	// 获取变量a的反射值对象
	valueOfA := reflect.ValueOf(&a)
	// 取出a地址的元素(a的值)
	valueOfA = valueOfA.Elem()
	// 修改a的值为1
	valueOfA.SetInt(1)
	// 打印a的值
	fmt.Println(valueOfA.Int())
}

type myInt int

type User struct {
	Id   int
	Name string
	Age  int
}

func (u *User) Hello(x interface{}) {
	v := reflect.ValueOf(x) //反射获取值
	fmt.Printf("类型名称:%v, 类型种类:%v, 类型值:%v", v, v.Type(), v.Kind())
	fmt.Println()
	//类型种类指的是值的类型，比如int，string，bool，struct，array，slice，map，chan，func，interface，ptr，unsafe.Pointer
}

func ReflectTest04() {
	u := &User{1, "OK", 12}
	u.Hello(u)

	u.Hello(123)
	u.Hello(myInt(122))
	u.Hello(12.123)

	var i = [3]int{1, 2, 3} // i是数组
	u.Hello(i)

	var y = []int{1, 2, 3} // y是切片
	u.Hello(y)

	var m = map[string]int{"a": 1, "b": 2} // m是map
	u.Hello(m)

}

func add(a, b int) int {
	return a + b
}

func ReflectTest05() {
	// 将函数包装为反射值对象
	funcValue := reflect.ValueOf(add)
	fmt.Println(funcValue)
	// 构造函数参数, 传入两个整型值
	paramList := []reflect.Value{reflect.ValueOf(10), reflect.ValueOf(20)}
	// 反射调用函数
	retList := funcValue.Call(paramList)
	// 获取第一个返回值, 取整数值
	fmt.Println(retList[0].Int())

}

func ReflectTest06() {
	type cat struct{}
	var v interface{} = cat{}
	t := reflect.TypeOf(v)
	fmt.Println("Type:", t, t.Name(), t.Kind(), t.String())
}

type Config struct {
	ID      string   `json:"id"`
	Genders []string `json:"性别"`
	Age     int      `json:"年龄"`
	Name    string   `json:"姓名"`
}

type ConfigList struct {
	Configs []Config `json:"configs"`
	Email   string   `json:"email"`
}

// 使用反射得到未知数据原来的类型
func ReflectTest07() {
	configList := ConfigList{
		Configs: []Config{
			{
				ID:      "1",
				Genders: []string{"asfd", "asfd"},
				Age:     20,
				Name:    "Tom",
			},
			{
				ID:      "2",
				Genders: []string{"asfd", "asfd", "asfd"},
				Age:     30,
				Name:    "Jack",
			},
		},
		Email: "nsddd.top",
	}
	//fmt.Println(configList)

	configListType := reflect.TypeOf(configList)
	fmt.Println(configListType)
	configListValue := reflect.ValueOf(configList)
	fmt.Println(configListValue)

	for i := 0; i < configListValue.NumField(); i++ {
		//获取每个成员的结构体字段类型
		fieldValue := configListValue.Field(i)
		fieldType := configListType.Field(i)
		switch fieldValue.Type().Kind().String() {
		case "string":
			fmt.Printf("\"%v\":\"%v\"}\n", fieldType.Tag.Get("json"), fieldValue)
		case "slice":
			fmt.Printf("{\"%v\":[", fieldType.Tag.Get("json"))
			length := fieldValue.Len()
			for j := 0; j < length; j++ {
				fieldValue2 := fieldValue.Index(j)
				switch fieldValue2.Type().Kind().String() {
				case "struct":
					if value, ok := fieldValue2.Interface().(Config); ok {
						fieldType2 := reflect.TypeOf(value)
						fmt.Printf("{")
						for k := 0; k < fieldValue2.NumField(); k++ {
							fieldType3 := fieldType2.Field(k)
							fieldValue3 := fieldValue2.Field(k)
							switch fieldValue3.Type().Kind().String() {
							case "string", "slice", "int":
								if k != fieldValue2.NumField()-1 {
									fmt.Printf("\"%v\":\"%v\",", fieldType3.Tag.Get("json"), fieldValue3)
								} else {
									fmt.Printf("\"%v\":\"%v\"", fieldType3.Tag.Get("json"), fieldValue3)
								}
							}
						}
						if j != length-1 {
							fmt.Printf("},")
						} else {
							fmt.Printf("}")
						}
					}
				}
			}
			fmt.Printf("],")
		}
	}
	//json
	jsonBody, err := json.Marshal(configList)
	if err != nil {
		fmt.Println("err=", err)
	}
	fmt.Println(string(jsonBody))
}

/*
type Type interface {
    // Kind返回该接口的具体分类
    Kind() Kind
    // Name返回该类型在自身包内的类型名，如果是未命名类型会返回""
    Name() string
    // PkgPath返回类型的包路径，即明确指定包的import路径，如"encoding/base64"
    // 如果类型为内建类型(string, error)或未命名类型(*T, struct{}, []int)，会返回""
    PkgPath() string
    // 返回类型的字符串表示。该字符串可能会使用短包名（如用base64代替"encoding/base64"）
    // 也不保证每个类型的字符串表示不同。如果要比较两个类型是否相等，请直接用Type类型比较。
    String() string
    // 返回要保存一个该类型的值需要多少字节；类似unsafe.Sizeof
    Size() uintptr
    // 返回当从内存中申请一个该类型值时，会对齐的字节数
    Align() int
    // 返回当该类型作为结构体的字段时，会对齐的字节数
    FieldAlign() int
    // 如果该类型实现了u代表的接口，会返回真
    Implements(u Type) bool
    // 如果该类型的值可以直接赋值给u代表的类型，返回真
    AssignableTo(u Type) bool
    // 如该类型的值可以转换为u代表的类型，返回真
    ConvertibleTo(u Type) bool
    // 返回该类型的字位数。如果该类型的Kind不是Int、Uint、Float或Complex，会panic
    Bits() int
    // 返回array类型的长度，如非数组类型将panic
    Len() int
    // 返回该类型的元素类型，如果该类型的Kind不是Array、Chan、Map、Ptr或Slice，会panic
    Elem() Type
    // 返回map类型的键的类型。如非映射类型将panic
    Key() Type
    // 返回一个channel类型的方向，如非通道类型将会panic
    ChanDir() ChanDir
    // 返回struct类型的字段数（匿名字段算作一个字段），如非结构体类型将panic
    NumField() int
    // 返回struct类型的第i个字段的类型，如非结构体或者i不在[0, NumField())内将会panic
    Field(i int) StructField
    // 返回索引序列指定的嵌套字段的类型，
    // 等价于用索引中每个值链式调用本方法，如非结构体将会panic
    FieldByIndex(index []int) StructField
    // 返回该类型名为name的字段（会查找匿名字段及其子字段），
    // 布尔值说明是否找到，如非结构体将panic
    FieldByName(name string) (StructField, bool)
    // 返回该类型第一个字段名满足函数match的字段，布尔值说明是否找到，如非结构体将会panic
    FieldByNameFunc(match func(string) bool) (StructField, bool)
    // 如果函数类型的最后一个输入参数是"..."形式的参数，IsVariadic返回真
    // 如果这样，t.In(t.NumIn() - 1)返回参数的隐式的实际类型（声明类型的切片）
    // 如非函数类型将panic
    IsVariadic() bool
    // 返回func类型的参数个数，如果不是函数，将会panic
    NumIn() int
    // 返回func类型的第i个参数的类型，如非函数或者i不在[0, NumIn())内将会panic
    In(i int) Type
    // 返回func类型的返回值个数，如果不是函数，将会panic
    NumOut() int
    // 返回func类型的第i个返回值的类型，如非函数或者i不在[0, NumOut())内将会panic
    Out(i int) Type
    // 返回该类型的方法集中方法的数目
    // 匿名字段的方法会被计算；主体类型的方法会屏蔽匿名字段的同名方法；
    // 匿名字段导致的歧义方法会滤除
    NumMethod() int
    // 返回该类型方法集中的第i个方法，i不在[0, NumMethod())范围内时，将导致panic
    // 对非接口类型T或*T，返回值的Type字段和Func字段描述方法的未绑定函数状态
    // 对接口类型，返回值的Type字段描述方法的签名，Func字段为nil
    Method(int) Method
    // 根据方法名返回该类型方法集中的方法，使用一个布尔值说明是否发现该方法
    // 对非接口类型T或*T，返回值的Type字段和Func字段描述方法的未绑定函数状态
    // 对接口类型，返回值的Type字段描述方法的签名，Func字段为nil
    MethodByName(string) (Method, bool)
    // 内含隐藏或非导出方法
}
*/

func ReflectTest08() {
	rVal := reflect.ValueOf("123") //获取变量值  实际传入的是未知类型数据，通过反射得到其类型，在用断言转回去

	//如何将reflect.Value转成空接口类型
	v := rVal.Interface().(string)
	fmt.Println(v)
}

// 专门演示反射，对结构体的反思
func reflectTest(b interface{}) {
	rType := reflect.TypeOf(b)
	fmt.Println("rType = ", rType)
	rVal := reflect.ValueOf(b)
	fmt.Println("rVal = ", rVal)

	iv := rVal.Interface()
	fmt.Printf("iv = %v iv type = %T", iv, iv)
	fmt.Println("")

	if stu, ok := iv.(Student); ok {
		fmt.Println("student.Name = ", stu.Name)
	}
	fmt.Println("student.Name = ", b.(Student).Name)
}

type Student struct {
	Name string
	Age  int
}

func ReflectTest09() {
	fmt.Println("分割线", "---------------------------------------")
	stu := Student{
		Name: "tom",
		Age:  20,
	}

	reflectTest(stu)
}

type Monster struct {
	Name  string  `json:"name"`
	Age   int     `json:"monster_age"`
	Score float32 `json:"成绩"`
	Sex   string
}

// 方法，返回两个数的和
func (s Monster) GetSum(n1, n2 int) int {
	return n1 + n2
}

// 方法，显示s的值
func (s Monster) Print() {
	fmt.Println("---start~----")
	fmt.Println(s)
	fmt.Println("---end~----")
}

// 方法， 接收四个值，给s赋值
func (s Monster) Set(name string, age int, score float32, sex string) {
	s.Name = name
	s.Age = age
	s.Score = score
	s.Sex = sex
}
func TestStruct(a interface{}) {
	//typ := reflect.TypeOf(a)
	val := reflect.ValueOf(a)

	//获取到a对应的类别
	kd := val.Kind()
	//如果传入的不是struct，就退出     --  判断是否是结构体
	if kd != reflect.Struct {
		fmt.Println("expect struct")
		return
	}

	//获取到该结构体有几个字段
	//num := val.NumField()
	//
	//fmt.Printf("struct has %d fields\n", num) //4
	////变量结构体的所有字段
	//for i := 0; i < num; i++ {
	//	fmt.Printf("Field %d: 值为=%v\n", i, val.Field(i))
	//	//获取到struct标签, 注意需要通过reflect.Type来获取tag标签的值
	//	tagVal := typ.Field(i).Tag.Get("json")
	//	fmt.Printf("Field %d: tag为=%v\n", i, tagVal)
	//}

	//获取到该结构体有多少个方法
	numOfMethod := val.NumMethod()
	fmt.Printf("字段struct has %d methods\n", numOfMethod)

	//var params []reflect.Value
	//方法的排序默认是按照 函数名的排序（ASCII码）·
	val.Method(1).Call(nil) //获取到第二个方法。调用它

	//调用结构体的第1个方法Method(0)
	var params []reflect.Value //声明了 []reflect.Value
	params = append(params, reflect.ValueOf(10))
	params = append(params, reflect.ValueOf(40))
	res := val.Method(0).Call(params) //传入的参数是 []reflect.Value, 返回[]reflect.Value
	fmt.Println("res=", res[0].Int()) //返回结果, 返回的结果是 []reflect.Value*/
}

func ReflectTest10() {
	var a Monster = Monster{
		Name:  "黄鼠狼精",
		Age:   400,
		Score: 30.8,
	}
	//将Monster实例传递给TestStruct函数
	TestStruct(a)
}
