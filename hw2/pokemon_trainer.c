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
#define MIN_POKEMON_INDEX 1
#define LAST_POKEMON 1


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
    trainer->pokemons_local = \
                    malloc(sizeof(*(trainer->pokemons_local))*max_num_local);
    if (trainer->pokemons_local == NULL) {
        free(trainer);
        return false;
    }
    trainer->pokemons_remote = \
                    malloc(sizeof(*(trainer->pokemons_remote))*max_num_remote);
    if (trainer->pokemons_remote == NULL) {
        free(trainer->pokemons_local);
        free(trainer);
        return false;
    }
    bool allocate_successfully = createName(trainer->name, name);
    if (!allocate_successfully) {
        free(trainer->pokemons_remote);
        free(trainer->pokemons_local);
        free(trainer);
        return false;
    }
    trainer->pokemons_local[0] = pokemonCopy(initial_pokemon);
    if (trainer->pokemons_local[0] == NULL){
        free(trainer->name);
        free(trainer->pokemons_remote);
        free(trainer->pokemons_local);
        free(trainer);
        return false;
    }
    return true;
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


void pokemonTrainerDestroy(PokemonTrainer trainer) {
    if (trainer != NULL) {
        free(trainer->name);

        for (int i = trainer->num_of_pokemons_local-1; i >= 0 ; i--) {
            pokemonDestroy(trainer->pokemons_local[i]);
        }
        // duplication - but creating a function for 3 lines is redundant TODO:should I create a function?
        for (int j = trainer->num_of_pokemons_remote-1; j >= 0 ; j--) {
            pokemonDestroy(trainer->pokemons_remote[j]);
        }
        free(trainer->pokemons_local); //TODO: ask if this correct
        free(trainer->pokemons_remote);
        free(trainer);
    }
}


PokemonTrainer pokemonTrainerCopy(PokemonTrainer trainer) {
    if (trainer == NULL) return NULL;
    PokemonTrainer new_trainer = pokemonTrainerCreate(trainer->name,
                trainer->pokemons_local[0],trainer->max_num_of_pokemons_local,
                                         trainer->max_num_of_pokemons_remote);
    if (new_trainer == NULL) return NULL;

    for (int i=1; i<trainer->num_of_pokemons_local; i++) {
        if (pokemonTrainerAddPokemon(new_trainer, trainer->pokemons_local[i]) \
                                     != POKEMON_TRAINER_SUCCESS) {
            pokemonTrainerDestroy(new_trainer);
            return NULL;
        }
        new_trainer->num_of_pokemons_local++;
    }
    // TODO: should duplicated code should move to another function? how?
    for (int j=1; j<trainer->num_of_pokemons_remote; j++) {
        if (pokemonTrainerAddPokemon(new_trainer, trainer->pokemons_remote[j]) \
                                     != POKEMON_TRAINER_SUCCESS) {
            pokemonTrainerDestroy(new_trainer);
            return NULL;
        }
        new_trainer->num_of_pokemons_remote++;
    }
    return new_trainer;
}

PokemonTrainerResult pokemonTrainerAddPokemon(PokemonTrainer trainer,
                                              Pokemon pokemon) {
    if (trainer == NULL || pokemon == NULL) return POKEMON_TRAINER_NULL_ARG;
    if (trainer->num_of_pokemons_local == trainer->max_num_of_pokemons_local)
        return POKEMON_TRAINER_PARTY_FULL;

    trainer->pokemons_local[trainer->num_of_pokemons_local] = \
            pokemonCopy(pokemon);
    if (trainer->pokemons_local[trainer->num_of_pokemons_local] == NULL)
        return POKEMON_TRAINER_OUT_OF_MEM;

    trainer->pokemons_local++;

    return POKEMON_TRAINER_SUCCESS;
}

Pokemon pokemonTrainerGetPokemon(PokemonTrainer trainer, int pokemon_index) {
    if (trainer == NULL || pokemon_index < MIN_POKEMON_INDEX || \
        pokemon_index > trainer->num_of_pokemons_local) {
        return NULL;
    }

    return trainer->pokemons_local[pokemon_index-1];
}


PokemonTrainerResult pokemonTrainerRemovePokemon(
        PokemonTrainer trainer, int pokemon_index) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;
    if (pokemon_index < MIN_POKEMON_INDEX || \
    pokemon_index > trainer->num_of_pokemons_local) {
        return POKEMON_TRAINER_INVALID_INDEX;
    }
    if (trainer->num_of_pokemons_local == LAST_POKEMON)
        return POKEMON_TRAINER_REMOVE_LAST;

    Pokemon pokemon = pokemonTrainerGetPokemon(trainer, pokemon_index);
    if (pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEM;

    pokemonDestroy(pokemon);

    // fix pokemons indexes
    int i=pokemon_index-1;
    for ( ; i < trainer->num_of_pokemons_local-1; i++){
        trainer->pokemons_local[i] = trainer->pokemons_local[i+1];
    }
    //pokemon->moves[i] = NULL; // remove duplicate pointer NOT freeing move TODO:should I remove duplicated pointer?
    trainer->num_of_pokemons_local--;

    return POKEMON_TRAINER_SUCCESS;
}