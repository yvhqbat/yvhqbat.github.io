## SIGHUP信号 -- 连接断开
参考：
- [SIGHUP信号与控制终端](https://blog.csdn.net/cugxueyu/article/details/2046565)
- [linux守护进程、SIGHUP与nohup详解](https://www.cnblogs.com/lvyahui/p/7389554.html)

## 如果不想在控制终端断开连接时程序退出，需要处理SIGHUP信号。
```
    // 忽视信号: SIGHUP, SIGPIPE 
    signal(SIGHUP, SIG_IGN);
    //signal(SIGPIPE, SIG_IGN);
```
