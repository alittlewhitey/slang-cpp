cmake_minimum_required(VERSION 3.22.1)
project(slang_cpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(slang_cpp SHARED
        include/register_slang.h
        include/slang_cpp.h
        src/register_slang.cpp
        src/slang_cpp.cpp)
