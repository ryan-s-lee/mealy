cmake_minimum_required(VERSION 3.23)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mealy)

add_executable(
    test
    test/main.cpp)

target_include_directories(
    test
    PRIVATE inc/)
