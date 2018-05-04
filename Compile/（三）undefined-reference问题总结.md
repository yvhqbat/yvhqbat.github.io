## （三）undefined reference问题总结

参考：[undefined reference问题总结](http://blog.51cto.com/ticktick/431329)，
这篇博客总结的很全面，囊括了几种可能的原因：

1. 链接时缺失了相关目标文件（.o）
2. 链接时缺少相关的库文件（.a/.so）
3. 链接的库文件中又使用了另一个库文件
4. 多个库文件链接顺序问题，依赖其他库的库一定要放到被依赖库的前面
5. 在c++代码中链接c语言的库，把与c语言库相关的头文件包含添加一个extern "C"的声明即可

```
extern "C"
{
#include "test.h"
}
```
