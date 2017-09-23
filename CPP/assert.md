## assert断言
assert 宏, 原型定义在<assert.h>中, 其作用是, 如果它的条件返回错误, 则终止程序执行.  
原型定义:
```
#include <assert.h>
void assert(int exprression);
```
先计算表达式expression, 如果其值为假(0), 那么先打印一条出错信息, 然后通过调用`abort`来终止程序运行.


使用`assert`的缺点是, 频繁的调用会极大的影响程序的性能, 增加额外的开销.  
在调试结束后, 可以通过在包含`#include <assert.h>`的语句之前插入`#define NDEBUG`来禁止使用`assert`调用.
```
#include <stdio.h>
#define NDEBUG
#include <assert.h>
```

## 用法总结
1. 在函数开始处检验传入参数的合法性.  
2. 每个`assert`只检验一个条件.  
如果同时检验多个条件,当断言失败,无法直观判断是哪个条件失败.  
3. 不能使用改变环境的语句.  
因为`assert`只在`DEBUG`生效, 如果那么做, 会使程序在真正运行时遇到问题.  
4. `assert`和后面的语句应空一行, 已形成逻辑和视觉上的一致性.  
5. 有的地方, `assert`不能代替条件过滤.  

## PS
程序一般分为`Debug`版本和`Release`版本, `Debug`版本用于内部调试, `Release`版本发行给用户使用.  

断言`assert`仅在`Debug`版本起作用的宏, 它用于检查**不应该发生的情况**.


