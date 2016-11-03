cmake_minimum_required(VERSION 3.3)
project(matam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set (CMAKE_C_STANDARD 99)

set(SOURCE_FILES hello_world.c)

add_subdirectory(hw0/part1)
add_subdirectory(hw0/part2)

add_executable(matam ${SOURCE_FILES})
