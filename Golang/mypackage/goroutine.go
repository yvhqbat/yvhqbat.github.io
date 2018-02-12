package mypackage

import (
	"fmt"
	"time"
)

// simple test
func GoroutineTest() {
	fmt.Println("in GoroutineTest() ...")
	go longWait()
	go shortWait()
	fmt.Println("about to sleep in GoroutineTest()")
	time.Sleep(10 * 1e9)
	fmt.Println("at the end of GoroutineTest()")

}

func longWait() {
	fmt.Println("beginning longWait()")
	defer func() { fmt.Println("end of longWait()") }()
	time.Sleep(5 * 1e9)
}

func shortWait() {
	fmt.Println("beginning shortWait()")
	time.Sleep(2 * 1e9)
	fmt.Println("end of shortWait()")
}

// goroutine-channel test
type Data string

func GoroutineChannelTest() {
	fmt.Println("GoroutineChannelTest...")

	chanData := make(chan Data)

	go SendData("13", chanData)
	go SendData("3", chanData)

	go GetDataRoutine(chanData)

	time.Sleep(1 * 1e9)

}

func SendData(data Data, chanData chan Data) {
	chanData <- data
}

func GetData(chanData chan Data) Data {
	var data Data
	data = <-chanData
	return data
}

func GetDataRoutine(chanData chan Data) {
	//	for i := 0; i < 2; i++ {
	//		data := GetData(chanData)
	//		//data := <-chanData
	//		fmt.Println(data)
	//	}

	// for-range 用在channel上，从通道获取值
	for v := range chanData {
		fmt.Printf("for-range test, v is %v\n", v)
	}
}

// goroutine-channel deadlock test
// fatal error: all goroutines are asleep - deadlock!
// 原因在于，无缓冲通道会被阻塞
func DeadLockTest() {
	chanInt := make(chan int)
	// 在缓冲满载之前，给一个带缓冲的通道发送数据是不会被阻塞的；
	// 而从通道读取数据也不会阻塞直到缓冲空了。
	// chanInt := make(chan int, 10)
	chanInt <- 17
	go GetInt(chanInt)
	time.Sleep(1 * 1e9)
}

func GetInt(chanInt chan int) {
	fmt.Println(<-chanInt)
}

// 同步：协程中用通道输出结果
func SynchronizationTest() {
	array := make([]int, 10)
	for i := 0; i < len(array); i++ {
		array[i] = i
	}
	chanSum := make(chan int)
	go Sum(array, chanSum)
	// ... do other things
	result := <-chanSum //等待Sum执行完成，即同步
	fmt.Printf("array sum is %d\n", result)
}

func Sum(array []int, chanSum chan int) {
	var result int
	for i := 0; i < len(array); i++ {
		result += array[i]
	}
	chanSum <- result
}

// select 切换协程
func SelectTest() {
	chan1 := make
}

func pump1(chan1 chan int) {

}

func pump2(chan2 chan int) {

}
