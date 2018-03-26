
## vsprintf_s函数和va_list多参数的使用

```
#include <cstdio>
#include <cstdarg>
#include <iostream>
using namespace std;

void print_s(char* buf,size_t bufsize, char *fmt, ...){
    va_list args;
    va_start(args,fmt);
    vsprintf_s(buf, bufsize, fmt, args);
    va_end(args);
}

int main()
{
    char buf[1024];
    print_s(buf, 1024, "hello %s\n", "liudong");
    cout << buf << endl;
    return 0;
}
```
