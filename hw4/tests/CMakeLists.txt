cmake_minimum_required(VERSION 3.3)
project(hw4)
link_directories(.)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(POKEMON_FILES pokemon_test.cpp test_utils.cc ../pokemon.cpp )
add_executable(hw4_pokemon_test ${POKEMON_FILES})

set(TRAINER_FILES trainer_test.cpp test_utils.cc ../trainer.cpp ../pokemon.cpp )
add_executable(hw4_trainer_test ${TRAINER_FILES})

set(K_GRAPH_FILES k_graph_mtm_test.cpp test_utils.cc ../k_graph_mtm.cpp )
add_executable(hw4_pokemon_test ${K_GRAPH_FILES})