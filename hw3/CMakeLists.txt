cmake_minimum_required(VERSION 3.4)
project(hw3)
link_directories(.)
add_subdirectory(dry_part)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Werror -pedantic-errors -D NDEBUG")
