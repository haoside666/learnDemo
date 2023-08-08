/*
go.mod 提供了 module、require、replace 和 exclude 四个命令：
    module 语句指定包的名字（路径）；
    require 语句指定的依赖项模块；
    replace 语句可以替换依赖项模块；
    exclude 语句可以忽略依赖项模块。
*/
package main

import (
	. "fmt"
	"go-mod/hello"
	"go-mod/models"
)

func main() {
	Println("main主函数")
	hello.Hello()
	Println(models.Name)
	//hello.Hello()
}
