cmake_minimum_required(VERSION 3.3)
project(TP_LOGO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(test-logo src/logo.c src/logo.h test/test_logo.c)