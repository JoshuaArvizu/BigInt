cmake_minimum_required(VERSION 3.23)
project(PA5)

set(CMAKE_CXX_STANDARD 14)

add_executable(test test.cpp bigint.h bigint.cpp)
add_executable(constructor_test constructor_test.cpp bigint.h bigint.cpp)
add_executable(mytest mytest.cpp bigint.h bigint.cpp)
add_executable(decipher decipher.cpp bigint.h bigint.cpp)
