cmake_minimum_required(VERSION 3.3)
project(hw3)
link_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Werror -pedantic-errors -D NDEBUG")

set(LIBMTM libmtm.a)

set(POKEDEX_FILES utilities.c pokedex.c pokedex_test.c utilities.h aux_macros.h set.h)
add_executable(hw3_pokedex_test ${POKEDEX_FILES})
target_link_libraries(hw3_pokedex_test ${LIBMTM})


#set(POKEMON_FILES pokemon.c pokemon.h pokemon_test.c store.c store.h)
#add_executable(hw3_pokemon_test ${POKEMON_FILES})
#target_link_libraries(hw3_pokemon_test ${LIBMTM})


