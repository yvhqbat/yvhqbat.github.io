add_executable(ThreadPoolTest ThreadPoolTest.cpp)
target_link_libraries(ThreadPoolTest threadpool)

add_executable(ThreadSpecificDataTest ThreadSpecificDataTest.cpp)

add_executable(server server.cpp)
target_link_libraries(server tcpserver)

add_executable(client client.cpp)
target_link_libraries(client tcpclient)

add_executable(json_test json_test.cpp)
target_link_libraries(json_test libjsoncpp.so)
