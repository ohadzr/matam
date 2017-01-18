cmake_minimum_required(VERSION 3.3)
project(hw4)
link_directories(.)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG")

set(POKEMON_FILES pokemon_test.cpp test_utils.cc ../pokemon.cpp )
add_executable(hw4_pokemon_test ${POKEMON_FILES})
target_link_libraries(hw4_pokemon_test ../libmtm.a)


set(TRAINER_FILES trainer_test.cpp test_utils.cc ../trainer.cpp ../pokemon.cpp )
add_executable(hw4_trainer_test ${TRAINER_FILES})

set(K_GRAPH_FILES k_graph_mtm_test.cpp test_utils.cc ../k_graph_mtm.h )
add_executable(hw4_k_graph_test ${K_GRAPH_FILES})


set(LOCATION_FILES location_test.cpp test_utils.cc )
add_executable(hw4_location_test ${LOCATION_FILES})


set(WORLD_FILES world_test.cpp test_utils.cc ../world.cpp )
add_executable(hw4_world_test ${WORLD_FILES})


set(POKEMON_GO_FILES pokemon_go_test.cpp test_utils.cc ../pokemon_go.cpp )
add_executable(hw4_pokemon_go_test ${POKEMON_GO_FILES})