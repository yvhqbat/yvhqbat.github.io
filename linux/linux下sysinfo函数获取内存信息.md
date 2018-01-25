
## linux下sysinfo函数获取内存信息

### 1. sysinfo函数

```
NAME
       sysinfo - returns information on overall system statistics

SYNOPSIS
       #include <sys/sysinfo.h>

       int sysinfo(struct sysinfo *info);

DESCRIPTION
       Until Linux 2.3.16, sysinfo() used to return information in the following structure:

           struct sysinfo {
               long uptime;             /* Seconds since boot */
               unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
               unsigned long totalram;  /* Total usable main memory size */
               unsigned long freeram;   /* Available memory size */
               unsigned long sharedram; /* Amount of shared memory */
               unsigned long bufferram; /* Memory used by buffers */
               unsigned long totalswap; /* Total swap space size */
               unsigned long freeswap;  /* swap space still available */
               unsigned short procs;    /* Number of current processes */
               char _f[22];             /* Pads structure to 64 bytes */
           };

       and the sizes were given in bytes.
```

### 2. 实例

```
#include <sys/sysinfo.h>

void
getMemInfo()
{
    struct sysinfo stSysInfo;
    if(0 != sysinfo(&stSysInfo))
    {
        return;
    }
    cout<<"totalram: "<<stSysInfo.totalram/(1024*1024)<<"M"<<endl;
    cout<<"freeram: "<<stSysInfo.freeram/(1024*1024)<<"M"<<endl;
}
```
