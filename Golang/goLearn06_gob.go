// rw project main.go
package main

import (
	"bytes"
	"encoding/gob"
	"fmt"
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
	gob_demo()
}

// encoding/gob
type Person struct {
	Name string
	Age  int
}

func gob_demo() {
	var person1 Person
	person1.Name = "tom"
	person1.Age = 23

	var buf bytes.Buffer
	enc := gob.NewEncoder(&buf)
	err := enc.Encode(person1)
	if err != nil {
		fmt.Println("encode error:", err)
		return
	}

	fmt.Printf("ater encoding, buf is: %v\n", buf)

	var person2 Person
	dec := gob.NewDecoder(&buf)
	err = dec.Decode(&person2)
	if err != nil {
		fmt.Println("decode error:", err)
		return
	}
	fmt.Printf("after decoding, name is %s, age is %d\n", person2.Name, person2.Age)
}
