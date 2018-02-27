## do/while{0}
参考：
[do/while(0)的妙用](http://www.cnblogs.com/wanghetao/archive/2011/11/02/2233545.html)

通常，如果在一个函数中开始要分配一些资源，然后在中途执行过程中如果遇到错误则退出函数，当然，退出前先释放资源. 使用do/while{0}可以提高代码的健壮性。
