

## gethostname函数获取主机名

```
NAME
       gethostname, sethostname - get/set hostname

SYNOPSIS
       #include <unistd.h>

       int gethostname(char *name, size_t len);
       int sethostname(const char *name, size_t len);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       gethostname():
           Since glibc 2.12: _BSD_SOURCE || _XOPEN_SOURCE >= 500
           || /* Since glibc 2.12: */ _POSIX_C_SOURCE >= 200112L
       sethostname():
           _BSD_SOURCE || (_XOPEN_SOURCE && _XOPEN_SOURCE < 500)

DESCRIPTION
       These system calls are used to access or to change the hostname of the current processor.

       sethostname()  sets the hostname to the value given in the character array name.  The len argument specifies the number of bytes in name.  (Thus, name does not require a termi‐
       nating null byte.)

       gethostname() returns the null-terminated hostname in the character array name, which has a length of len bytes.  If the null-terminated hostname is too large to fit, then  the
       name  is  truncated,  and  no  error  is  returned  (but see NOTES below).  POSIX.1-2001 says that if such truncation occurs, then it is unspecified whether the returned buffer
       includes a terminating null byte.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

### 2. 实例

```
#include <iostream>
using namespace std;
#include <unistd.h>

int
main(int argc, char** argv)
{
    char buffer[64]={0};
    gethostname(buffer, 64);
    cout<<buffer<<endl;

    return 0;
}
```

### 3. python
```
import socket
hostname=socket.gethostname()
```
