cmake_minimum_required(VERSION 3.20)
project(graphics)

set(CMAKE_CXX_STANDARD 14)
set(HEADER_COMMENTS false)

add_executable(main
        src/main.cpp
        src/listener.h src/render.h)

target_compile_options(main PRIVATE -Wall)

add_subdirectory(extern)
