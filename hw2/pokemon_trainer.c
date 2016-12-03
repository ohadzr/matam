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


/**
* This function fix the new pokemon indexes after removing a pokemon from
* the pokemon array (local or remote). The function doesn't change the number
* of pokemons local or remote, this is the user responsibilty.
*
*/
static void fixPokemonIndexes(PokemonTrainer trainer, int starting_index,
                              bool is_local);


static PokemonTrainerResult pokemonTrainerDepositOrWithdrawPokemon(
        PokemonTrainer trainer, int pokemon_index, bool is_desposit);

static PokemonTrainerResult pokemonTrainerRemovePokemonAux(
        PokemonTrainer trainer, int pokemon_index, bool is_local);


static Pokemon pokemonTrainerGetMostRankedPokemonAux(PokemonTrainer trainer,
        int starting_index, bool start_at_local, int* most_ranked_index,
                                              bool* most_ranked_is_local);

/**
* Move pokemons indexes(!) from proffesor to trainer. The trainer should have
* either max_num_of_pokemons_local number of pokemons or all pokemons he own.
*
*/
static void mergeTrainerAndProfessor(PokemonTrainer trainer);

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

PokemonTrainerResult pokemonTrainerRemovePokemonAux(
        PokemonTrainer trainer, int pokemon_index, bool is_local) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;
    if (pokemon_index < MIN_POKEMON_INDEX || \
    (is_local && pokemon_index > trainer->num_of_pokemons_local || \
    (!is_local && pokemon_index > trainer->num_of_pokemons_remote))) {
        return POKEMON_TRAINER_INVALID_INDEX;
    }
    if (is_local && trainer->num_of_pokemons_local == LAST_POKEMON)
        return POKEMON_TRAINER_REMOVE_LAST;

    Pokemon pokemon = pokemonTrainerGetPokemon(trainer, pokemon_index);
    if (pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEM;

    pokemonDestroy(pokemon);

    fixPokemonIndexes(trainer,pokemon_index,is_local);

    return POKEMON_TRAINER_SUCCESS;
}


PokemonTrainerResult pokemonTrainerDepositOrWithdrawPokemon(
        PokemonTrainer trainer, int pokemon_index, bool is_desposit) {
    // TODO: is similar validation should be in a different function? (dup with above)
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;
    if (pokemon_index < MIN_POKEMON_INDEX || \
        (is_desposit && pokemon_index > trainer->num_of_pokemons_local) ||\
        (!is_desposit && pokemon_index > trainer->num_of_pokemons_remote)) {
        return POKEMON_TRAINER_INVALID_INDEX;
    }
    if (trainer->num_of_pokemons_local == LAST_POKEMON && is_desposit)
        return POKEMON_TRAINER_DEPOSIT_LAST;

    if (trainer->num_of_pokemons_remote == \
            trainer->max_num_of_pokemons_remote && is_desposit)
        return POKEMON_TRAINER_DEPOSIT_FULL;
    if (trainer->num_of_pokemons_local == \
            trainer->max_num_of_pokemons_local && !is_desposit)
        return POKEMON_TRAINER_PARTY_FULL;
    Pokemon pokemon = pokemonCopy(pokemonTrainerGetPokemon(trainer,
                                                           pokemon_index));
    if (pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEM;
    // no need to check remove result because of validation
    pokemonTrainerRemovePokemonAux(trainer,pokemon_index, is_desposit);
    if (is_desposit) {
        trainer->pokemons_remote[trainer->num_of_pokemons_remote] = pokemon;
        trainer->num_of_pokemons_remote++;
    }
    else {
        trainer->pokemons_local[trainer->num_of_pokemons_local] = pokemon;
        trainer->num_of_pokemons_local++;
    }
    return POKEMON_TRAINER_SUCCESS;
}


void fixPokemonIndexes(PokemonTrainer trainer, int starting_index,
                       bool is_local) {
    int i=starting_index-1;

    if (is_local) {
        for ( ; i < trainer->num_of_pokemons_local-1; i++){
            trainer->pokemons_local[i] = trainer->pokemons_local[i+1];
        }
        //pokemon->moves[i] = NULL; // remove duplicate pointer NOT freeing move TODO:should I remove duplicated pointer?
        trainer->num_of_pokemons_local--;
    }
    else { //TODO: count as dup?
        for ( ; i < trainer->num_of_pokemons_remote-1; i++){
            trainer->pokemons_remote[i] = trainer->pokemons_remote[i+1];
        }
        //pokemon->moves[i] = NULL; // remove duplicate pointer NOT freeing move TODO:should I remove duplicated pointer?
        trainer->num_of_pokemons_remote--;
    }
}


Pokemon pokemonTrainerGetMostRankedPokemonAux(PokemonTrainer trainer,
            int starting_index, bool start_at_local, int* most_ranked_index,
            bool* most_ranked_is_local) {
    *most_ranked_index=starting_index;
    int rank;
    bool is_local = start_at_local;
    // checking local first
    if (is_local) {
        for (int i=starting_index+1; i < trainer->num_of_pokemons_local ; i++) {
            rank = pokemonGetRank(trainer->pokemons_local[*most_ranked_index]);
            if (pokemonGetRank(trainer->pokemons_local[i]) > rank) {
                *most_ranked_index = i;
            }
        }
    }
    if (start_at_local) starting_index=0;
    for (int i=starting_index; i < trainer->num_of_pokemons_remote ; i++) {
        if (is_local) {
            rank = pokemonGetRank(trainer->pokemons_local[*most_ranked_index]);
        }
        else {
            rank = pokemonGetRank(trainer->pokemons_remote[*most_ranked_index]);
        }

        if (pokemonGetRank(trainer->pokemons_remote[i]) > rank) {
            *most_ranked_index = i;
            is_local = false;
        }
    }
    *most_ranked_is_local = is_local;
    if (is_local) return trainer->pokemons_local[*most_ranked_index];
    return trainer->pokemons_remote[*most_ranked_index];
}


void mergeTrainerAndProfessor(PokemonTrainer trainer) {
    while (trainer->num_of_pokemons_remote != NO_POKEMONS && \
         trainer->num_of_pokemons_local < trainer->max_num_of_pokemons_local) {
        trainer->pokemons_local[trainer->num_of_pokemons_local] = \
                trainer->pokemons_remote[0];
        trainer->num_of_pokemons_local++;

        fixPokemonIndexes(trainer, 1, false); //fix first prof. pokemon index
    }
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
    bool is_local = true;

    PokemonTrainerResult result = \
    pokemonTrainerRemovePokemonAux(trainer, pokemon_index, is_local);

    return result;
}


PokemonTrainerResult pokemonTrainerDepositPokemon(
        PokemonTrainer trainer, int pokemon_index) {
    bool is_desposit = true;

    PokemonTrainerResult result = \
    pokemonTrainerDepositOrWithdrawPokemon(trainer,pokemon_index,is_desposit);

    return result;
}

PokemonTrainerResult pokemonTrainerWithdrawPokemon(
        PokemonTrainer trainer, int pokemon_index) {
    bool is_desposit = false;

    PokemonTrainerResult result = \
    pokemonTrainerDepositOrWithdrawPokemon(trainer,pokemon_index,is_desposit);

    return result;
}

int pokemonTrainerGetNumberOfPokemons(PokemonTrainer trainer) {
    assert(trainer != NULL);
    return trainer->num_of_pokemons_local + trainer->num_of_pokemons_remote;
}

Pokemon pokemonTrainerGetMostRankedPokemon(PokemonTrainer trainer) {
    if (trainer == NULL) return NULL;
    int most_ranked_index;
    bool most_ranked_is_local;
    Pokemon pokemon = pokemonTrainerGetMostRankedPokemonAux(
                    trainer,0,true,&most_ranked_index,&most_ranked_is_local);
    return pokemon;
}

PokemonTrainerResult pokemonTrainerMakeMostRankedParty(PokemonTrainer trainer) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;
    int total_pokemons = pokemonTrainerGetNumberOfPokemons(trainer);
    int most_ranked_pokemon_index, starting_index;
    bool is_local = true, most_ranked_is_local;
    Pokemon most_ranked_pokemon, tmp_pokemon;

    for (int i=0; i < total_pokemons; i++) {
        if (i - trainer->num_of_pokemons_local >= 0) is_local=false;
        is_local ? starting_index = i : \
                        starting_index = i - trainer->num_of_pokemons_local;
        most_ranked_pokemon = pokemonTrainerGetMostRankedPokemonAux(
                            trainer, starting_index, is_local,
                           &most_ranked_pokemon_index, &most_ranked_is_local);
        if (is_local) {
            tmp_pokemon = trainer->pokemons_local[starting_index];
            trainer->pokemons_local[starting_index] = most_ranked_pokemon;
        }
        else {
            tmp_pokemon = trainer->pokemons_remote[starting_index];
            trainer->pokemons_remote[starting_index] = most_ranked_pokemon;
        }
        if (most_ranked_is_local)
            trainer->pokemons_local[most_ranked_pokemon_index] = tmp_pokemon;
        else trainer->pokemons_remote[most_ranked_pokemon_index] = tmp_pokemon;
    }
    mergeTrainerAndProfessor(trainer);

    return POKEMON_TRAINER_SUCCESS;
}