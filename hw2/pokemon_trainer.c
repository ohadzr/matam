//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pokemon_trainer.h"


#define SAME_STRINGS 0
#define NO_POKEMONS 0


/********************************
 * Helper Function Declarations *
 ********************************/

// TODO: shouldn't be static? same function in pokemon_trainer.c
/**
* This function allocate new memory for a given pokemon name / move name
* then copy (deep copy) the name into the pokemon / move
*
* @return
*   bool - return true if allocation successed, otherwise false
*/
static bool createName(char* dst_name, char* name);

/**
* This function allocate new memory for a given trainer.
* the allocation is for his name, local pokemons, remote pokemons and
* pokemonCopy function.
*
* @return
*   bool - return true if allocation successed, otherwise false
*/
static bool pokemonTrainerCreateAllocateFields(PokemonTrainer trainer,
                                    char* name, Pokemon initial_pokemon,
                                    int max_num_local, int max_num_remote);



/****************************************
 *    Assistent Pokemon Trainer Funcs   *
 ****************************************/

bool createName(char* dst_name, char* name) {
    dst_name = malloc(sizeof(*name)+1);
    if (dst_name != NULL) {
        strcpy(dst_name, name);
        dst_name[sizeof(*name)] = '\0';
        return true;
    }

    return false;
}


bool pokemonTrainerCreateAllocateFields(PokemonTrainer trainer,
                                        char* name, Pokemon initial_pokemon,
                                        int max_num_local, int max_num_remote) {
    bool allocate_successfully = true;
    trainer->pokemons_local = \
                    malloc(sizeof(*(trainer->pokemons_local))*max_num_local);
    if (trainer->pokemons_local == NULL) {
        free(trainer);
        allocate_successfully = false;
    }
    trainer->pokemons_remote = \
                    malloc(sizeof(*(trainer->pokemons_remote))*max_num_remote);
    if (trainer->pokemons_remote == NULL) {
        free(trainer->pokemons_local);
        free(trainer);
        allocate_successfully = false;
    }
    if (!createName(trainer->name, name)) allocate_successfully = false;
    if (!allocate_successfully) {
        free(trainer->pokemons_remote);
        free(trainer->pokemons_local);
        free(trainer);
        allocate_successfully = false;
    }
    trainer->pokemons_local[0] = pokemonCopy(initial_pokemon);
    if (trainer->pokemons_local[0] == NULL){
        free(trainer->name);
        free(trainer->pokemons_remote);
        free(trainer->pokemons_local);
        free(trainer);
    }
    return allocate_successfully;
}


/********************************
 *    Pokemon Trainer Funcs     *
 ********************************/

PokemonTrainer pokemonTrainerCreate(char* name, Pokemon initial_pokemon,
                                    int max_num_local, int max_num_remote) {
    if (name == NULL || strcmp(name,"") == SAME_STRINGS ||
        initial_pokemon == NULL || max_num_local <= 0 || max_num_remote <= 0)
        return NULL;
    PokemonTrainer trainer = malloc(sizeof(*trainer));
    if (trainer == NULL) return NULL;
    trainer->max_num_of_pokemons_local = max_num_local;
    trainer->max_num_of_pokemons_remote = max_num_remote;
    trainer->num_of_pokemons_local = NO_POKEMONS;
    trainer->num_of_pokemons_remote = NO_POKEMONS;

    bool allocation_successfully = pokemonTrainerCreateAllocateFields(trainer,
                                                name,initial_pokemon,
                                                max_num_local,max_num_remote);
    if (!allocation_successfully) return NULL;

    trainer->num_of_pokemons_local++;

    return trainer;
}