
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

### 7. sigaction()函数设置信号处理函数
```
// 设置信号处理函数，当SIGTERN, SIGINT时，退出程序
void setupSignalHandlers(void) {
    struct sigaction act;

    /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction is used.
     * Otherwise, sa_handler is used. */
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sigShutdownHandler;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);

#ifdef HAVE_BACKTRACE
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_NODEFER | SA_RESETHAND | SA_SIGINFO;
    act.sa_sigaction = sigsegvHandler;
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGBUS, &act, NULL);
    sigaction(SIGFPE, &act, NULL);
    sigaction(SIGILL, &act, NULL);
#endif
    return;
}
```

### 8. 保存进程ID到文件
```
void createPidFile(void) {
    /* Try to write the pid file in a best-effort way. */
    FILE *fp = fopen(server.pidfile,"w");
    if (fp) {
        fprintf(fp,"%d\n",(int)getpid());
        fclose(fp);
    }
}
```

### 8. LRU approximation algorithm
```
/*
 * LRU approximation algorithm
 *
 * Redis uses an approximation of the LRU algorithm that runs in constant
 * memory. Every time there is a key to expire, we sample N keys (with
 * N very small, usually in around 5) to populate a pool of best keys to
 * evict of M keys (the pool size is defined by REDIS_EVICTION_POOL_SIZE).
 *
 * The N keys sampled are added in the pool of good keys to expire (the one
 * with an old access time) if they are better than one of the current keys
 * in the pool.
 *
 * After the pool is populated, the best key we have in the pool is expired.
 * However note that we don't remove keys from the pool when they are deleted
 * so the pool may contain keys that no longer exist.
 *
 * When we try to evict a key, and all the entries in the pool don't exist
 * we populate it again. This time we'll be sure that the pool has at least
 * one key that can be evicted, if there is at least one key that can be
 * evicted in the whole database. */
```

参考：  
- [Redis作为LRU缓存](http://redis.majunwei.com/topics/lru-cache.html)
- [Modified Pseudo LRU Replacement Algorithm：改进的伪LRU替换算法](http://www.docin.com/p-800624016.html)
