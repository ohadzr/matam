cmake_minimum_required(VERSION 3.3)
project(hw4)
link_directories(.)
include_directories(.)



#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -D NDEBUG -L. -Lmtm")


#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
#include(FindPkgConfig)
#find_package(libmtm REQUIRED)
#include_directories(${LIBMTM_INCLUDE_DIR})


set(POKEMON_FILES pokemon_test.cc test_utils.cc ../pokemon.cc)
add_executable(hw4_pokemon_test ${POKEMON_FILES})
#target_link_libraries(hw4_pokemon_test libmtm.a)


set(TRAINER_FILES trainer_test.cc test_utils.cc ../trainer.cc ../world.cc ../pokemon.cc ../item.cc)
add_executable(hw4_trainer_test ${TRAINER_FILES})
#target_link_libraries(hw4_trainer_test libmtm.a)

set(K_GRAPH_FILES k_graph_mtm_test.cc test_utils.cc ../k_graph_mtm.h )
add_executable(hw4_k_graph_test ${K_GRAPH_FILES})


set(WORLD_FILES world_test.cc test_utils.cc ../world.cc ../pokemon.cc ../trainer.cc ../item.cc)
add_executable(hw4_world_test ${WORLD_FILES})
#target_link_libraries(hw4_world_test libmtm.a)


set(POKEMON_GO_FILES pokemon_go_test.cc test_utils.cc ../pokemon_go.cc ../world.cc ../pokemon.cc ../trainer.cc ../item.cc)
add_executable(hw4_pokemon_go_test ${POKEMON_GO_FILES})
#target_link_libraries(hw4_pokemon_go_test libmtm.a)

set(ITEM_FILES item_test.cc test_utils.cc ../item.cc)
add_executable(hw4_item_test ${ITEM_FILES})
