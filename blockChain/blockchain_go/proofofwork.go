package main

import (
	"bytes"
	"crypto/sha256"
	"fmt"
	"math/big"
)

const targetBits = 24
const maxNoce = 100000000

// proof of work, 工作量证明
type ProofOfWork struct {
	block  *Block
	target *big.Int
}

func NewProofOfWork(b *Block) *ProofOfWork {
	target := big.NewInt(1)
	fmt.Println(target)
	target.Lsh(target, uint(256-targetBits))
	fmt.Println(target)
	pow := &ProofOfWork{b, target}
	//	pow := new(ProofOfWork)
	//	pow.block = b
	//	pow.target = target
	return pow
}

// prepare data to hash
func (pow *ProofOfWork) prepareData(nonce int) []byte {
	data := bytes.Join(
		[][]byte{
			pow.block.Data,
			pow.block.PrevBlockHash,
			IntToHex(pow.block.Timestamp),
			IntToHex(int64(targetBits)),
			IntToHex(int64(nonce)),
		},
		[]byte{},
	)
	return data
}

func (pow *ProofOfWork) Run() (int, []byte) {
	var hashInt big.Int
	var hash [32]byte
	nonce := 0
	fmt.Printf("block.data is %s\n", pow.block.Data)
	for nonce < maxNoce {
		data := pow.prepareData(nonce)
		hash = sha256.Sum256(data)
		hashInt.SetBytes(hash[:])

		if hashInt.Cmp(pow.target) == -1 {
			fmt.Printf("\r hash is %x\n", hash)
			break
		} else {
			nonce++
		}
	}
	return nonce, hash[:]
}

// proof
func (pow *ProofOfWork) Validate() bool {
	var hashInt big.Int

	data := pow.prepareData(pow.block.Nonce)
	hash := sha256.Sum256(data)
	hashInt.SetBytes(hash[:])

	return hashInt.Cmp(pow.target) == -1
}
