cmake_minimum_required(VERSION 3.20)
project(graphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(main
        src/main.cpp
        src/listener.h
        src/buffer.cpp src/buffer.h
        src/shader.cpp src/shader.h)

target_compile_options(main PRIVATE -Wall)

add_subdirectory(extern)
