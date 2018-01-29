
## linux下sigaction函数进行信号处理


### 1. 信号
参考《APUE第十章》
> 信号，是软件中断，提供了一种处理异步事件的方法。

### 2. 三种方式处理信号
1. 忽略此信号，SIGKILL/SIGSTOP除外；
2. 捕捉信号，调用一个信号处理函数，SIGKILL/SIGSTOP除外；
3. 执行系统默认动作，大多数默认动作是终止该进程。

### 3. 常用信号
信号|说明
--|--
SIGUSR1|用户定义信号，可用于应用程序
SIGUSR2|同SIGUSR1

### 4. 函数sigaction
APUE推荐，最好使用sigaction代替signal函数，故，主要学习了sigaction函数。

信号屏蔽字：每个进程都有一个信号屏蔽字，它规定了当前要阻塞递送到该进程的信号集。
进程可调用`sigprocmask()`函数来检测和更改其当前信号屏蔽字。

```
NAME
       sigaction - examine and change a signal action

SYNOPSIS
       #include <signal.h>

       int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);

DESCRIPTION
       The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.  (See signal(7) for an overview of signals.)

       signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP.

       If act is non-NULL, the new action for signal signum is installed from act.  If oldact is non-NULL, the previous action is saved in oldact.

       The sigaction structure is defined as something like:

           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };

RETURN VALUE
       sigaction() returns 0 on success; on error, -1 is returned, and errno is set to indicate the error.
```

可参考[sigaction 用法实例](https://www.cnblogs.com/lidabo/p/4581202.html)

### 4. 实例
```
#include <iostream>
#include <thread>
using namespace std;

#include <signal.h>    // sigaction()
#include <unistd.h>    // sleep(1)

void sig_handler(int signo)
{
	cout<<"receved signal: "<<signo<<endl;
	for(int i=0;i<5;++i){
		cout<<i<<endl;
		sleep(1);
	}
}

int
main(int argc, char** argv)
{
	struct sigaction act;
	act.sa_handler=sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	if(sigaction(SIGUSR1, &act, NULL)<0){
		cout<<"error in sigaction"<<endl;
		return -1;
	}

	int cnt=0;
	while(1)
	{
		cout<<"while cnt = "<<cnt<<endl;
		if(++cnt==3){
			raise(SIGUSR1);
		}
		sleep(1);
	}
	return 0;
}

```
