cmake_minimum_required(VERSION 3.3)
project(hw2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(SOURCE_FILES pokemon.h pokemon.c pokemon_test.c)
add_executable(hw2_pokemon_test ${SOURCE_FILES})

set(SOURCE_FILES2 pokemon.h pokemon.c pokemon_trainer_test.c pokemon_trainer.c)
add_executable(hw2_trainer_test ${SOURCE_FILES2})