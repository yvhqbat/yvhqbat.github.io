## 记录锁

参考：
- 《APUE》
- [ Linux进程同步之记录锁（fcntl）](https://blog.csdn.net/anonymalias/article/details/9197641)

记录锁（record locking）:当第一个**进程**正在读或写文件的某个部分时，使用记录锁可以阻止其他进程修改同一文件区。
一个更合适的术语是**字节范围锁**（byte-range locking）,因为它锁定的只是文件中的一个区域（也可能是整个文件）。

```
#include <fcntl.h>

int fcntl(int fd, int cmd, .../*struct flock *flockptr */);
```

### 实例
```
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
using namespace std;

void demo()
{
	struct flock lock;
	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=10;
	lock.l_pid=getpid();

	int fd=open("test.txt",O_RDWR|O_CREAT);
	if(fd<0){
		cout<<"open file failed"<<endl;
		return;
	}

	if(fcntl(fd,F_SETLK,&lock)<0){
		cout<<"fcntl error"<<endl;
		return;
	}
	// do something

	lock.l_type=F_UNLCK;
	if(fcntl(fd,F_SETLK,&lock)<0){
		cout<<"fcntl unlock failed"<<endl;
		return;
	}

	cout<<"pid is "<<lock.l_pid<<endl;
}


int main()
{
	demo();
	return 0;
}
```
