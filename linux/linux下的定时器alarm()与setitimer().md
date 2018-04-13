## 定时器

- alarm
- setitimer

参考：
- [Linux下的定时器：alarm()与setitimer()](https://www.cnblogs.com/lidabo/p/4652764.html)

### 1. alarm()函数
```
#include <unistd.h>

// 参数seconds是产生SIGALRM信号需要的秒数
unsigned int alarm(usigned int seconds);
```
> 使用alarm函数可以设置一个定时器，当定时器超时时，产生**SIGALRM**信号。如果忽略或不捕捉此信号，则其默认动作是终止调用该alarm函数的进程。
> 每个进程只能有一个闹钟时间；
> 需要设置SIGALRM信号处理函数。

### 2. setitimer()函数
```
NAME
       getitimer, setitimer - get or set value of an interval timer

SYNOPSIS
       #include <sys/time.h>

       int getitimer(int which, struct itimerval *curr_value);
       int setitimer(int which, const struct itimerval *new_value,
                     struct itimerval *old_value);
```
setitimer()比alarm功能强大  
setitimer()为其所在进程设置一个定时器，如果itimerval.it_interval不为0(it_interval的两个域都不为0)，则该定时器将持续有效(每隔一段时间就会发送一个信号)

### 3. pause()函数
```
#include <unistd.h>

int pause(void);
```
pause函数使调用进程挂起直至捕捉到一个信号。只有执行了一个信号处理程序并从其返回时，pause才返回。
