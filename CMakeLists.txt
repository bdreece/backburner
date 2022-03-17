cmake_minimum_required(VERSION 3.10)

project(backburner VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(tests)
