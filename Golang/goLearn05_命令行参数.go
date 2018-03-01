// demo project main.go
package main

import (
	"flag"
	"fmt"
	"os"
)

var n = flag.Bool("n", false, "n flag")
var sep = flag.String("s", "", "separator")

func main() {
	flag.Parse()
	//flag.PrintDefaults()
	fmt.Println(*n)
	fmt.Println(*sep)

	fmt.Println(os.Args)
}

// test
/*
demo# ./demo -n=1 -s="caipei"
  -n	n flag
  -s string
    	separator
[]
true
caipei
[./demo -n=1 -s=caipei]
*/
