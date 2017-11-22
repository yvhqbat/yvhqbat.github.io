
# dlopen, dlsym, dlclose 加载动态链接库

参考:
[采用dlopen、dlsym、dlclose加载动态链接库【总结】](http://www.cnblogs.com/Anker/p/3746802.html)

## 1. 插件

插件(Plug-in 又译外挂)是一种遵循一定规范的应用程序接口编写出来的程序。

应用软件提供使插件能够应用的各项服务，其中包括提供加载方式，使插件可以加载到应用程序和网络传输协议中，从而和插件进行数据交换。

插件必须依赖于应用程序才能发挥自身功能，仅靠插件是无法正常运行的。相反地，应用程序并不需要依赖插件就可以运行，这样一来，插件就可以**加载到应用程序上并且动态更新**而不会对应用程序造成任何改变。

公开应用程序接口提供一个标准的界面，允许其他人编写插件和应用程序互动。

## 2. dlopen, dlsym, dlclose 的使用

linux提供了加载和处理动态链接库的系统调用，非常方便。  
即: `dlopen`, `dlsym`, `dlclose`


### 2.1 生成动态链接库
```
gcc -shared -o libcal.so cal.c
```

cal.c文件
```
int add(int a, int b)
{
   return (a+b);
}
```

### 2.2 加载动态链接库

```
gcc -rdynamic -o cal_use cal_use.c -ldl
```

cal.use.c 文件
```
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*FUNC)(int,int);


int main(int argc, char **argv)
{
   void *handle;
   //int (*add)(int, int);
   FUNC add;
   char *error;

  handle = dlopen("./libcal.so", RTLD_LAZY);
   if (!handle) {
       fprintf(stderr, "%s\n", dlerror());
       exit(EXIT_FAILURE);
   }

  dlerror();    /* Clear any existing error */

  /* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
  *  would seem more natural, but the C99 standard leaves
  *  casting from "void *" to a function pointer undefined.
  *  The assignment used below is the POSIX.1-2003 (Technical
  *  Corrigendum 1) workaround; see the Rationale for the
  *  POSIX specification of dlsym().
  */

  //*(void **) (&add) = dlsym(handle, "add");
  add=(FUNC)dlsym(handle,"add");
  if ((error = dlerror()) != NULL)  {
       fprintf(stderr, "%s\n", error);
       exit(EXIT_FAILURE);
   }

  printf("%d\n", (*add)(2,3));
   dlclose(handle);
   exit(EXIT_SUCCESS);
}
```

### 2.3 问题

使用gcc编译可以, 但改为g++则运行时出错.  
`./libcal.so: undefined symbol: add`  
应该是c++与c相互调用的问题, 需要设置.

只需要在编译动态库的cal.c文件中加入 `extern "C"`即可.

### 2.4 小技巧
`dlsym`找到全局结构体API_STRUCT后，可以直接用这个全局结构体指针来使用库里面的函数.
因为我们有时候提供的库不仅仅是一个两个函数的，一般的一个库都会存在多个函数，用这种方式就可以直接使用, 不然找函数名称的话要写很多次dlsym.
