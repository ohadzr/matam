cmake_minimum_required(VERSION 3.3)
project(hw3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(SOURCE_FILES list.h map.h print_utils.h set.h)

add_executable(hw3 ${SOURCE_FILES})
