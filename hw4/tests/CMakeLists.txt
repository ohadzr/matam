cmake_minimum_required(VERSION 3.3)
project(hw4)
link_directories(.)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(SOURCE_FILES pokemon_test.cpp test_utils.cc ../pokemon.cpp )
add_executable(hw4_pokemon_test ${SOURCE_FILES})


set(SOURCE_FILES trainer_test.cpp test_utils.cc ../trainer.cpp ../pokemon.cpp )
add_executable(hw4_trainer_test ${SOURCE_FILES})