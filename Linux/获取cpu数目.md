
## 获取cpu数目

写的代码时一定要考虑可移植性。
一个进程开启的线程数量与CPU个数相关，而不同的机器CPU的数目不同，当代码从一个机器移到另外一个机器时，不要手工修改相关参数，而是自动获取CPU数目从而创建合适的线程数目。

### 1. Linux命令查看

`cat /proc/cpuinfo |grep processor|wc -l`

### 2. `std::thread::hardware_concurrency()`
```
#include <iostream>
#include <thread>
 
int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
}
```

### 3. python

```
from multiprocessing import cpu_count
print(cpu_count())
```
