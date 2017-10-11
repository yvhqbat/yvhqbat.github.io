## time_t
> 时间函数的使用.

```
#include <time.h>

long long usec(void) 
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
}

#ifdef USEC_TEST_MAIN
int main()
{
    long long start;
    start = usec();
    for (i = 0; i < num; i++)
    {
        //do something.
    }
    printf("use time is %lld usec\n",usec()-start);
}
#endif
```
