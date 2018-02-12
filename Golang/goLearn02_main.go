// gotest project main.go
package main

import (
	"fmt"
	//	"strconv"
	//	"strings"
	"log"
	"os"
	"runtime"
	"time"

	//	"./packages/pack1"
)

// variable
var n int = 5

// 因式分解关键字的写法一般用于声明全局变量
// 当一个变量声明之后，系统自动赋予它该类型的零值。
// 记住，所有的内存在Go中都是经过初始化的。
var (
	a   int
	b   bool
	str string
)

// Go在编译时可以根据变量的值来自动推断其类型
var c = 13

// const
//const PI = 3.1415926
const PI float32 = 3.1415926

// func
func sum(a int, b int) int { return a + b }

// 局部变量，函数体内声明局部变量时，应使用简短声明语法 :=
func addOne(x int) int {
	local := 3
	return x + local
}

// pointer，如果是做系统编程、操作系统或者网络应用，指针是不可或缺的一部分。
var ptr *int

// func init(), 是每个包在完成初始化后自动执行，并且 执行优先级比main函数高。
func init() {
	fmt.Println("this is the init function.")
}

/*=========================================*/
// func main
func main() {
	fmt.Println("Hello World!")
	fmt.Println(sum(1, 4))
	fmt.Println(n)
	fmt.Println(PI)

	t := time.Now()
	fmt.Println(t)

	// 指针
	fmt.Println(ptr)
	ptr = &a
	fmt.Println(ptr)
	fmt.Printf("%d, %p, %p\n", a, &a, ptr)

	fmt.Println(runtime.GOOS)

	fileTest()

	bp := sum
	fmt.Println(bp(3, 13))
	fmt.Println(gBp(3, 13))

	fmt.Println(namedFunction(1, 7))

	var m int
	var n int
	m, n = namedFunction(1, 13)
	fmt.Println(m, n)

	passByReference(&m)
	fmt.Println(m)

	Greeting("hello", "dog", "cat", "dogs", "cats")
	//hello [dog cat dogs cats]
	GreetingWithInterface("i", "love", 1, 3)

	deferTest()

	logTest()
	logLoggerTest()

	callback(3, 5, sub)

	timeTest()

	closureTest()

	runtimeCallerTest()

	arrayTest()

	//pack1.helloWorld()

	structTest()

}

/*===================================================*/

// 文件读写
func fileTest() {
	f, err := os.OpenFile("notes.txt", os.O_RDWR|os.O_CREATE, 0755)
	if err != nil {
		fmt.Println("err")
	}

	n, err = f.Write([]byte("i love you"))
	fmt.Println(n, err)

	f.Close()
}

// 函数类型
type binOp func(int, int) int

var gBp binOp = sum

// 命名的参数
func namedFunction(a int, b int) (x int, y int) {
	//	x = a
	//	y = b
	//	return
	return a, b
}

// 传递指针给函数
func passByReference(x *int) {
	*x = 13
}

// 传递变长参数给函数, who ...string  --> 是一个数组
func Greeting(prefix string, who ...string) {
	//fmt.Println(prefix, who)
	fmt.Println(prefix)
	for pos, value := range who {
		fmt.Println(pos, value)
	}
}

// 空接口 interface{} 和 for-range循环
func GreetingWithInterface(values ...interface{}) {
	for pos, value := range values {
		fmt.Println(pos, value)
	}
}

// defer关键字，在进入和离开某个函数打印相关的消息
func trace(s string) {
	fmt.Println("entering:", s)
}

func untrace(s string) {
	fmt.Println("leaving:", s)
}

func deferTest() {
	trace("deferTest")
	defer untrace(("deferTest"))
	fmt.Println("processing...")
}

// log标准库
func logTest() {
	arr := []int{2, 3, 5}

	log.Print("print array ", arr, "\n")
	log.Println("print array", arr)
	log.Printf("print array with item [%d, %d]", arr[0], arr[1])

	//log.Fatalln("fatal error, exit.")
	//fmt.Println("after log.Fatalln")
}

// log.Logger 标准库
func logLoggerTest() {
	// logFile
	fileName := "info.log"
	logFile, err := os.Create(fileName)
	defer logFile.Close()
	if err != nil {
		log.Fatalln("open file error")
	}

	// log.Logger
	debugLog := log.New(logFile, "[Info]", log.Ldate|log.Ltime|log.Llongfile)
	debugLog.Println("A Info message here")
	debugLog.SetPrefix("[Debug]")
	debugLog.Println("A Debug Message here ")
}

// 回调函数：函数可以作为其他函数的参数进行传递，然后在其他函数内调用执行。
func sub(a int, b int) {
	fmt.Println(a, "-", b, "=", a-b)
}

func callback(a int, b int, f func(int, int)) {
	f(a, b)
}

// time.Now() 计算函数执行时间
func timeTest() {
	start := time.Now()
	fmt.Println("processing...")
	end := time.Now()
	delta := end.Sub(start)
	fmt.Printf("time used: %s\n", delta)
}

// 闭包(closure)，即匿名函数
func closureTest() {
	// ①赋值给变量
	f := func(a int, b int) int {
		return a * b
	}
	c := f(13, 9)
	fmt.Println(c)

	// ②直接调用执行
	func(s string) {
		a := []int{1, 2, 3, 4, 5}
		for pos, i := range a {
			fmt.Println(pos, i)
		}

		fmt.Println(s)
	}("i love you.")
}

// runtime.Caller()函数， 返回函数被调用的位置
func runtimeCallerTest() {
	_, file, line, _ := runtime.Caller(1)
	fmt.Println(file, line)
}

// 数组
func arrayTest() {
	//var arr [5]int
	arr := [5]int{}
	for i := 0; i < 5; i++ {
		arr[i] = i * 2
	}
	for i := 0; i < len(arr); i++ {
		fmt.Println(arr[i])
	}

	var arr2 [5]int
	arr2 = arr // 数组拷贝
	arr2[2] = 13
	for pos, val := range arr2 {
		fmt.Println(pos, val)
	}

	for pos, val := range arr {
		fmt.Println(pos, val)
	}

	// 多维数组
	const (
		WIDTH  = 1920
		HEIGHT = 1080
	)
	type pixel int
	var screen [WIDTH][HEIGHT]pixel
	for y := 0; y < HEIGHT; y++ {
		for x := 0; x < WIDTH; x++ {
			screen[x][y] = 0
		}
	}

	result := arraySum(&arr)
	fmt.Println("result =", result)
}

// 数组大小必须一致
func arraySum(arr *[5]int) (sum int) {
	for _, val := range arr {
		sum += val
	}
	return
}

/* 切片（slice）
 * 将数组传递给函数会消耗很多内存，有两种方法可避免：
 *   - 传递数组的指针
 *   - 使用数组的切片
 * 在go中，通常使用切片
 */

// struct
type STUDENT struct {
	name string
	age  int
}

func structTest() {
	st := new(STUDENT)
	st.name = "yvhqbat"
	st.age = 13
	fmt.Println(st.name, st.age)
}
