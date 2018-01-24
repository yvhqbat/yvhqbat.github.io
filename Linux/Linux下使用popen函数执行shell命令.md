
## Linux下使用popen函数执行shell命令

### 1. `popen()`函数

```
NAME
       popen, pclose - pipe stream to or from a process

SYNOPSIS
       #include <stdio.h>

       FILE *popen(const char *command, const char *type);

       int pclose(FILE *stream);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       popen(), pclose():
           _POSIX_C_SOURCE >= 2 || _XOPEN_SOURCE || _BSD_SOURCE || _SVID_SOURCE

DESCRIPTION
       The  popen()  function  opens  a  process by creating a pipe, forking, and invoking the shell.  Since a pipe is by definition unidirectional, the type argument may specify only
       reading or writing, not both; the resulting stream is correspondingly read-only or write-only.
       
RETURN VALUE
       The popen() function returns NULL if the fork(2) or pipe(2) calls fail, or if it cannot allocate memory.

       The  pclose()  function returns -1 if wait4(2) returns an error, or some other error is detected.  In the event of an error, these functions set errnro to indicate the cause of
       the error.
```

popen()函数通过创建一个管道，调用fork()产生一个子进程，执行一个shell以运行命令来开启一个进程。  
pclose()函数关闭标准I/O流，等待命令执行结束，然后返回shell的终止状态。如果shell不能被执行，则pclose()返回的终止状态与shell已执行exit一样。

### 2. 实例：使用popen获取cpu数目
linux下查看cpu数目的方法：`cat /proc/cpuinfo |grep processor |wc -l`

使用popen()函数的例子：
```
#include <stdio.h>
#include <unistd.h>

int
getCpuNum()
{
    char buffer[16]={0};
    FILE* stream=popen("cat /proc/cpuinfo |grep processor |wc -l", "r");
    if(nullptr != stream)
    {
        fread(buffer, 1, sizeof(buffer)-1, stream);
        pclose(stream);
    }

    int num=atoi(buffer);
    return num;
}
```
