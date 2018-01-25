
### 1. statfs函数

可用于查询一个路径的总空间大小和可用空间大小。

```
NAME
       statfs, fstatfs - get file system statistics

SYNOPSIS
       #include <sys/vfs.h>    /* or <sys/statfs.h> */

       int statfs(const char *path, struct statfs *buf);
       int fstatfs(int fd, struct statfs *buf);

DESCRIPTION
       The function statfs() returns information about a mounted file system.  path is the pathname of any file within the mounted file system.  buf is a pointer to a statfs structure
       defined approximately as follows:

           #if __WORDSIZE == 32          /* System word size */
           # define __SWORD_TYPE           int
           #else /* __WORDSIZE == 64 */
           # define __SWORD_TYPE         long int
           #endif

           struct statfs {
               __SWORD_TYPE f_type;    /* type of file system (see below) */
               __SWORD_TYPE f_bsize;   /* optimal transfer block size */
               fsblkcnt_t   f_blocks;  /* total data blocks in file system */
               fsblkcnt_t   f_bfree;   /* free blocks in fs */
               fsblkcnt_t   f_bavail;  /* free blocks available to
                                          unprivileged user */
               fsfilcnt_t   f_files;   /* total file nodes in file system */
               fsfilcnt_t   f_ffree;   /* free file nodes in fs */
               fsid_t       f_fsid;    /* file system id */
               __SWORD_TYPE f_namelen; /* maximum length of filenames */
               __SWORD_TYPE f_frsize;  /* fragment size (since Linux 2.6) */
               __SWORD_TYPE f_spare[5];
           };

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```
### 2. 实例

```
#include <sys/vfs.h>

void
statfs_demo()
{
    struct statfs stStatFs;
    if(0 == statfs("./", &stStatFs))
    {
        cout<<stStatFs.f_blocks<<endl;
        cout<<stStatFs.f_bfree<<endl;
    }
}
```
