## （七）协程goroutine和通道channel.md

### 1. 并行、并发和协程
一个并发程序可以在一个处理器或内核上使用多个线程来执行任务，但是只有同一个程序在某个时间点同时运行在多核或者多处理器上才是真正的并行。
- 并行，是一种通过使用多处理器以提高速度的能力。
- 并发，可以是并行的，也可以不是。
- 协程（goroutine），go中，应用程序并发处理的部分被称作协程；它可以更有效的并发运算。

### 2. 协程和线程
协程和线程并无一对一的关系，协程是根据一个或多个线程的可用性，映射（多路复用，执行于）他们之上的，协程调度器在Go运行时很好的完成了这个工作。
Go使用通道(channel)来同步协程（goroutine）
协程是轻量的，比线程更轻；因为创建非常廉价，必要的时候可以轻松创建并运行大量的协程；

### 3. 通道channel
> Go有一个特殊的类型，通道（channel），像是管道，可以通过chan发送**类型化的数据**在协程之间通信，可以避开所有内存共享导致的坑；
通道的通信方式保证了同步性。数据通过通道，同一时间只有一个协程可以访问数据，所以不会出现数据竞争。
> 通道，实际上是类型化的消息队列，使数据得以传输；先进先出（FIFO）可以保证发送给他们的元素的顺序；
> 通道也是**引用类型**，所以使用`make()`函数来给他分配内存。
```
var ch chan string
ch=make(chan string)

ch:=make(chan string)

// 带缓冲通道
ch:=make(chan string, 100)
```

> 无缓冲通道会被阻塞；
> 带缓冲通道在缓冲用完前不阻塞，当缓冲满后会阻塞；
> 如果容量大于0，通道就是异步的：缓冲满载（发送）或变空（接收）之前通信不会阻塞，元素会按照发送的顺序被接收；
> 如果容量为0或者未设置，通信仅在收发双发准备好的情况下才可以成功；

> 无缓冲通道，可以作为多个协程同步的完美工具。

### 4. 示例
```
// go_routine project main.go
package main

import (
	"fmt"
	"time"
)

func main() {
	//test_0()
	test_1()
	//test_2()
	//test_3()
	//test_4()
}

func longWait() {
	fmt.Println("begine long wait ...")
	time.Sleep(5 * 1e9)
	fmt.Println("end of long wait")
}

func shortWait() {
	fmt.Println("begine short wait ...")
	time.Sleep(2 * 1e9)
	fmt.Println("end of short wait")
}

func test_0() {
	go longWait()
	go shortWait()

	// wait for go functions stop
	fmt.Println("about to sleep in test_0()")
	time.Sleep(10 * 1e9)
	fmt.Println("at the end of test_0()")
}

func test_1() {
	ch := make(chan string)

	go sendData(ch)
	go getData(ch)

	time.Sleep(1e9)
}

func sendData(ch chan string) {
	ch <- "i"
	ch <- "love"
	ch <- "you"

	// 关闭通道
	close(ch)
}

// 推荐使用for-range
func getData(ch chan string) {
	//	var data string
	//	data = <-ch
	//	fmt.Println(data)

	//	for i := 0; i < 3; i++ {
	//		dt := <-ch
	//		fmt.Println(dt)
	//	}

	// 给通道使用for-range循环
	// 使用for-range语句来读取通道是更好的方法，因为它会自动检测通道是否关闭
	//	for v := range ch {
	//		fmt.Printf("string is %s\n", v)
	//	}

	// 使用close和判断通道是否关闭
	for {
		data, open := <-ch // 判断
		if !open {
			break
		}
		fmt.Printf("string is %s\n", data)
	}
}

func test_2() {
	// 带缓冲的通道，10为容量
	ch := make(chan string, 10)
	fmt.Printf("cap is %d\n", cap(ch))
	ch <- "i love you"
	go getString(ch)
	//ch <- "i love you"

	time.Sleep(1e9)
}

func getString(ch chan string) {
	data := <-ch
	fmt.Printf("string is \"%s\"\n", data)
}

func test_3() {
	array := []int{1, 2, 3, 4, 5}

	ch := make(chan int)
	go sum(array[:], ch)
	//...
	result := <-ch // 使用通道达到了同步的目的
	fmt.Printf("result is %d\n", result)
}

// 协程中使用通道返回函数结果
func sum(array []int, ch chan int) {
	var result int
	for _, v := range array {
		result += v
	}
	fmt.Printf("result is %d\n", result)
	time.Sleep(5 * 1e9)
	ch <- result
}

func test_4() {
	done := make(chan bool)
	go doSomething(done)
	go func() {
		done <- true
	}()

	<-done
	fmt.Printf("done 1\n")
	<-done
	fmt.Printf("dong 2\n")
}

func doSomething(done chan bool) {
	fmt.Printf("do something ...\n")
	time.Sleep(2 * 1e9)
	done <- true
}

```
