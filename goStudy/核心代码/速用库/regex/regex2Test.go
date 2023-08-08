package main

import (
	"fmt"
	"github.com/dlclark/regexp2"
)
/*
参考文档:https://pkg.go.dev/github.com/dlclark/regexp2@v1.10.0#pkg-overview

RegexOptions
const (
	None                    RegexOptions = 0x0
	IgnoreCase                           = 0x0001 // "i"
	Multiline                            = 0x0002 // "m"
	ExplicitCapture                      = 0x0004 // "n"
	Compiled                             = 0x0008 // "c"
	Singleline                           = 0x0010 // "s"
	IgnorePatternWhitespace              = 0x0020 // "x"
	RightToLeft                          = 0x0040 // "r"
	Debug                                = 0x0080 // "d"
	ECMAScript                           = 0x0100 // "e"
	RE2                                  = 0x0200 // RE2 (regexp package) compatibility mode
	Unicode                              = 0x0400 // "u"
)
*/

/*
 type Regexp
	Compile 解析正则表达式，如果成功，则返回可用于匹配文本的 Regexp 对象。
    func Compile(expr string, opt RegexOptions) (*Regexp, error)
	
	MustCompile 与 Compile 类似，但如果无法解析表达式，则会出现恐慌。它简化了保存已编译正则表达式的全局变量的安全初始化。
    func MustCompile(str string, opt RegexOptions) *Regexp

    func (re *Regexp) Debug() bool
    func (re *Regexp) FindNextMatch(m *Match) (*Match, error)

	FindRunesMatch 在输入符文切片中搜索正则表达式匹配项
    func (re *Regexp) FindRunesMatch(r []rune) (*Match, error)
    func (re *Regexp) FindRunesMatchStartingAt(r []rune, startAt int) (*Match, error)

	FindStringMatch 在输入字符串中搜索 Regexp 匹配项
    func (re *Regexp) FindStringMatch(s string) (*Match, error)

	FindStringMatchStartingAt 在输入字符串中搜索从 startAt 索引开始的 Regexp 匹配项
    func (re *Regexp) FindStringMatchStartingAt(s string, startAt int) (*Match, error)

	GetGroupNames 返回用于命名表达式中的捕获组的字符串集。
    func (re *Regexp) GetGroupNames() []string
    func (re *Regexp) GetGroupNumbers() []int
    func (re *Regexp) GroupNameFromNumber(i int) string
    func (re *Regexp) GroupNumberFromName(name string) int

	如果符文匹配,MatchRunes 返回 true,如果发生超时,将设置正则表达式错误
    func (re *Regexp) MatchRunes(r []rune) (bool, error)

	如果字符串与正则表达式匹配，则 MatchString 返回 true,如果发生超时,将设置错误
    func (re *Regexp) MatchString(s string) (bool, error)

	Replace 搜索输入字符串并用替换文本替换找到的每个匹配项。Count 将限制尝试匹配的数量，而 startAt 将允许我们在输入开始时跳过可能的匹配（向左或向右取决于 RightToLeft 选项）。将 startAt 和 count 设置为 -1 以遍历整个字符串
    func (re *Regexp) Replace(input, replacement string, startAt, count int) (string, error)

	ReplaceFunc 搜索输入字符串，并使用求值器中的字符串替换找到的每个匹配项。 Count 将限制尝试匹配的数量，而 startAt 将允许我们在输入开头跳过可能的匹配项（向左或向右取决于 RightToLeft 选项）。将 startAt 和 count 设置为 -1 以遍历整个字符串。
    func (re *Regexp) ReplaceFunc(input string, evaluator MatchEvaluator, startAt, count int) (string, error)
    func (re *Regexp) RightToLeft() bool
    func (re *Regexp) String() string

*/

func validatePassword(password string) (bool, error) {
	// 定义正则表达式
	regex := regexp2.MustCompile(`^(?=(?:[^A-Z]*[A-Z]))(?=\D*\d)[^\s]{8,15}$`, 0)

	// 使用正则表达式进行匹配
	return regex.MatchString(password)
}

func temp() {
	passwords := []string{
		"abc12345",    // 不符合要求，缺少大写字母
		"Abcdefg1",    // 符合要求
		"passWORD123", // 符合要求
		"pass123",     // 不符合要求，长度不够
	}

	for _, password := range passwords {
		valid, _ := validatePassword(password)
		fmt.Printf("%s: %t\n", password, valid)
	}
}

func temp() {
	bufioTest1()
}