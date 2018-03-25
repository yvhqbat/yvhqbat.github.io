package main

import (
	"bytes"
	"crypto/sha256"
	"encoding/gob"
	"fmt"
	"strconv"
	"time"
)

type Block struct {
	Timestamp     int64
	Data          []byte
	PrevBlockHash []byte
	Nonce         int
	Hash          []byte
}

func NewBlock(data string, prevBlockHash []byte) *Block {
	b := new(Block)
	b.Timestamp = time.Now().Unix()
	b.Data = []byte(data)
	b.PrevBlockHash = prevBlockHash
	//b.SetHash()
	pow := NewProofOfWork(b)
	nonce, hash := pow.Run()
	b.Nonce = nonce
	b.Hash = hash[:]
	return b
}

func (b *Block) SetHash() {
	timestamp := []byte(strconv.FormatInt(b.Timestamp, 10))
	headers := bytes.Join([][]byte{timestamp, b.Data, b.PrevBlockHash}, []byte{})
	hash := sha256.Sum256(headers)
	b.Hash = hash[:]
}

// 序列化，使用encoding/gob
func (b *Block) Serialize() []byte {
	var result bytes.Buffer
	encoder := gob.NewEncoder(&result)
	err := encoder.Encode(b)
	if err != nil {
		fmt.Println("encode block error.")
		return []byte{}
	}
	return result.Bytes()
}

// 反序列化
func DeserializeBlock(d []byte) *Block {
	var block Block
	decode := gob.NewDecoder(bytes.NewReader(d))
	err := decode.Decode(&block)
	if err != nil {
		fmt.Println("decode error")
		return nil
	}
	return &block
}
