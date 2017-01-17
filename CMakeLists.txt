cmake_minimum_required(VERSION 3.4)
project(matam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set (CMAKE_C_STANDARD 99)

add_subdirectory(hw2)
add_subdirectory(hw4)

set(BAR_FILES ex3_bar.c)
add_executable(bar_test ${BAR_FILES})