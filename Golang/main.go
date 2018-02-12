// structLearn project main.go
package main

import (
	"fmt"

	"mypackage"
)

func main() {
	//	structTest()

	//	mypackageTest()

	//	mypackage.MethodTest()
	//	mypackage.MethodTest2()
	//	mypackage.MethodTest3()

	//	mypackage.MemTest()

	//	mypackage.InterfaceTest()
	//	mypackage.VectorTest()

	//mypackage.GoroutineTest()
	mypackage.GoroutineChannelTest()
	//mypackage.DeadLockTest()
	mypackage.SynchronizationTest()
}

type STUDENT struct {
	name string
	age  int
}

func structTest() {
	var st STUDENT
	st.name = "dog"
	st.age = 26

	fmt.Println(st)
	fmt.Println("name:", st.name, ", age", st.age)
}

func mypackageTest() {
	var st mypackage.StructTest
	st.Name = "liudong"
	//st.id = 11  // 只有首字母大写才可见

	ot := new(mypackage.Outer)
	ot.OuterName = "dogge"
	ot.OuterAge = 3
	ot.InnerName = "inner dogge"
	//ot.innerAge = 13 //开头小写，对外不可见
	fmt.Println(ot)
	fmt.Println(ot.InnerName)
}
