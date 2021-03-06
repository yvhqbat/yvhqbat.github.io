
## linux下`/proc/*`目录详解

[参考](http://blog.csdn.net/preterhuman_peak/article/details/40649229)

### `/proc/*`

linux里一切皆为文件，/proc目录是一种内核和内核模块用来向进程（process）发送信息的机制（所以叫做“/proc”），这个伪文件系统允许与内核内部数据结构交互，获取有关进程的有用信息，在运行中（on the fly）改变设置（通过改变内核参数）。与其他文件系统不同，/proc 存在于内存而不是硬盘中。proc 文件系统提供的信息如下：
- 进程信息：系统中的任何一个进程，在 proc 的子目录中都有一个同名的进程 ID，可以找到 cmdline、mem、root、stat、statm，以及 status。某些信息只有超级用户可见，例如进程根目录。每一个单独含有现有进程信息的进程有一些可用的专门链接，系统中的任何一个进程都有一个单独的自链接指向进程信息，其用处就是从进程中获取命令行信息。
- 系统信息：如果需要了解整个系统信息中也可以从/proc/stat 中获得，其中包括 CPU 占用情况、磁盘空间、内存对换、中断等。
- CPU 信息：利用/proc/CPUinfo 文件可以获得中央处理器的当前准确信息。
- 负载信息：/proc/loadavg 文件包含系统负载信息。
- 系统内存信息：/proc/meminfo 文件包含系统内存的详细信息，其中显示物理内存的数量、可用交换空间的数量，以及空闲内存的数量等。

可以通过读取相关文件，编写某些工具软件。

参考：
[/proc/pid下的相应信息说明](http://www.cnblogs.com/GoodGoodWorkDayDayUp/archive/2011/05/27/2059685.html)
