```
https://www.lddgo.net/string/golangregex
```

Index

    func QuoteMeta(s string) string
    func Match(pattern string, b []byte) (matched bool, err error)
    func MatchString(pattern string, s string) (matched bool, err error)
    func MatchReader(pattern string, r io.RuneReader) (matched bool, err error)
    type Regexp
    func Compile(expr string) (*Regexp, error)
    func CompilePOSIX(expr string) (*Regexp, error)
    func MustCompile(str string) *Regexp
    func MustCompilePOSIX(str string) *Regexp
    func (re *Regexp) String() string
    func (re *Regexp) LiteralPrefix() (prefix string, complete bool)
    func (re *Regexp) Longest()
    func (re *Regexp) NumSubexp() int
    func (re *Regexp) SubexpNames() []string
    func (re *Regexp) Match(b []byte) bool
    func (re *Regexp) MatchString(s string) bool
    func (re *Regexp) MatchReader(r io.RuneReader) bool
    func (re *Regexp) Find(b []byte) []byte
    func (re *Regexp) FindString(s string) string
    func (re *Regexp) FindIndex(b []byte) (loc []int)
    func (re *Regexp) FindStringIndex(s string) (loc []int)
    func (re *Regexp) FindReaderIndex(r io.RuneReader) (loc []int)
    func (re *Regexp) FindSubmatch(b []byte) [][]byte
    func (re *Regexp) FindStringSubmatch(s string) []string
    func (re *Regexp) FindSubmatchIndex(b []byte) []int
    func (re *Regexp) FindStringSubmatchIndex(s string) []int
    func (re *Regexp) FindReaderSubmatchIndex(r io.RuneReader) []int
    func (re *Regexp) FindAll(b []byte, n int) [][]byte
    func (re *Regexp) FindAllString(s string, n int) []string
    func (re *Regexp) FindAllIndex(b []byte, n int) [][]int
    func (re *Regexp) FindAllStringIndex(s string, n int) [][]int
    func (re *Regexp) FindAllSubmatch(b []byte, n int) [][][]byte
    func (re *Regexp) FindAllStringSubmatch(s string, n int) [][]string
    func (re *Regexp) FindAllSubmatchIndex(b []byte, n int) [][]int
    func (re *Regexp) FindAllStringSubmatchIndex(s string, n int) [][]int
    func (re *Regexp) Split(s string, n int) []string
    func (re *Regexp) Expand(dst []byte, template []byte, src []byte, match []int) []byte
    func (re *Regexp) ExpandString(dst []byte, template string, src string, match []int) []byte
    func (re *Regexp) ReplaceAllLiteral(src, repl []byte) []byte
    func (re *Regexp) ReplaceAllLiteralString(src, repl string) string
    func (re *Regexp) ReplaceAll(src, repl []byte) []byte
    func (re *Regexp) ReplaceAllString(src, repl string) string
    func (re *Regexp) ReplaceAllFunc(src []byte, repl func([]byte) []byte) []byte
    func (re *Regexp) ReplaceAllStringFunc(src string, repl func(string) string) string

重点

    Regexp.MatchString
    Regexp.FindAllString
    Regexp.FindAllStringSubmatch
    Regexp.FindAllStringSubmatchIndex
    Regexp.FindString
    Regexp.FindStringIndex
    Regexp.FindStringSubmatch
    Regexp.ReplaceAllLiteralString
    Regexp.ReplaceAllString
    Regexp.SubexpNames



```
1.func Match(pattern string, b []byte) (matched bool, err error)
Match检查b中是否存在匹配pattern的子序列。更复杂的用法请使用Compile函数和Regexp对象。

2.func MatchString(pattern string, s string) (matched bool, err error)
MatchString类似Match，但匹配对象是字符串。

例子
matched, err := regexp.MatchString("foo.*", "seafood")
fmt.Println(matched, err)
matched, err = regexp.MatchString("bar.*", "seafood")
fmt.Println(matched, err)
matched, err = regexp.MatchString("a(b", "seafood")
fmt.Println(matched, err)

Output:

true <nil>
false <nil>
false error parsing regexp: missing closing ): `a(b`

3.func Compile(expr string) (*Regexp, error)

Compile解析并返回一个正则表达式。如果成功返回，该Regexp就可用于匹配文本。

在匹配文本时，该正则表达式会尽可能早的开始匹配，并且在匹配过程中选择回溯搜索到的第一个匹配结果。这种模式被称为“leftmost-first”，Perl、Python和其他实现都采用了这种模式，但本包的实现没有回溯的损耗。对POSIX的“leftmost-longest”模式，参见CompilePOSIX。

4.func MustCompile(str string) *Regexp
MustCompile类似Compile但会在解析失败时panic，主要用于全局正则表达式变量的安全初始化。

5.func (re *Regexp) String() string
String返回用于编译成正则表达式的字符串。

6.func (re *Regexp) MatchString(s string) bool
MatchString类似Match，但匹配对象是字符串。


7.func (*Regexp) FindStringIndex
func (re *Regexp) FindStringIndex(s string) (loc []int)
Find返回保管正则表达式re在b中的最左侧的一个匹配结果的起止位置的切片（显然len(loc)==2）。匹配结果可以通过起止位置对b做切片操作得到：b[loc[0]:loc[1]]。如果没有匹配到，会返回nil。

Example
re := regexp.MustCompile("ab?")
fmt.Println(re.FindStringIndex("tablett"))
fmt.Println(re.FindStringIndex("foo") == nil)

Output:
[1 3]
true

8.func (re *Regexp) FindStringSubmatch(s string) []string
Find返回一个保管正则表达式re在b中的最左侧的一个匹配结果以及（可能有的）分组匹配的结果的[]string切片。如果没有匹配到，会返回nil。

Example
re := regexp.MustCompile("a(x*)b(y|z)c")
fmt.Printf("%q\n", re.FindStringSubmatch("-axxxbyc-"))
fmt.Printf("%q\n", re.FindStringSubmatch("-abzc-"))

Output:
["axxxbyc" "xxx" "y"]
["abzc" "" "z"]

9.func (re *Regexp) FindAllString(s string, n int) []string

Find返回保管正则表达式re在b中的所有不重叠的匹配结果的[]string切片。如果没有匹配到，会返回nil。

Example
re := regexp.MustCompile("a.")
fmt.Println(re.FindAllString("paranormal", -1))
fmt.Println(re.FindAllString("paranormal", 2))
fmt.Println(re.FindAllString("graal", -1))
fmt.Println(re.FindAllString("none", -1))

Output:
[ar an al]
[ar an]
[aa]
[]

10.func (re *Regexp) Split(s string, n int) []string
Split将re在s中匹配到的结果作为分隔符将s分割成多个字符串，并返回这些正则匹配结果之间的字符串的切片。
返回的切片不会包含正则匹配的结果，只包含匹配结果之间的片段。当正则表达式re中不含正则元字符时，本方法等价于strings.SplitN。

举例：
s := regexp.MustCompile("a*").Split("abaabaccadaaae", 5)
// s: ["", "b", "b", "c", "cadaaae"]

11.
func (re *Regexp) ReplaceAllString(src, repl string) string
ReplaceAllString(src, repl, pattern string) string：将字符串 src 中所有匹配正则表达式模式 pattern 的部分替换为 repl，并返回替换后的新字符串。

Example
re := regexp.MustCompile("a(x*)b")
fmt.Println(re.ReplaceAllString("-ab-axxb-", "T"))


Output:
-T-T-
```

