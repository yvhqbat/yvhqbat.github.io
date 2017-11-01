# 编译静态链接库libhello.a
#add_library(hello hello.cpp)

# 编译可执行文件和设置链接库（注意顺序）
#add_executable(main main.cpp)
#target_link_libraries(main hello)

# CThreadPool
add_library(threadpool ThreadPool.cpp)

# tcpsever  tcpclient
add_library(tcpserver TcpServer.cpp)
add_library(tcpclient TcpClient.cpp)
