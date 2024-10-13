cmake_minimum_required(VERSION 3.22.1)
project(slang_cpp)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-pedantic HAS_PEDANTIC)
if(HAS_PEDANTIC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif ()

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(slang_cpp SHARED
        include/register_slang.h
        include/slang_cpp.h
        include/slang_enums.h
        src/register_slang.cpp
        src/slang_cpp.cpp
)
#target_link_libraries(slang_cpp ${PROJECT_SOURCE_DIR}/lib/libgodot-cpp.linux.template_debug.x86_64.a)

file(GLOB LIBS "/home/littlewhite/Projects/Clones/slang-release/lib/*")
file(GLOB LIBS2 "/home/littlewhite/Projects/Clones/slang/source/**/*.cpp")
#file(GLOB LIBS3 "/home/littlewhite/Projects/Clones/slang/source/core/unix/*")

target_link_libraries(slang_cpp ${LIBS} # ${LIBS2} # ${LIBS3}
        #/home/littlewhite/Projects/Clones/slang/source/core/libslang_string-escape-util.so
        /home/littlewhite/Projects/Clones/slang/source/core/slang-string-escape-util.cpp
        /home/littlewhite/Projects/Clones/slang/source/core/slang-char-util.cpp
        /home/littlewhite/Projects/Clones/slang/source/core/slang-string.cpp
        /home/littlewhite/Projects/Clones/slang/source/core/slang-char-encode.cpp
        /home/littlewhite/Projects/Clones/godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a
)