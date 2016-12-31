CC = gcc
LIBS = -L. -lmtm
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror

TEST_FOLDER = tests
MAP_FOLDER = map_mtm

##### TODO: remove comment below
#OBJ_MAP = ${MAP_FOLDER}/map_mtm.o
OBJ_STORE = store.o
OBJ_POKEMON = utilities.o pokemon.o
OBJ_TRAINER = utilities.o trainer.o
OBJ_POKEDEX = utilities.o pokedex.o
OBJ_LOCATION = utilities.o location.o
OBJ_POKEMON_GO = pokemon_go.o
OBJ_TEST = ${TEST_FOLDER}/store_test.o ${TEST_FOLDER}/pokemon_test.o \
		   ${TEST_FOLDER}/trainer_test.o  ${TEST_FOLDER}/pokedex_test.o\
		   ${TEST_FOLDER}/location_test.o ${TEST_FOLDER}/pokemon_go_test.o
####    TODO: delete this ^ (one line) add below instead
#		   ${TEST_FOLDER}/location_test.o ${TEST_FOLDER}/pokemon_go_test.o \
#		   ${TEST_FOLDER}/map_test.o

#################### main

all : pokemon_go tests
	make pokemon_go
	make tests

pokemon_go : ${OBJ_POKEMON_GO}
	${CC} ${CFLAGS} ${OBJ_POKEMON_GO} ${LIBS} -o $@

#### TODO: replace later
#####tests : ${OBJ_TEST} ${OBJ_MAP}
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
	#### TODO: add later
	#${CC} ${CFLAGS} ${TEST_FOLDER}/pokemon_go_test.o ${OBJ_POKEMON_GO} \
	#        ${LIBS} -o pokemon_go_test
	#${CC} ${CFLAGS} ${TEST_FOLDER}/map_test.o ${OBJ_MAP} \
	#        ${LIBS} -o map_test

#################### pokemon Go adts code

utilities.o : utilities.h
	${CC} ${CFLAGS} -c utilities.c -o $@

store.o : store.h list.h print_utils.h
	${CC} ${CFLAGS} -c store.c -o $@

pokemon.o : pokemon.h store.h list.h set.h utilities.h pokedex.h
	${CC} ${CFLAGS} -c pokemon.c -o $@

trainer.o : pokemon_trainer.h pokemon.h store.h \
             list.h set.h utilities.h pokedex.h print_utils.h location.h
	${CC} ${CFLAGS} -c pokemon_trainer.c -o $@

pokedex.o : pokemon_trainer.h pokemon.h store.h \
             list.h set.h utilities.h pokedex.h print_utils.h location.h
	${CC} ${CFLAGS} -c pokemon_trainer.c -o $@

location.o : location.h set.h list.h print_utils.h pokemon.h \
              store.h utilities.h pokedex.h
	${CC} ${CFLAGS} -c location.c -o $@

pokemon_go.o : pokedex.h set.h utilities.h pokemon_trainer.h \
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

${TEST_FOLDER}/trainer_test.o : ${TEST_FOLDER}/pokemon_trainer_test.c pokemon.h
                                store.h list.h print_utils.h location.h \
							    ${TEST_FOLDER}/test_utilities.h \
                                set.h utilities.h pokedex.h pokemon_trainer.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/trainer_test.c -o $@

${TEST_FOLDER}/pokedex_test.o : ${TEST_FOLDER}/pokedex_test.c pokedex.h \
                                ${TEST_FOLDER}/test_utilities.h  set.h \
                                utilities.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/pokedex_test.c -o $@

${TEST_FOLDER}/location_test.o : ${TEST_FOLDER}/location_test.c location.h \
                                 set.h list.h print_utils.h pokemon.h  \
                                 utilities.h pokedex.h store.h \
                                 ${TEST_FOLDER}/test_utilities.h
	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/location_test.c -o $@

###TODO: add pokemon_go_test
#${TEST_FOLDER}/pokemon_go_test.o : ${TEST_FOLDER}/yad3service_test.c \
#								   yad3service.h customer.h  realtor.h \
#								   ${TEST_FOLDER}/test_utilities.h
#	${CC} ${CFLAGS} -I. -c ${TEST_FOLDER}/pokemon_go_test.c -o $@

###TODO: add map test
#${TEST_FOLDER}/map_test.o : ${TEST_FOLDER}/map_test.c \
#							${MAP_FOLDER}/map_mtm.h  \
#							${TEST_FOLDER}/test_utilities.h
#	${CC} ${CFLAGS} -Imap_mtm -c ${TEST_FOLDER}/map_test.c -o $@


#################### mtm_map

#####TODO: edit this before finish
#${MAP_FOLDER}/map_mtm.o : ${MAP_FOLDER}/map_mtm.c ${MAP_FOLDER}/map_mtm.h
#	${CC} ${CFLAGS} -c ${MAP_FOLDER}/map_mtm.c -o $@

#################### Misc commands	
.PHONY: clean
clean:
	rm -f *.o ${TEST_FOLDER}/*.o ${MAP_FOLDER}/*.o  \
    store_test pokemon_test trainer_test pokedex_test location_test \
    pokemon_go_test map_test