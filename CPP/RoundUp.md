## round up
> 将data上调至ALIGN的倍数

```
#include <iostream>
using namespace std;

/** @enum
 *  @brief  对齐
 */
enum{ ALIGN = 8 };

/** @fn size_t RoundUp(size_t data)
 *  @brief  将data上调至ALIGN的倍数
 */
size_t RoundUp(size_t data)
{
	return (data + ALIGN - 1)&~(ALIGN - 1);
}

/* 测试 */
int main()
{
	for (int data = 0; data < 100; data++)
	{
		cout << RoundUp(data) << endl;
	}
}

```

参考: SGI Stl_alloc.h
```
__default_alloc_template::_S_round_up(size_t __bytes) 
{ return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }
```
