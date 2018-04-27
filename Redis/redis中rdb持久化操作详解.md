## rdb
涉及的文件：
- rio.h  // io操作，是对文件读写，缓存读写，文件描述法集合读写的统一接口封装
- rio.c
- rdb.h  // 有关rdb文件的save和load的相关操作，用到了rio接口
- rdb.c
- redis-check-dump.c  // 读dump.rdb文件，并进行检查
- dump.rdb

## dump.rdb文件详解
- [Redis源码分析（十二）--- redis-check-dump本地数据库检测](https://blog.csdn.net/androidlushangderen/article/details/40190195)
- [Redis RDB文件结构](https://blog.csdn.net/focus_zhu/article/details/46757869)
- [redis快照文件dump.rdb解析工具--redis-rdb-tools](https://blog.csdn.net/yanshu2012/article/details/50556812)
- [Parse Redis dump.rdb files, Analyze Memory, and Export Data to JSON](https://github.com/sripathikrishnan/redis-rdb-tools)

## rdb.h代码阅读及注释
rdb中的数据存储的基本格式为[len][data]，前面使用字节表示的长度，后面是真实的数据;

redis在数据存储方面上，把内存消耗降到了极致。比如只要是在数据库中保存的长度等数字的，必须经过计算判断，然后再分配相应的字节保存;
字符串等非数值存储，redis在这里采用了lzf压缩算法，当然取出的时候，进行解压.

有一个比较特殊的后台保存到数据库的方法，因为redis其实和mencached一样，是内存数据库，如果对数据的操作都直接是写入磁盘，I/O开销肯定很大，所以一般内存数据库都是先把操作结构都存放在内存中，等到了内存的数据满了，再持久化到磁盘中，就是保存数据库操作到文件中了。redis在这里还很人性化的提供了backgroundSave()的方式，使用fork的方法由子进程进行操作。

```
/*
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __REDIS_RDB_H
#define __REDIS_RDB_H

#include <stdio.h>
#include "rio.h"

/* TBD: include only necessary headers. */
#include "redis.h"

/* The current RDB version. When the format changes in a way that is no longer
 * backward compatible this number gets incremented. */
#define REDIS_RDB_VERSION 6

/* Defines related to the dump file format. To store 32 bits lengths for short
 * keys requires a lot of space, so we check the most significant 2 bits of
 * the first byte to interpreter the length:
 *
 * 00|000000 => if the two MSB are 00 the len is the 6 bits of this byte
 * 01|000000 00000000 =>  01, the len is 14 byes, 6 bits + 8 bits of next byte
 * 10|000000 [32 bit integer] => if it's 01, a full 32 bit len will follow
 * 11|000000 this means: specially encoded object will follow. The six bits
 *           number specify the kind of object that follows.
 *           See the REDIS_RDB_ENC_* defines.
 *
 * Lengths up to 63 are stored using a single byte, most DB keys, and may
 * values, will fit inside. */
// 长度所占的空间
#define REDIS_RDB_6BITLEN 0        // 2bits保存宏，6bits保存len，占1byte
#define REDIS_RDB_14BITLEN 1       // 2bits保存宏，14bits保存len，占2bytes
#define REDIS_RDB_32BITLEN 2       // 1byte保存宏，4bytes保存len，占5bytes
#define REDIS_RDB_ENCVAL 3
#define REDIS_RDB_LENERR UINT_MAX

/* When a length of a string object stored on disk has the first two bits
 * set, the remaining two bits specify a special encoding for the object
 * accordingly to the following defines: */
#define REDIS_RDB_ENC_INT8 0        /* 8 bit signed integer */
#define REDIS_RDB_ENC_INT16 1       /* 16 bit signed integer */
#define REDIS_RDB_ENC_INT32 2       /* 32 bit signed integer */
#define REDIS_RDB_ENC_LZF 3         /* string compressed with FASTLZ */

/* Dup object types to RDB object types. Only reason is readability (are we
 * dealing with RDB types or with in-memory object types?). */
// 五种基本类型
#define REDIS_RDB_TYPE_STRING 0
#define REDIS_RDB_TYPE_LIST   1
#define REDIS_RDB_TYPE_SET    2
#define REDIS_RDB_TYPE_ZSET   3
#define REDIS_RDB_TYPE_HASH   4

/* Object types for encoded objects. */
// 编码类型
#define REDIS_RDB_TYPE_HASH_ZIPMAP    9
#define REDIS_RDB_TYPE_LIST_ZIPLIST  10
#define REDIS_RDB_TYPE_SET_INTSET    11
#define REDIS_RDB_TYPE_ZSET_ZIPLIST  12
#define REDIS_RDB_TYPE_HASH_ZIPLIST  13

/* Test if a type is an object type. */
// 类型检查
#define rdbIsObjectType(t) ((t >= 0 && t <= 4) || (t >= 9 && t <= 13))

/* Special RDB opcodes (saved/loaded with rdbSaveType/rdbLoadType). */
// opcode: operation code --> 操作码
#define REDIS_RDB_OPCODE_EXPIRETIME_MS 252
#define REDIS_RDB_OPCODE_EXPIRETIME 253
#define REDIS_RDB_OPCODE_SELECTDB   254
#define REDIS_RDB_OPCODE_EOF        255

// APIs
// rdbsave... rdbload...


/*============== type ================================*/
// 写type到rio， type占一个字节，unsigned char
int rdbSaveType(rio *rdb, unsigned char type);

// 从rio中读1个字节的数据，作为type返回
int rdbLoadType(rio *rdb);

/*============= time_t ===============================*/
// 写time_t到rio, 4个字节
int rdbSaveTime(rio *rdb, time_t t);

// 从rio读4个字节数据，作为时间返回
time_t rdbLoadTime(rio *rdb);

/*============== len =================================*/
// 写len到rio, 根据len的大小，来决定占用几个字节(1/2/4)
int rdbSaveLen(rio *rdb, uint32_t len);

// 从rio读取len
uint32_t rdbLoadLen(rio *rdb, int *isencoded);

/*============= 对 type 的Wrapper =====================*/
// 分析o->type,然后调用rdbSaveType()函数写入type到rio
int rdbSaveObjectType(rio *rdb, robj *o);
// 调用rdbLoadType()读取类型，并判断是否为ObjectType
int rdbLoadObjectType(rio *rdb);

// 从dump.rdb文件中加载数据，保存到服务器数据库中
int rdbLoad(char *filename);

// 创建子进程，持久化数据到rdb文件
int rdbSaveBackground(char *filename);

// 向slaves发送rdb数据
int rdbSaveToSlavesSockets(void);

// 删除子进程持久化时用到的临时文件
void rdbRemoveTempFile(pid_t childpid);

int rdbSave(char *filename);

// 写o到rio， 保存object到rio
int rdbSaveObject(rio *rdb, robj *o);
off_t rdbSavedObjectLen(robj *o);
off_t rdbSavedObjectPages(robj *o);

// 根据类型从rio中读object
robj *rdbLoadObject(int type, rio *rdb);


void backgroundSaveDoneHandler(int exitcode, int bysignal);

// 写key-value到rio
int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val, long long expiretime, long long now);

robj *rdbLoadStringObject(rio *rdb);

#endif

```

### redis-check-dump.c代码阅读

在读取dump.rdb文件时，并不是普通的读取文件，而是采用了存储映射；
```
    // 打开文件
    fd = open(argv[1], O_RDONLY);
	
    // 使用了mmap()函数进行存储映射
    data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

    // check
    process();

    munmap(data, size);
    close(fd);

```

### dump.rdb文件末尾保存有校验码，利用crc64校验数据传输的完整性；
主要文件：
- crc64.h
- crc64.c
- crc16.c

crc64.h
```
#ifndef CRC64_H
#define CRC64_H

#include <stdint.h>

// 计算一块数据的crc64值
uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l);

#endif

```

crc64参考：
- [利用crc64校验数据传输的完整性](https://www.alibabacloud.com/help/zh/doc-detail/43394.htm)
- [Redis源码中的CRC校验码（crc16、crc64）原理浅析](https://www.alibabacloud.com/help/zh/doc-detail/43394.htm)

类似算法还有MD5 Message Digest Algorithm MD5（中文名为消息摘要算法第五版）为计算机安全领域广泛使用的一种散列函数，用以提供消息的完整性保护。
参考: 
- [百度百科MD5](https://baike.baidu.com/item/MD5/212708?fr=aladdin)
