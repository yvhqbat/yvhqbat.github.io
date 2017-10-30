## 开发必备Linux命令

2017年10月26日
10:24

###	1. 日志查询类
#### 1.1 按关键字不分页查询
```
grep "applyld" app.log
```

#### 1.2 按关键字从前往后分页查询
```
cat -n app.log | grep "applyld" | more
// -n 打印行号
// more 分页显示
```

#### 1.3 按关键字只显示最后M行查询
```
tail -n M app.log | grep "applyld"
// M为行数
```

#### 1.4 日志太多, 将相关日志输出到文件后查看
```
cat -n app.log | grep "applyld" > app_new.log
```

### 2. 端口查询类

#### 2.1 查看端口使用情况(tcp/udp/unix)
```
root@ubuntu:/home/ld# netstat -aln
Active Internet connections (servers and established)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 0.0.0.0:8005            0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN     
tcp        0      0 10.16.138.66:22         10.16.138.13:50733      ESTABLISHED
tcp6       0      0 :::34091                :::*                    LISTEN     
tcp6       0      0 :::111                  :::*                    LISTEN     
tcp6       0      0 :::22                   :::*                    LISTEN     
tcp6       0      0 ::1:631                 :::*                    LISTEN     
udp        0      0 0.0.0.0:111             0.0.0.0:*                          
udp        0      0 10.16.138.66:123        0.0.0.0:*                          
udp        0      0 127.0.0.1:123           0.0.0.0:*                          
udp        0      0 0.0.0.0:123             0.0.0.0:*                          
udp        0      0 0.0.0.0:41476           0.0.0.0:*                                                
udp6       0      0 :::949                  :::*                               
udp6       0      0 :::54277                :::*                               
udp6       0      0 :::5353                 :::*                               
Active UNIX domain sockets (servers and established)
Proto RefCnt Flags       Type       State         I-Node   Path
unix  2      [ ACC ]     SEQPACKET  LISTENING     2831     /run/udev/control
unix  2      [ ACC ]     STREAM     LISTENING     14482    @/tmp/dbus-dUQOfEQD
unix  2      [ ACC ]     STREAM     LISTENING     2844     /var/run/dbus/system_bus_socket
unix  2      [ ACC ]     STREAM     LISTENING     14278    @/tmp/.X11-unix/X0
```

#### 2.2 查看指定端口的使用情况
```
root@ubuntu:/home/ld# netstat -ano | grep 8005
tcp        0      0 0.0.0.0:8005            0.0.0.0:*               LISTEN      off (0.00/0/0)
tcp        0      0 10.16.138.66:8005       10.1.64.80:52677        ESTABLISHED off (0.00/0/0)
```

#### 2.3 查看占用指定端口的进程
```
root@ubuntu:/home/ld# sudo lsof -i:8005
COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
server  27415 root    9u  IPv4 261791      0t0  TCP *:8005 (LISTEN)
server  27415 root   10u  IPv4 261792      0t0  TCP 10.16.138.66:8005->10.1.64.80:52677 (ESTABLISHED)
```

### 3. 查看网络连接
#### 3.1 列出所有的网络连接(tcp/udp)
```
lsof -i
```
#### 3.2 列出所有的tcp网络连接
```
lsof -i tcp
```

#### 3.3 列出所有的udp网络连接
```
lsof -i udp
```
#### 3.4 列出指定的tcp端口情况
```
lsof -i tcp:80
```

#### 3.5 列出指定的udp端口情况
```
lsof -i udp:80
```

### 4. 查看资源使用情况

#### 4.1 查看系统中各个进程的资源占用状况
```
top
// 使用top后, 按 Shift+M 显示结果将按照进程内存占用率排序
```
#### 4.2 查看内存使用情况
```
free -m
// -m 以MB为单位
```

#### 4.3 查看磁盘空间使用情况
```
df -h
```

#### 4.4 查看cpu使用率/内存/虚拟内存交换情况/IO读写情况
```
root@ubuntu:/home/ld# vmstat 5  // 每5秒刷新一次
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  0      0 1805432  22904 1304308    0    0     1     1   15    4  7  7 86  0  0
 1  0      0 1805556  22904 1304308    0    0     0     2  327  445  7 18 75  0  0
```

### 5. 进程操作

 #### 5.1 根据名称查询进程
使用标准格式显示
```
root@ubuntu:/home/ld# ps -ef | grep 'server'
root     27415 26076 99 13:51 pts/28   00:33:31 ./server
root     28648  8015  0 14:25 pts/27   00:00:00 grep --color=auto server
```
使用BSD格式显示
```
root@ubuntu:/home/ld# ps -aux | grep 'server'
root     27415 99.4  0.7  85792 30956 pts/28   Sl+  13:51  33:43 ./server
root     28703  0.0  0.0   3788   668 pts/27   S+   14:25   0:00 grep --color=auto server
```

#### 5.2 杀掉进程

kill -9 pid  //pid 为相应的进程号
```
root@ubuntu:/home/ld# kill -9 27415
```
### 6. 文件复制
	scp 是一种安全方式的文件复制, 基于ssh.
#### 6.1 复制本地文件到远程
```
scp ./test.txt root@10.16.138.66:/home/liudong11/
// 如果复制目录, 需要使用 -r
```
#### 6.2 复制远程文件到本地
```
scp root@10.16.138.66:/home/liudong11/test.txt ./
 ```
