cmake_minimum_required(VERSION 3.4)
project(hw3)
link_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Werror -pedantic-errors -D NDEBUG")

set(POKEDEX_FILES utilities.c pokedex.c tests/pokedex_test.c)
add_executable(hw3_pokedex_test ${POKEDEX_FILES})
target_link_libraries(hw3_pokedex_test libmtm.a)


