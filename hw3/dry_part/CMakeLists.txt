cmake_minimum_required(VERSION 3.4)
project(hw3)
link_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Werror -pedantic-errors -D NDEBUG")

set(LIST_OPERATE_FILES listOperate.c)
add_executable(hw3_dry_list_operate ${LIST_OPERATE_FILES})


