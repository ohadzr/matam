#ifndef POKEMON_TRAINER_H_
#define POKEMON_TRAINER_H_

#include <stdio.h>
#include <stdbool.h>
#include "pokemon.h"

typedef enum {
	POKEMON_TRAINER_SUCCESS,
	POKEMON_TRAINER_NULL_ARG,
	POKEMON_TRAINER_OUT_OF_MEM,
	POKEMON_TRAINER_INVALID_INDEX,
	POKEMON_TRAINER_PARTY_FULL,
	POKEMON_TRAINER_REMOVE_LAST,
	POKEMON_TRAINER_DEPOSIT_LAST,
	POKEMON_TRAINER_DEPOSIT_FULL
} PokemonTrainerResult;

typedef struct pokemon_trainer_t {
	// TODO: Add fields here
    char* name;
    Pokemon* pokemons_local;
    Pokemon* pokemons_remote;
    int num_of_pokemons_local, num_of_pokemons_remote;
    int max_num_of_pokemons_local, max_num_of_pokemons_remote;
} *PokemonTrainer;

/**
* Creates a new pokemon trainer.
* The trainer has a name property,
* pokemon list that get initialized with a first given pokemon.
*
* The max_num_local parameter sets the maximum amount of pokemons that the
* trainer is allowed to have on him at any given time.
* The max_num_remote parameter sets the maximum amount of pokemons that the
* trainer is allowed to have at the professor at any given time.
*
* @return
* 	A new allocated pokemon trainer.
* 	If name is NULL or empty, initial_pokemon is NULL, max_num_local or
*   max_num_remote is not positive, or in case of a memory allocation failure
*   - return NULL.
**/
PokemonTrainer pokemonTrainerCreate(char* name, Pokemon initial_pokemon,
	int max_num_local, int max_num_remote);

/**
* Frees all memory allocated for the given pokemon trainer.
* This function can receive NULL. In this case, no action will be taken.
*/
void pokemonTrainerDestroy(PokemonTrainer trainer);

/**
* Creates a newly allocated copy of a given pokemon trainer.
*
* @return
*   A newly allocated copy of the original pokemon trainer.
*   NULL if the trainer  is NULL or in any case of memory allocation failure.
*/
PokemonTrainer pokemonTrainerCopy(PokemonTrainer trainer);

/**
* Add the a pokemon to a given trainer.
* The new pokemon is a copy of given pokemon.
* The pokemon index is the number of pokemons the trainer has.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or pokemon is NULL.
* 	POKEMON_TRAINER_PARTY_FULL if number of local pokemons reached max.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerAddPokemon(PokemonTrainer trainer,
	Pokemon pokemon);

/**
* Find and return a pokemon by given index
*
* @return
* NULL if trainer is NULL or if pokemon_index is invalid (lower than 1 or
* bigger than num_of_pokemons_local).
* Pokemon - by the given index, otherwise.
*/
Pokemon pokemonTrainerGetPokemon(PokemonTrainer trainer, int pokemon_index);

PokemonTrainerResult pokemonTrainerRemovePokemon(
	PokemonTrainer trainer, int pokemon_index);

PokemonTrainerResult pokemonTrainerDepositPokemon(
	PokemonTrainer trainer, int pokemon_index);

PokemonTrainerResult pokemonTrainerWithdrawPokemon(
	PokemonTrainer trainer, int pokemon_index);

int pokemonTrainerGetNumberOfPokemons(PokemonTrainer trainer);

Pokemon pokemonTrainerGetMostRankedPokemon(PokemonTrainer trainer);

PokemonTrainerResult pokemonTrainerMakeMostRankedParty(PokemonTrainer trainer);

PokemonTrainerResult pokemonTrainerPrintEnumeration(
	PokemonTrainer trainer, FILE* file);

#endif // POKEMON_TRAINER_H_
