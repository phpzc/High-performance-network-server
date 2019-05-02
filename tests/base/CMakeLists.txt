cmake_minimum_required(VERSION 3.13)
project(test-base)

set(CMAKE_CXX_STANDARD 17)
set(TESTS_BASE base.cpp )
add_executable(tests-base ${TESTS_BASE})

set(TESTS_SIMPLE simple.cpp)
add_executable(tests-simple ${TESTS_SIMPLE})

set(TESTS_HIGH high.cpp)
add_executable(tests-high ${TESTS_HIGH})

set(TESTS_HIGH_READV_WRITEV hight_readv_writev.cpp)
add_executable(tests_high_readv_writev ${TESTS_HIGH_READV_WRITEV})

#设置安装目录
INSTALL(TARGETS tests-base
        RUNTIME DESTINATION tests/base/bin)
INSTALL(TARGETS tests-simple
        RUNTIME DESTINATION tests/base/bin)
INSTALL(TARGETS tests-high
        RUNTIME DESTINATION tests/base/bin)
INSTALL(TARGETS tests_high_readv_writev
        RUNTIME DESTINATION tests/base/bin)

