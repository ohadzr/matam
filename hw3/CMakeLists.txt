cmake_minimum_required(VERSION 3.3)
project(hw3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(LIBMTM libmtm.a)

set(STORE_FILES store.c store.h store_test.c)
add_executable(hw3_store_test ${STORE_FILES})
target_link_libraries(hw3_store_test ${LIBMTM})


set(POKEMON_FILES pokemon.c pokemon.h pokemon_test.c store.c store.h)
add_executable(hw3_pokemon_test ${POKEMON_FILES})
target_link_libraries(hw3_pokemon_test ${LIBMTM})


