cmake_minimum_required(VERSION 3.3)
project(hw0_part2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(SOURCE_FILES dry_part2)

add_executable(hw2 ${SOURCE_FILES})
