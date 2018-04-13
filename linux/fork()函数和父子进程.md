## fork函数
```
NAME
       fork - create a child process

SYNOPSIS
       #include <unistd.h>

       pid_t fork(void);

DESCRIPTION
       fork()  creates  a  new process by duplicating the calling process.  The new process, referred to as the child.

RETURN VALUE
       On  success, the PID of the child process is returned in the parent, and 0 is returned in the child.  On failure, -1 is returned in the parent, no child process is created, and
       errno is set appropriately.
```
> fork()函数调用一次返回两次；
> 子进程和父进程继续执行fork调用之后的指令。子进程是父进程的**副本**，子进程获得父进程数据空间、堆和栈的副本，父进程和子进程并不共享这些存储空间。父进程和子进程共享正文段。
> 写时复制(Copy-On-Write)。

> fork之后，父子进程哪个先执行与操作系统（调度算法）有关，在实际应用中并不重要，如果父子进程需要协同，可以通过进程间通信IPC，常用的是管道pipe()函数。
如redis中在后台持久化数据到文件即创建一个子进程，并通过pipe和父进程进行协同合作。

## 父进程和子进程的继承关系
### 子进程自父进程继承到：     
1.进程的资格(真实(real)/有效(effective)/已保存(saved)用户号(UIDs)和组号(GIDs))
2.环境(environment)
3.堆栈
4.内存
5.打开文件的描述符(注意对应的文件的位置由父子进程共享，这会引起含糊情况)
6.执行时关闭(close-on-exec) 标志 (译者注：close-on-exec标志可通过fnctl()对文件描述符设置，POSIX.1要求所有目录流都必须在exec函数调用时关闭。更详细说明，参见《UNIX环境高级编程》 W. R. Stevens, 1993, 尤晋元等译(以下简称《高级编程》), 3.13节和8.9节)
7.信号(signal)控制设定
8.nice值 (译者注：nice值由nice函数设定，该值表示进程的优先级，数值越小，优先级越高)
进程调度类别(scheduler class)(译者注：进程调度类别指进程在系统中被调度时所属的类别，不同类别有不同优先级，根据进程调度类别和nice值，进程调度程序可计算出每个进程的全局优先级(Global process prority)，优先级高的进程优先执行)
8.进程组号
9.对话期ID(Session ID) (译者注：译文取自《高级编程》，指：进程所属的对话期(session)ID， 一个对话期包括一个或多个进程组， 更详细说明参见《高级编程》9.5节)
10.当前工作目录
11.根目录 (译者注：根目录不一定是“/”，它可由chroot函数改变)
12.文件方式创建屏蔽字(file mode creation mask (umask))(译者注：译文取自《高级编程》，指：创建新文件的缺省屏蔽字)
13.资源限制
14.控制终端

### 子进程所独有：

进程号
1.不同的父进程号(译者注：即子进程的父进程号与父进程的父进程号不同， 父进程号可由getppid函数得到)
2.自己的文件描述符和目录流的拷贝(译者注：目录流由opendir函数创建，因其为顺序读取，顾称“目录流”)
3.子进程不继承父进程的进程，正文(text)， 数据和其它锁定内存(memory locks)(译者注：锁定内存指被锁定的虚拟内存页，锁定后，4.不允许内核将其在必要时换出(page out)，详细说明参见《The GNU C Library Reference Manual》 2.2版， 1999, 3.4.2节)
5.在tms结构中的系统时间(译者注：tms结构可由times函数获得，它保存四个数据用于记录进程使用中央处理器 (CPU：Central Processing Unit)的时间，包括：用户时间，系统时间， 用户各子进程合计时间，系统各子进程合计时间)
6.资源使用(resource utilizations)设定为0
8.阻塞信号集初始化为空集(译者注：原文此处不明确，译文根据fork函数手册页稍做修改)
9.不继承由timer_create函数创建的计时器
10.不继承异步输入和输出

