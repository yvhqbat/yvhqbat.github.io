
# C和C++之间库的互相调用

参考: [C和C++之间库的互相调用](http://www.cppblog.com/wolf/articles/77828.html)

## 1. `extern "C"` 的作用

参考: [C++项目中的extern "C" {}](https://www.cnblogs.com/skynet/archive/2010/07/10/1774964.html)

C++项目代码中, 经常会看到下面这样的代码:
```
#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif
```

### 1.1 条件编译

```
#ifdef __cplusplus

/*...*/

#endif
```

因为**C语言中不支持`extern "C"`声明**，如果你明白`extern "C"`的作用就知道在C中也没有必要这样做，这就是条件编译的作用！  
在`*.c`文件中包含了extern "C"时会出现编译时错误。

条件编译，一个重要应用——避免重复包含头文件。

### 1.2
