
## SIGPIPE信号

> 当一个进程向某个已收到RST的套接字执行写操作时，内核向该进程发送一个SIGPIPE信号。
该信号的默认行为是终止进程，因此进程必须捕获它以免不情愿的被终止。
不论该进程是捕获了该信号并从其信号处理函数返回，还是简单地忽略该信号，写操作都将返回EPIPE错误。

对一个对端已经关闭的socket调用两次write, 第一次write引发一个RST，第二次write会生成SIGPIPE信号, 该信号默认结束进程.

[参考博客](https://yq.aliyun.com/articles/42215)

## SIGPIPE信号的处理方式

### 1. 直接忽略
```
if(SIG_ERR == signal(SIGPIPE, SIG_IGN))
{
    return 1;
}
```

### 2. 使用sigaction替代signal, 避免signal系统调用问题

```
struct sigaction sa;

sa.sa_handler = SIG_IGN;
sigemptyset(&sa.sa_mask);
sa.sa_flags = 0;

if (sigaction(SIGPIPE, &sa, NULL) < 0)
{
    perror("cannot ignore SIGPIPE");
	return -1;
}
```

### 3. sigaction捕获信号后处理
常见处理方式是，信号处理函数为空。
