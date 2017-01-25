cmake_minimum_required(VERSION 3.3)
project(hw4)
link_directories(.)
include_directories(.)



#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG -L. -Lmtm")


set(DRY_1_FILES dry1.cpp )
add_executable(hw4_dry1 ${DRY_1_FILES})

set(DRY_2_FILES dry2.cpp )
add_executable(hw4_dry2 ${DRY_2_FILES})
