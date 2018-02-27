// rw project main.go
package main

import (
	"crypto/sha1"
	"fmt"
	"io"
)
func main() {
	crypto_demo()
}



// crypto包和hash包
// 通过网络传输的数据必须加密，以防止被hacker读取和篡改，并且保证发出的数据和收到的数据检验和一致。
func crypto_demo() {
	hasher := sha1.New()
	io.WriteString(hasher, "123456789")
	b := []byte{}
	result := hasher.Sum(b)
	fmt.Printf("result: %v\n", result)
	fmt.Printf("result: %x\n", result)
	fmt.Printf("result: %d\n", result)
}
