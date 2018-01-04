# boost 库的安装与使用

[boost官网](http://www.boost.org/)

## 1. boost的安装

1. 下载boost源码
2. 安装

```
./bootstrap.sh

// 完整编译(对boost的完整编译, 安装所有的静态库,动态库)
./b2 --buildtype=complete install

```

## 2. boost文档
文档路径
```
boost_1_65_0/doc/html
```

## 3. 使用(以boost::log为例)

test.cpp

```
#include <boost/log/trivial.hpp>

int main(int, char*[])
{
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    return 0;
}
```

编译
```
g++ -g -std=c++11 -Wall -DBOOST_LOG_DYN_LINK -c test.cpp -o test.o


g++ -g -std=c++11 test.o -o test -rdynamic -lpthread -lboost_log -lboost_system -lboost_thread -lboost_filesystem


export LD_LIBRARY_PATH=/usr/local/lib

g++ -g -std=c++11 test.o -o test -rdynamic -lpthread -lboost_log -lboost_system -lboost_thread -lboost_filesystem

./test

```

输出
```
d@ld-pc:~$ ./test
[2017-12-19 23:09:28.851997] [0x00007f291b076780] [trace]   A trace severity message
[2017-12-19 23:09:28.852139] [0x00007f291b076780] [debug]   A debug severity message
[2017-12-19 23:09:28.852169] [0x00007f291b076780] [info]    An informational severity message
[2017-12-19 23:09:28.852193] [0x00007f291b076780] [warning] A warning severity message
[2017-12-19 23:09:28.852215] [0x00007f291b076780] [error]   An error severity message
[2017-12-19 23:09:28.852236] [0x00007f291b076780] [fatal]   A fatal severity message

```
