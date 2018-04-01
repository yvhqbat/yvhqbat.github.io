
# 区块链笔记

## 参考资料
- [七月在线课程](https://github.com/yingl/julyedu/blob/master/201801_blockchain_open/lesson_01.md)
- [中本聪(Satoshi Nakamoto)比特币白皮书](https://github.com/GammaGao/bitcoinwhitepaper)
- [Blockchain in Go](https://github.com/Jeiwan/blockchain_go)
- [Blockchain Tutorial](https://github.com/liuchengxu/blockchain-tutorial)

- [比特币账户模型：UTXO](http://book.51cto.com/art/201711/558936.htm)
- [白话区块链](http://book.51cto.com/art/201711/558912.htm)

## Base58编解码
参考：
- [比特币中的Base58 编码](https://www.jianshu.com/p/e002931bb38b)
- [百度百科 base64](https://baike.baidu.com/item/base64/8545775)

base58和base64一样是一种二进制转可视字符串的算法，主要用来转换大整数值。区别是，转换出来的字符串，去除了几个看起来会产生歧义的字符，如 0 (零), O (大写字母O), I (大写的字母i) and l (小写的字母L) ，和几个影响双击选择的字符，如/, +。结果字符集正好58个字符(包括9个数字，24个大写字母，25个小写字母)。不同的应用实现中，base58 最后查询的字母表可能不同，所以没有具体的标准。

Base58 的输入是一个[0,256)的值的流，输出结果是一个[0,58) 的值的流。然后将每个值去查字母表，得出一个可视字符串。
转换过程实际上就是一个256进制的值转换为一个58进制的值。

- [Go 的base58库](https://github.com/shengdoushi/base58)
- [python 内置base64编解码库](https://docs.python.org/3/library/base64.html)

## 加密算法
参考：
- [常用加密算法概述](http://www.cnblogs.com/colife/p/5566789.html)

## 非对称加密
比特币采用了非对称加密机制，使用公钥生成账号地址，同时在交易中使用私钥签名，如果公钥无法验证私钥签名的话，就意味着这笔交易无效。虽然公钥在网上完全公开，但是因为没有私钥无法构造签名，所以伪造交易记录变得几乎不可能。

## hash算法

1. hash
网络传输数据的时候，A收到B的传过来的文件，需要确认收到的文件有没有损坏。如何解决？

有一种方法是B在传文件之前先把文件的hash结果给A，A收到文件再计算一次哈希然后和收到的哈希比较就知道文件有无损坏。

2. hash list
当文件很大的时候，往往需要把文件拆分很多的数据块各自传输，这个时候就需要知道每个数据块的哈希值。怎么办呢？

这种情况，可以在下载数据之前先下载一份哈希列表(hash list)，这个列表每一项对应一个数据块的哈希值。对这个hash list拼接后可以计算一个根hash。实际应用中，我们只要确保从一个可信的渠道获取正确的根hash，就可以确保下载正确的文件。

似乎很完美了。但是还不够好！基于hash list的方案这样一个问题:有些时候我们获取(遍历)所有数据块的hash list代价比较大，只能获取部分节点的哈希。

3. Merkle tree
有没有一种方法可以通过部分hash就能校验整个文件的完整性呢？

答案是肯定的，merkle tree能做到。

## Merkle Tree(默克尔树)算法
参考：
- [Merkle Tree（默克尔树）算法解析](https://blog.csdn.net/wo541075754/article/details/54632929)
- [Merkle Tree与区块链](https://blog.csdn.net/pony_maggie/article/details/74538902)

Merkel树和区块链的链没啥关系，主要是区块内部用于验证交易的完整性以及验证某个交易是否合法。

## 去中心化

- [为什么说去中心化很重要](https://ethfans.org/posts/why-decentralization-matters)

## 区块与交易
本质上就是账本。利用区块记录曾经发生的交易。比特币的每个区块本质上是一系列交易的打包，而挖矿就是争夺打包的权利。

