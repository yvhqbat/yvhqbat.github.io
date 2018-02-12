// mypackage project mypackage.go
package mypackage

type StructTest struct {
	Name string
	id   int
}

/* Go 语言中的继承是通过内嵌或组合来实现的，
 * 所以可以说，在 Go 语言中，相比
 * 较于继承，组合更受青睐。
 */
type Inner struct {
	InnerName string
	innerAge  int
}

/*标签（ tag） ：它是一个附属于字段的字符串，可以是文档或其他的重要标记*/
/*内嵌结构体，实现 继承机制；重载字段或方法机制：外层名字会覆盖内层名字。 */
type Outer struct {
	OuterName string
	OuterAge  int
	Inner     "匿名（ 或内嵌） 字段，即这些字段没有显式的名字，只有字段的类型是必须的，此时类型就是字段的名字。"
}
