package mypackage

import (
	"fmt"
	"strconv"
)

/*===================================*/
//结构体
type TwoInts struct {
	a int
	b int
}

//结构体类型的方法
func (recv *TwoInts) Add() int {
	return recv.a + recv.b
}

func (recv *TwoInts) AddNum(x int) int {
	return recv.Add() + x
}

//类型的String方法，如果类型定义了String()方法，fmt.Printf()/fmt.Print()/fmt.Println()会自动使用String()方法。
func (recv *TwoInts) String() string {
	return "(" + strconv.Itoa(recv.a) + "/" + strconv.Itoa(recv.b) + ")"
}

//test
func MethodTest() {
	fmt.Println("MethodTest...")
	ti := new(TwoInts)
	ti.a = 3
	ti.b = 7
	fmt.Println(ti) //"会调用类型的String方法"
	fmt.Println(ti.Add())
	fmt.Println(ti.AddNum(5))

}

/*===================================*/
// 非结构体类型上的方法
type VectorInt []int //数组切片

//方法， 数组切片传递，不需要使用指针
func (recv VectorInt) Add() int {
	var result int
	for _, element := range recv {
		result += element
	}
	return result
}

//test2
func MethodTest2() {
	fmt.Println("MethodTest2...")
	vec := VectorInt{1, 2, 3, 4, 5}
	fmt.Println("vec sum is", vec.Add())
}

/*===================================*/
// 接口 interface
type Engine interface {
	Start()
	Stop()
}

type Car struct {
	Engine
}

func (recv *Car) GoToWorkIn() {
	fmt.Println("start car...")
	//recv.Start()
	//recv.Stop()
}

func MethodTest3() {
	c := new(Car)
	c.GoToWorkIn()
}
