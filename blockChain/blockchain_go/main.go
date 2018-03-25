// blockchain_go_ld project main.go
package main

import (
	"fmt"
	"strconv"
)

func main() {
	//	fmt.Println("Hello World!")

	//	// block
	//	b := NewBlock("liudong", []byte("liudongwho"))
	//	fmt.Println(b)
	//	fmt.Println(string(b.Data))

	bc := NewBlockChain()
	bc.AddBlock("block 1")
	bc.AddBlock("block 2")

	for _, b := range bc.blocks {
		fmt.Printf("prev hash:%x\n", b.PrevBlockHash)
		fmt.Printf("data: %s\n", b.Data)
		fmt.Printf("hash: %x\n", b.Hash)

		pow := NewProofOfWork(b)
		fmt.Printf("pow: %s\n", strconv.FormatBool(pow.Validate()))

		serialize := b.Serialize()
		fmt.Println("serialize is ", serialize)

		block := DeserializeBlock(serialize)
		fmt.Println(block)

		fmt.Println()
	}
}
