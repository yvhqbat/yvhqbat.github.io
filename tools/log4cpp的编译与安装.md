## log4cpp的编译与安装

log4cpp官网:
http://log4cpp.sourceforge.net/
可以下载源码和查看API.

总结：
编译安装过程，归结起来其实只需要依次输入四个命令：
```
[root@localhost log4cpp-1.0]#./configure
[root@localhost log4cpp-1.0]#make
[root@localhost log4cpp-1.0]#make check
[root@localhost log4cpp-1.0]#make install
```

安装完毕后，会在 `/usr/local/`里的include和lib文件夹里面看到了log4cpp的头文件和库文件。

## log4cpp 的简单使用
```
// main.cpp

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

int main(int argc, char** argv) {
	log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
	appender1->setLayout(new log4cpp::BasicLayout());

	log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
	appender2->setLayout(new log4cpp::BasicLayout());

	log4cpp::Category& root = log4cpp::Category::getRoot();
	root.setPriority(log4cpp::Priority::WARN);
	root.addAppender(appender1);
    root.addAppender(appender2);

    //printf-style
    root.error("this is an error %d.",3);
    //use of streams for logging messages
    root<<log4cpp::Priority::ERROR<<"THIS IS AN ERROR "<<3;

    /*
	log4cpp::Category& sub1 = og4cpp::Category::getInstance(std::string("sub1"));
	sub1.addAppender(appender2);

	// use of functions for logging messages
	root.error("root error");
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";
    */

	return 0;
}

```

编译时需要链接静态库或动态库, 以静态库为例
```
add_executable(log4cpp_test log4cpp_test.cpp)
target_link_libraries(log4cpp_test liblog4cpp.a)
```
