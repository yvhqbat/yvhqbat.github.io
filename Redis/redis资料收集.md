
## redis资料收集
[yvhqbat-redis](http://blog.csdn.net/yvhqbat/article/category/6243356)

## 遇到的问题查阅
在阅读redis源码时，有很多未见多的知识，经过网上搜索后，记录在此，以便日后查看。

### 1. C 库函数 - setlocale()
[ C 库函数 - setlocale()](http://www.runoob.com/cprogramming/c-function-setlocale.html)

### 2. SHA1算法原理
[SHA1算法原理](https://www.cnblogs.com/scu-cjx/p/6878853.html)

### 3. linux中内核的一个不错的参数somaxconn
[linux中内核的一个不错的参数somaxconn](http://blog.csdn.net/taolinke/article/details/6800979)  
[Redis学习笔记五——启动警告问题的解决](http://blog.csdn.net/a491857321/article/details/52006376)

### 4. sigqueue函数 进程间通信
[sigqueue函数 进程间通信](http://blog.csdn.net/ccccdddxxx/article/details/6314360)

### 5. 守护进程
```
// 如果server.daemonize=true,则服务器以守护进程方式运行，默认为false.
if (server.daemonize) daemonize();
```

daemonize()函数：

```
// 将程序以守护进程方式运行
void daemonize(void) {
    int fd;

    if (fork() != 0) exit(0); /* parent exits */
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but
     * the 'logfile' is set to 'stdout' in the configuration file
     * it will not log at all. */
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
}
```
### 6. linux下overcommit_memory的问题
[linux下overcommit_memory的问题](http://blog.csdn.net/houjixin/article/details/46412557)

