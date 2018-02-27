// rw project main.go
package main

import (
	"flag"
	"fmt"
	"os"
)

// flag包
var b = flag.Bool("b", false, "bool flag")

// init函数，在main之前自动执行
func init() {
	fmt.Println("parse flags")
	flag.Parse()
	flag.PrintDefaults()
}

func main() {
	// os.Args  --> 命令行参数列表
	fmt.Println(os.Args[0])
    
    // flag.Arg(i)
	fmt.Println(flag.Arg(0))
}
