cmake_minimum_required(VERSION 3.13)
project(test-v11)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_singleton test_singleton.cpp)
add_executable(test_observer test_observer.cpp)

#设置安装目录
INSTALL(TARGETS test_singleton
        RUNTIME DESTINATION tests/v11/bin)
INSTALL(TARGETS test_observer
        RUNTIME DESTINATION tests/v11/bin)
