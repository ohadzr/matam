cmake_minimum_required(VERSION 3.3)
project(hw0_part1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(SOURCE_FILES part1.c)

add_executable(hw0_part1 ${SOURCE_FILES})
