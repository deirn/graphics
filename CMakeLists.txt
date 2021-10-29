cmake_minimum_required(VERSION 3.20)
project(graphics)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
    src/main.cpp
    src/config.h
    src/listener.h
    src/buffer.cpp src/buffer.h
    src/shader.cpp src/shader.h
    src/paths.cpp src/paths.h)

target_compile_options(main PRIVATE -Wall)

if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    add_custom_command(TARGET main PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/res)

    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)
endif ()

add_subdirectory(extern)
