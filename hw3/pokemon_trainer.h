#ifndef POKEMON_TRAINER_H_
#define POKEMON_TRAINER_H_

#include <stdio.h>
#include <stdbool.h>
#include "pokemon.h"
#include "set.h"
#include "store.h"



typedef enum {
	POKEMON_TRAINER_OUT_OF_MEM,
	POKEMON_TRAINER_NULL_ARG,
    POKEMON_TRAINER_INSUFFICIENT_BUDGET,
    POKEMON_TRAINER_NO_AVAILABLE_ITEM,
	POKEMON_TRAINER_SUCCESS
} PokemonTrainerResult;

typedef struct pokemon_trainer_t {
    char* name;
	char* location;
    Set pokemon_set;
    Set item_set;
	double xp;
    int pokecoins;
	int number_of_caught_pokemons;

} *PokemonTrainer;

/**
* Creates a new pokemon trainer.
* The trainer has a name property, and a location property,
* the budget is the beginning amount of pokecoins he has,
* XP that set to DEFUALT_XP,
* and number_of_caught_pokemons parameter sets zero.
* Also, create two sets - one for pokemons and one for items.
*
* @return
* 	A new allocated pokemon trainer.
* 	NULL - if name is NULL or empty, location is NULL, or budget is negative or
* 	if memory allocation fails.
*
**/
PokemonTrainer pokemonTrainerCreate(char* name, char* location, int budget);

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
* Add the a pokemon to the pokemon set of a given trainer.
* The new pokemon is a copy of given pokemon.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or pokemon is NULL.
 * 	POKEMON_TRAINER_OUT_OF_MEM if set had a memory allocation error.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerAddPokemon(PokemonTrainer trainer,
	Pokemon pokemon);


#endif // POKEMON_TRAINER_H_
