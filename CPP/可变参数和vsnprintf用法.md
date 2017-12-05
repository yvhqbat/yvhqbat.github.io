
## 1. 可变参数

参考:  
http://blog.csdn.net/yvhqbat/article/details/51339505


## 2. vsnprintf函数
### 2.1 vsnprintf
参考:  
http://www.cplusplus.com/reference/cstdio/vsnprintf/

```
#include <cstdio>

int vsnprintf (char * s, size_t n, const char * format, va_list arg );

Write formatted data from variable argument list to sized buffer.
```

Composes a string with the same text that would be printed if format was used on printf, but using the elements in the variable argument list identified by arg instead of additional function arguments and storing the resulting content as a C string in the buffer pointed by s (taking n as the maximum buffer capacity to fill).

If the resulting string would be longer than n-1 characters, the remaining characters are discarded and not stored, but counted for the value returned by the function.

Internally, the function retrieves arguments from the list identified by arg as if va_arg was used on it, and thus the state of arg is likely to be altered by the call.

In any case, arg should have been initialized by va_start at some point before the call, and it is expected to be released by va_end at some point after the call.

Parameters

s  
Pointer to a buffer where the resulting C-string is stored.
The buffer should have a size of at least n characters.

n  
Maximum number of bytes to be used in the buffer.  
The generated string has a length of at most n-1, leaving space for the additional terminating null character.  
size_t is an unsigned integral type.  

format  
C string that contains a format string that follows the same specifications as format in printf (see printf for details).  

arg  
A value identifying a variable arguments list initialized with va_start.
va_list is a special type defined in <cstdarg>.

Return Value  
The number of characters that would have been written if n had been sufficiently large, not counting the terminating null character.
If an encoding error occurs, a negative number is returned.
Notice that only when this returned value is non-negative and less than n, the string has been completely written.


### 2.2 示例
```
#include <cstdio>

void print_log(const char* fmt,...)
{
    char buffer[256];
    va_list args;
    va_start (args, fmt);
    vsnprintf (buffer,256,fmt, args);
    va_end (args);
    printf("%s",buffer);
}

// 测试
int main(int argc, const char* argv[]) {
    cout<<"hello world";
    print_log("my name is %s, my age is %d\n","liudong",25);
```
