CC = gcc
LIBS = -L. -lmtm
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror

TEST_FOLDER = tests
MAP_FOLDER = map_mtm


OBJ_STORE = store.o
OBJ_POKEMON = utilities.o pokemon.o pokedex.o store.o
OBJ_TRAINER = utilities.o trainer.o pokedex.o store.o location.o pokemon.o
OBJ_POKEDEX = utilities.o pokedex.o
OBJ_LOCATION = utilities.o location.o pokedex.o pokemon.o store.o
OBJ_POKEMON_GO = pokemon_go.o location.o pokedex.o trainer.o pokemon.o store.o utilities.o
OBJ_TEST = ${TEST_FOLDER}/store_test.o ${TEST_FOLDER}/pokemon_test.o \
		   ${TEST_FOLDER}/trainer_test.o  ${TEST_FOLDER}/pokedex_test.o\
		   ${TEST_FOLDER}/location_test.o


#################### main

all : pokemon_go tests
	make pokemon_go
	make tests

pokemon_go : ${OBJ_POKEMON_GO}
	${CC} ${CFLAGS} ${OBJ_POKEMON_GO} ${LIBS} -o $@

tests : ${OBJ_TEST}
	${CC} ${CFLAGS} ${TEST_FOLDER}/store_test.o ${OBJ_STORE} \
	${LIBS} -o store_test
	${CC} ${CFLAGS} ${TEST_FOLDER}/pokemon_test.o ${OBJ_POKEMON} \
	${LIBS} -o pokemon_test
	${CC} ${CFLAGS} ${TEST_FOLDER}/trainer_test.o ${OBJ_TRAINER} \
	${LIBS} -o trainer_test
	${CC} ${CFLAGS} ${TEST_FOLDER}/pokedex_test.o ${OBJ_POKEDEX} \
    ${LIBS} -o pokedex_test
	${CC} ${CFLAGS} ${TEST_FOLDER}/location_test.o ${OBJ_LOCATION} \
	${LIBS} -o location_test


#################### pokemon Go adts code

utilities.o : utilities.h utilities.c
	${CC} ${CFLAGS} -c utilities.c -o $@

store.o : store.c store.h list.h print_utils.h
	${CC} ${CFLAGS} -c store.c -o $@

pokemon.o : pokemon.c pokemon.h store.h list.h set.h utilities.h pokedex.h
	${CC} ${CFLAGS} -c pokemon.c -o $@

trainer.o : pokemon_trainer.c pokemon_trainer.h pokemon.h store.h \
             list.h set.h utilities.h pokedex.h print_utils.h location.h
	${CC} ${CFLAGS} -c pokemon_trainer.c -o $@

pokedex.o : pokedex.c pokemon_trainer.h pokemon.h store.h \
             list.h set.h utilities.h pokedex.h print_utils.h location.h
	${CC} ${CFLAGS} -c pokedex.c -o $@

location.o : location.c location.h set.h list.h print_utils.h pokemon.h \
              store.h utilities.h pokedex.h
	${CC} ${CFLAGS} -c location.c -o $@

pokemon_go.o : pokemon_go.c pokedex.h set.h utilities.h pokemon_trainer.h \
                pokemon.h store.h list.h print_utils.h location.h
	${CC} ${CFLAGS} -c pokemon_go.c -o $@


#################### pokemonGo + map_mtm tests

${TEST_FOLDER}/store_test.o : ${TEST_FOLDER}/store_test.c store.h list.h \
                              ${TEST_FOLDER}/test_utilities.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/store_test.c -o $@

${TEST_FOLDER}/pokemon_test.o : ${TEST_FOLDER}/pokemon_test.c pokedex.h \
                                ${TEST_FOLDER}/test_utilities.h \
                                pokemon.h store.h list.h set.h utilities.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/pokemon_test.c -o $@

${TEST_FOLDER}/trainer_test.o : ${TEST_FOLDER}/pokemon_trainer_test.c pokemon.h \
								store.h list.h print_utils.h location.h \
							    ${TEST_FOLDER}/test_utilities.h \
                                set.h utilities.h pokedex.h pokemon_trainer.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/pokemon_trainer_test.c -o $@

${TEST_FOLDER}/pokedex_test.o : ${TEST_FOLDER}/pokedex_test.c pokedex.h \
                                ${TEST_FOLDER}/test_utilities.h  set.h \
                                utilities.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/pokedex_test.c -o $@

${TEST_FOLDER}/location_test.o : ${TEST_FOLDER}/location_test.c location.h \
                                 set.h list.h print_utils.h pokemon.h  \
                                 utilities.h pokedex.h store.h \
                                 ${TEST_FOLDER}/test_utilities.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/location_test.c -o $@


#################### mtm_map


#################### Misc commands	
.PHONY: clean
clean:
	rm -f *.o ${TEST_FOLDER}/*.o ${MAP_FOLDER}/*.o  \
    store_test pokemon_test trainer_test pokedex_test location_test \
    pokemon_go_test map_test