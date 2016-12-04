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

/**
* This function allocate new memory for given pokemon name / move name
* then copy (deep copy) the name into the pokemon / move
* Name must not be NULL or empty string
*
*
* @return
*   chr* - return the pointer of name if success, otherwise NULL
*/
static char* createName(char* name);

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

/**
* Aux function for @pokemonTrainerDepositPokemon and
* @pokemonTrainerWithdrawPokemon Remove a pokemon from a trainer locally [or
 * remote pokemon] and send it to the professor remote pokemon
* [or back to trainer].
*
* Pokemon index must be valid (lower than 1 or bigger than
* num_of_pokemons_local). The remote pokemon index is the number of remote
* pokemons (include him). local pokemons indexes are changed.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer is NULL.
* 	POKEMON_TRAINER_INVALID_INDEX if pokemon_index is invalid (lower than 1 or
*   bigger than num_of_pokemons_local).
*   POKEMON_TRAINER_DEPOSIT_LAST if it's last local pokemon, and he cannot
*   deposit it (only in case of deposit).
*   POKEMON_TRAINER_DEPOSIT_FULL if the professor's deposit is full and can't
*   have more pokemons (only in case of deposit).
*   POKEMON_TRAINER_PARTY_FULL if trainer's deposit is full and can't have
*   more pokemons (only in case of withdraw).
* 	POKEMON_SUCCESS otherwise.
*/
static PokemonTrainerResult pokemonTrainerDepositOrWithdrawPokemon(
        PokemonTrainer trainer, int pokemon_index, bool is_deposit);

/**
* Aux function to @pokemonTrainerRemovePokemon.
* Remove a pokemon from a trainer (local or remote pokemon).
* Can't remove last pokemon.
* Pokemon index must be valid (lower than 1 or bigger than
* num_of_pokemons_local).
*
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer is NULL.
* 	POKEMON_TRAINER_INVALID_INDEX if pokemon_index is invalid (lower than 1 or
*   bigger than num_of_pokemons_local).
*   POKEMON_TRAINER_REMOVE_LAST if the pokemon trainer has one last pokemon
*   locally.
* 	POKEMON_SUCCESS otherwise.
*/
static PokemonTrainerResult pokemonTrainerRemovePokemonAux(
        PokemonTrainer trainer, int pokemon_index, bool is_local);

/**
* Aux function to @pokemonTrainerGetMostRankedPokemon.
* Find and order the most ranked pokemons at the trainer. the trainer should
* have his most ranked pokemons by order (most ranked - first).
* If there are pokemons with the same rank, the function will order them as
* following :
* 1. trainer pokemon or professor pokemon --> trainer pokemon first
* 2. both pokemons at trainer or at the professor --> return smallest index
*
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer is NULL.
* 	POKEMON_SUCCESS otherwise.
* 	*most_ranked_index - int for the index of the pokemon in trainer list
* 	*most_ranked_is_local - bool for telling if pokemon is at the trainer
* 	(local) or at the professor (remote)
*/
static Pokemon pokemonTrainerGetMostRankedPokemonAux(PokemonTrainer trainer,
        int starting_index, bool start_at_local, int* most_ranked_index,
                                              bool* most_ranked_is_local);

/**
* Move pokemons indexes(!) from professor to trainer. The trainer should have
* either max_num_of_pokemons_local number of pokemons or all pokemons he own.
*
*/
static void mergeTrainerAndProfessor(PokemonTrainer trainer);


/**
* Find a pokemon (local or remote) by given index. Helper function to
* @pokemonTrainerGetPokemon.
*
* @return
* 	A pointer to a Pokemon that already exist.
* 	If trainer is NULL or empty or pokemon index is not valid - return NULL.
**/
static Pokemon pokemonTrainerGetPokemonAux(PokemonTrainer trainer,
                                           int pokemon_index, bool is_local);

/****************************************
 *    Assistent Pokemon Trainer Funcs   *
 ****************************************/

char* createName(char* name) {
    if (name == NULL || name[0] == '\0') return NULL;
    char* dst_name = malloc(sizeof(*name)+1);
    if (dst_name != NULL) {
        strcpy(dst_name, name);
        dst_name[strlen(name)] = '\0';
        return dst_name;
    }
    return NULL;
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
    trainer->name = createName(name);
    if (trainer->name == NULL) {
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
    (is_local && pokemon_index > trainer->num_of_pokemons_local) || \
    (!is_local && pokemon_index > trainer->num_of_pokemons_remote)) {
        return POKEMON_TRAINER_INVALID_INDEX;
    }
    if (is_local && trainer->num_of_pokemons_local == LAST_POKEMON)
        return POKEMON_TRAINER_REMOVE_LAST;

    Pokemon pokemon = pokemonTrainerGetPokemonAux(trainer, pokemon_index,
                                                  is_local);
    if (pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEM;

    pokemonDestroy(pokemon);

    fixPokemonIndexes(trainer,pokemon_index,is_local);

    return POKEMON_TRAINER_SUCCESS;
}


PokemonTrainerResult pokemonTrainerDepositOrWithdrawPokemon(
        PokemonTrainer trainer, int pokemon_index, bool is_deposit) {
    // validation is similar to @pokemonTrainerRemovePokemonAux but moving it
    // to a different function won't make the function shorter (need to check
    // if result is POKEMON_TRAINER_SUCCESS) - 4 validation lines are OK.
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;
    if (pokemon_index < MIN_POKEMON_INDEX || \
        (is_deposit && pokemon_index > trainer->num_of_pokemons_local) ||\
        (!is_deposit && pokemon_index > trainer->num_of_pokemons_remote)) {
        return POKEMON_TRAINER_INVALID_INDEX;
    }
    if (trainer->num_of_pokemons_local == LAST_POKEMON && is_deposit)
        return POKEMON_TRAINER_DEPOSIT_LAST;

    if (trainer->num_of_pokemons_remote == \
            trainer->max_num_of_pokemons_remote && is_deposit)
        return POKEMON_TRAINER_DEPOSIT_FULL;
    if (trainer->num_of_pokemons_local == \
            trainer->max_num_of_pokemons_local && !is_deposit)
        return POKEMON_TRAINER_PARTY_FULL;
    Pokemon pokemon = pokemonCopy(pokemonTrainerGetPokemonAux(trainer,
                                                   pokemon_index, is_deposit));
    if (pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEM;
    // no need to check remove result because of validation
    pokemonTrainerRemovePokemonAux(trainer,pokemon_index, is_deposit);
    if (is_deposit) {
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
        trainer->num_of_pokemons_local--;
    }
    else {
        for ( ; i < trainer->num_of_pokemons_remote-1; i++){
            trainer->pokemons_remote[i] = trainer->pokemons_remote[i+1];
        }
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
        for (int i=starting_index; i <= trainer->num_of_pokemons_local ;i++) {
            rank = pokemonGetRank(pokemonTrainerGetPokemonAux(trainer,
                                                          *most_ranked_index,
                                                          is_local));
            if (pokemonGetRank(pokemonTrainerGetPokemonAux(trainer, i,true)) >
                    rank) {
                *most_ranked_index = i;
            }
        }
    }
    if (start_at_local) starting_index=1;
    for (int i=starting_index; i <= trainer->num_of_pokemons_remote ; i++) {
        rank = pokemonGetRank(pokemonTrainerGetPokemonAux(trainer,
                                                        *most_ranked_index,
                                                        is_local));
        if (pokemonGetRank(pokemonTrainerGetPokemonAux(trainer, i,false)) >
                rank) {
            *most_ranked_index = i;
            is_local = false;
        }
    }
    *most_ranked_is_local = is_local;
    return pokemonTrainerGetPokemonAux(trainer, *most_ranked_index, is_local);
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


Pokemon pokemonTrainerGetPokemonAux(PokemonTrainer trainer,
                                    int pokemon_index, bool is_local) {
    if (trainer == NULL || pokemon_index < MIN_POKEMON_INDEX || \
        (pokemon_index > trainer->num_of_pokemons_local && is_local) || \
        (pokemon_index > trainer->num_of_pokemons_remote && !is_local)) {
        return NULL;
    }

    if (is_local) {
        return trainer->pokemons_local[pokemon_index-1];
    }
    else {
        return trainer->pokemons_remote[pokemon_index-1];
    }
}

/********************************
 *    Pokemon Trainer Funcs     *
 ********************************/

PokemonTrainer pokemonTrainerCreate(char* name, Pokemon initial_pokemon,
                                    int max_num_local, int max_num_remote) {
    if (name == NULL || strcmp(name,"") == SAME_STRINGS ||
        initial_pokemon == NULL || max_num_local <= NO_POKEMONS
        || max_num_remote <= NO_POKEMONS)
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
        // duplication - but creating a function for 2 lines is redundant
        for (int j = trainer->num_of_pokemons_remote-1; j >= 0 ; j--) {
            pokemonDestroy(trainer->pokemons_remote[j]);
        }
        free(trainer->pokemons_local);
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
    for (int j=0; j<trainer->num_of_pokemons_remote; j++) {
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

    trainer->num_of_pokemons_local++;

    return POKEMON_TRAINER_SUCCESS;
}

Pokemon pokemonTrainerGetPokemon(PokemonTrainer trainer, int pokemon_index) {

    bool is_local=true;

    Pokemon pokemon = pokemonTrainerGetPokemonAux(trainer, pokemon_index,
                                                  is_local);
    return pokemon;
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
    bool is_deposit = true;

    PokemonTrainerResult result = \
    pokemonTrainerDepositOrWithdrawPokemon(trainer,pokemon_index,is_deposit);

    return result;
}

PokemonTrainerResult pokemonTrainerWithdrawPokemon(
        PokemonTrainer trainer, int pokemon_index) {
    bool is_deposit = false;

    PokemonTrainerResult result = \
    pokemonTrainerDepositOrWithdrawPokemon(trainer,pokemon_index,is_deposit);

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
                    trainer,1,true,&most_ranked_index,&most_ranked_is_local);
    return pokemon;
}

PokemonTrainerResult pokemonTrainerMakeMostRankedParty(PokemonTrainer trainer) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;
    int total_pokemons = pokemonTrainerGetNumberOfPokemons(trainer);
    int most_ranked_pokemon_index, starting_index;
    bool is_local = true, most_ranked_is_local;
    Pokemon most_ranked_pokemon, tmp_pokemon;

    for (int i=1; i <= total_pokemons; i++) {
        if (i - trainer->num_of_pokemons_local > 0) is_local=false;
        if (is_local)
            starting_index = i;
        else
            starting_index = i - trainer->num_of_pokemons_local;
        most_ranked_pokemon = pokemonTrainerGetMostRankedPokemonAux(
                            trainer, starting_index, is_local,
                           &most_ranked_pokemon_index, &most_ranked_is_local);
        tmp_pokemon = pokemonTrainerGetPokemonAux(trainer, starting_index,
                                                  is_local);
        if (is_local)
            trainer->pokemons_local[starting_index-1] = most_ranked_pokemon;
        else
            trainer->pokemons_remote[starting_index-1] = most_ranked_pokemon;

        if (most_ranked_is_local)
            trainer->pokemons_local[most_ranked_pokemon_index-1] = tmp_pokemon;
        else
            trainer->pokemons_remote[most_ranked_pokemon_index-1] = tmp_pokemon;
    }
    mergeTrainerAndProfessor(trainer);
    return POKEMON_TRAINER_SUCCESS;
}


PokemonTrainerResult pokemonTrainerPrintEnumeration(
        PokemonTrainer trainer, FILE* file) {
    if (trainer == NULL || file == NULL) return POKEMON_TRAINER_NULL_ARG;

    PokemonResult result;

    for (int i=0; i<trainer->num_of_pokemons_local; i++) {
        fprintf(file, "%s",trainer->name);
        fprintf(file, ": ");
        result = pokemonPrintName(trainer->pokemons_local[i],file);
        if (result == POKEMON_OUT_OF_MEM) return POKEMON_TRAINER_OUT_OF_MEM;
        fprintf(file, "\n");
        pokemonPrintName(trainer->pokemons_local[i],file);
        fprintf(file, ": ");
        result = pokemonPrintVoice(trainer->pokemons_local[i],file);
        if (result == POKEMON_OUT_OF_MEM) return POKEMON_TRAINER_OUT_OF_MEM;
        fprintf(file, "\n");
    }

    return POKEMON_TRAINER_SUCCESS;
}