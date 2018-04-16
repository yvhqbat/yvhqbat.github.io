
## redis的内存分配器
redis的内存分配器包装在文件zmalloc.h/zmalloc.c文件中

参考：
- [Redis采用不同内存分配器tcmalloc和jemalloc](https://blog.csdn.net/u010994304/article/details/49906819)
- [jemalloc的使用](https://blog.csdn.net/yefeng38083120/article/details/46367527)
- [github.com/jemalloc](https://github.com/jemalloc/jemalloc)
- [JEMALLOC(3)](https://www.freebsd.org/cgi/man.cgi?query=jemalloc&sektion=3)
- [jemalloc在linux上从安装到使用](https://blog.csdn.net/xiaofei_hah0000/article/details/52214592)

## jemalloc.h头文件的分析

## 内存碎片
1. 什么是内存碎片？
假设系统只有一片64字节的内存，分配给4个单元，每个16个字节： 

将这4个单元分配释放再重新分配4个12字节的内存片： 
我们发现多了4*4不连续的内存片，下次我们就不能分配12或者16字节的内存了。 

另外，glibc分配内存一般向4或者8取整，比如我们向申请13字节的内存，实际上得到的内存片会是16字节，多出来的3个字节我们不知道，也就无法使用了。

2. 内存碎片很可怕吗？ 
短时间内不明显，对于线上的服务器比如nginx,运行时间可能经年，每天几亿的请求量，如果每天产生100片 ，一年下来也是3万多片 ，相当恐怖！

## 实例
```
#include<iostream>
#include <string.h>
using namespace std;

/*
# 需要设置编译选项 -DJEMALLOC_NO_DEMANGLE
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -Wall -DJEMALLOC_NO_DEMANGLE")
*/
#include "jemalloc/jemalloc.h"

#define USE_JEMALLOC
// 使用jemalloc库,将malloc calloc realloc free 重定向到 je_malloc je_calloc je_realloc je_free.
#if defined(USE_JEMALLOC)
#define malloc(size) je_malloc(size)
#define calloc(count,size) je_calloc(count,size)
#define realloc(ptr,size) je_realloc(ptr,size)
#define free(ptr) je_free(ptr)
#endif

int main()
{
	char* p=(char*)malloc(100);
	memcpy(p,"liudong",8);
	cout<<p<<endl;
	free(p);
	
	return 0;
}
```




