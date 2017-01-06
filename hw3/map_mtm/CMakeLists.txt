cmake_minimum_required(VERSION 3.4)
project(hw3)
link_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Werror -pedantic-errors -D NDEBUG -c")

set(MAP_MTM_FILES map_mtm.c ../tests/map_example_test.c)
add_executable(hw3_map_mtm_test ${MAP_MTM_FILES})

