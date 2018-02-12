package mypackage

import (
	"fmt"
)

// 接口(interface)
// 接口，定义了一组方法（方法集），但是这些方法不包含实现代码，接口里也不包含变量。
// 接口类型的变量 var ai InterfaceName，
//             本质上是一个指针，但指向接口值的指针是非法的，不仅一点用也没有，还会导致代码错误，方法指针表，是通过运行时反射能力构建的。

//interface
type Isharpe interface {
	Area() float32
}

//struct Square
type Square struct {
	side float32
}

func (recv *Square) Area() float32 {
	return recv.side * recv.side
}

//struct Rectangle
type Rectangle struct {
	width  float32
	height float32
}

func (recv *Rectangle) Area() float32 {
	return recv.width * recv.height
}

//test
func InterfaceTest() {
	sq := new(Square)
	sq.side = 5
	fmt.Printf("square side is %f, area is %f\n", sq.side, sq.Area())

	// 只要实现了接口，即可对接口变量进行赋值
	var isharpe Isharpe
	isharpe = sq
	fmt.Printf("use interface, area is %f\n", isharpe.Area())

	rect := new(Rectangle)
	rect.height = 3
	rect.width = 5

	//var isharpe1 Isharpe
	isharpe = rect
	fmt.Printf("rect width is %f, height is %f, area is %f\n", rect.width, rect.height, rect.Area())
	fmt.Printf("isharp1 area is %f\n", isharpe.Area())

	//类型断言
	if v, ok := isharpe.(*Rectangle); ok {
		fmt.Println("issharpe is Rectangle type.")
		fmt.Println(v)
	} else {
		fmt.Println("issharpe is not Rectangle type.")
	}

	// 错误用法：
	//	t := isharpe.(type)
	//	fmt.Println("type is %T", t)

	// 类型判断 type-switch
	switch t := isharpe.(type) {
	case *Rectangle:
		fmt.Printf("type is %T with value %v\n", t, t)
	case *Square:
		fmt.Printf("type is %T with value %v\n", t, t)
	default:
		fmt.Printf("unexpected type %T\n", t)
	}

	//测试一个值是否实现了某个接口
	//	if sv, ok := (*rect).(Isharpe); ok {
	//		fmt.Printf("rect implements Isharpe interface\n")
	//	}
}

// 接口嵌套接口，即一个接口可以包含一个或多个其他接口
type ReadWrite interface {
	Read()
	Write()
}

type Lock interface {
	Lock()
	Unlock()
}

type File interface {
	ReadWrite
	Lock
	Open()
	Close()
}

// 类型断言，即检测接口变量的动态类型
//if v, ok := varI.(T); ok { // checked type assertion
//Process(v)
//return
//}

// 空接口，空接口不包含任何方法，它对实现不做任何要求。可以给一个空接口类型的变量 var v interface{} 赋任何类型的值。
type Any interface{}

// 利用空接口，构建通用类型的数组
// Vector能放任何类型的变量，因为任何类型都实现了空接口
type Vector struct {
	a []Any "切片"
}

func VectorTest() {
	fmt.Println("Vector test ...")
	vec := new(Vector)
	vec.a = make([]Any, 50, 100)
	for i := 0; i < 10; i++ {
		vec.a[i] = i * i
	}
	fmt.Println(vec)
	fmt.Printf("vec.a size is %d, vec.a capacity is %d\n", len(vec.a), cap(vec.a))
}
