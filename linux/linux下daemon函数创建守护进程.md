## 守护进程

[参考博客：守护进程详解及创建，daemon()使用](http://www.cnblogs.com/mickole/p/3188321.html)

### 1. 守护进程
    守护进程（daemon），是运行在后台的一种特殊进程。
	
### 2. linux下daemon()函数创建守护进程

daemon()函数说明：

```
NAME
       daemon - run in the background

SYNOPSIS
       #include <unistd.h>

       int daemon(int nochdir, int noclose);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       daemon(): _BSD_SOURCE || (_XOPEN_SOURCE && _XOPEN_SOURCE < 500)

DESCRIPTION
       The daemon() function is for programs wishing to detach themselves from the controlling terminal and run in the background as system daemons.

       If nochdir is zero, daemon() changes the calling process's current working directory to the root directory ("/"); otherwise, the current working directory is left unchanged.

       If noclose is zero, daemon() redirects standard input, standard output and standard error to /dev/null; otherwise, no changes are made to these file descriptors.

RETURN VALUE
       (This  function  forks,  and  if  the fork(2) succeeds, the parent calls _exit(2), so that further errors are seen by the child only.)  On success daemon() returns zero.  If an
       error occurs, daemon() returns -1 and sets errno to any of the errors specified for the fork(2) and setsid(2).
```

实例：

```
#include <unistd.h>
#include <fcntl.h>

#include <time.h>
#include <string.h>

#include <iostream>
using namespace std;


int
main(int argc, char** argv)
{
    if(-1 == daemon(0, 1))
    {
        cout<<"daemon error"<<endl;
        exit(-1);
    }

    while(1)
    {
        int fd=open("daemon.log", O_RDWR|O_CREAT|O_APPEND);
        if(-1==fd)
        {
            cout<<"open file error"<<endl;
            exit(-2);
        }

        time_t t=time(NULL);
        char *buf=asctime(localtime(&t));
        write(fd, buf, strlen(buf));
        close(fd);

        sleep(2);
    }

    return 0;
}
```
 	
### 3. 进程相关的linux命令
- ps 命令
ps命令，打印系统中各个进程的状态。
```
ps -ef|grep ***
```

- pidof 命令
pidof 打印某个程序的pid
```
pidof systemd
```
