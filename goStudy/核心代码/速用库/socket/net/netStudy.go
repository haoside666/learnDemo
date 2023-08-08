package netStudy

import (
	"fmt"
	"net"
	"os"
)

// 根据域名查找IP地址
func NetTest() {
	addr, err := net.ResolveIPAddr("ip", "www.baidu.com")
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(addr.IP)
}

// net.ParseIP() 检查IP地址格式是否有效
func TestIP(s string) bool {
	ip := net.ParseIP(s)
	if ip == nil {
		return false
	} else {
		return true
	}

}
