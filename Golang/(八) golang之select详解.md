## (八) golang之select详解
> select实现了一种监听模式，通常用在（无限）循环中；在某种情况下，通过break语句使循环退出。

### 示例
```
// select project main.go
package main

import (
	"fmt"
	"time"
)

func main() {
	ch1 := make(chan int)
	ch2 := make(chan int)

	var cnt int
	// 计时器：time.Ticker结构体，以指定的时间间隔重复的向通道time.Ticker.C发送时间值
	ticker := time.NewTicker(2 * 1e9)
	defer ticker.Stop()

	// time.Tick函数，周期性的给返回的通道发送时间值
	chanRate := time.Tick(1 * 1e9)

	// 定时器：time.After()函数，在指定时间之后发送一次时间
	chanTimer := time.After(3 * 1e9)

	go pump1(ch1)
	go pump2(ch2)

	for {
		select {
		case v := <-ch1:
			fmt.Printf("received on channel 1: %d\n", v)
		case v := <-ch2:
			fmt.Printf("received on channel 2: %d\n", v)
		case t := <-ticker.C:
			cnt++
			fmt.Printf("ticker %d ... %v\n", cnt, t)
		case t := <-chanRate:
			fmt.Printf("time.Tick %v\n", t)
		case t := <-chanTimer:
			fmt.Printf("time is up, %v\n", t)
		}

		// 当达到一定的条件时，退出循环
		if cnt > 5 {
			fmt.Printf("break\n")
			break
		}
	}

}

func pump1(ch chan int) {
	for i := 0; ; i++ {
		ch <- i
		time.Sleep(1e9)
	}
}

func pump2(ch chan int) {
	for i := 0; ; i++ {
		ch <- i
		time.Sleep(2 * 1e9)
	}
}
```
