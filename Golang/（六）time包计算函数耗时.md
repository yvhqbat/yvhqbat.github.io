## time包计算函数耗时

```
// demo project main.go
package main

import (
	"fmt"
	"time"
)

func main() {
	time_use()
}

func dosomething() {
	fmt.Println("start")
	time.Sleep(2 * 10e8)
	fmt.Println("end")
}

// time use
func time_use() {
	start := time.Now()
	dosomething()
	end := time.Now()
	cost := end.Sub(start)
	fmt.Printf("time used %v\n", cost)
}
```
