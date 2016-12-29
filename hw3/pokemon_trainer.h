#ifndef POKEMON_TRAINER_H_
#define POKEMON_TRAINER_H_

#include <stdio.h>
#include <stdbool.h>
#include "pokemon.h"
#include "set.h"
#include "list.h"
#include "store.h"
#include "utilities.h"
#include "print_utils.h"
#include "pokedex.h"
#include "location.h"


typedef struct pokemon_trainer_t* PokemonTrainer;


typedef Set Trainers;
typedef void* PokemonTrainerElement;



typedef enum {
	POKEMON_TRAINER_OUT_OF_MEMORY,
	POKEMON_TRAINER_NULL_ARG,
    POKEMON_TRAINER_INSUFFICIENT_BUDGET,
    POKEMON_TRAINER_ITEM_OUT_OF_STOCK,
    POKEMON_TRAINER_ALREADY_IN_LOCATION,
    POKEMON_TRAINER_LOCATION_IS_NOT_REACHABLE,
    POKEMON_TRAINER_POKEMON_DOESNT_EXIST,
    POKEMON_TRAINER_INVALID_AGR,
    POKEMON_TRAINER_POKEMON_HP_AT_MAX,
	POKEMON_TRAINER_ALREADY_EXIST,
	POKEMON_TRAINER_SUCCESS
} PokemonTrainerResult;



/**
* Check if all arguments for @pokemonTrainerCreate are valid.
* name and location shouldn't be NULL or empty strings
* budget must be not negative
*
* @return
* 	true - if valid.
* 	false - if not.
*
**/
bool pokemonTrainerIsValidArgs(char* name, char* location, int budget);

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
* Add the a pokemon to the pokemon list of a given trainer.
* The new pokemon is a copy of given pokemon.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or pokemon is NULL.
 * 	POKEMON_TRAINER_OUT_OF_MEMORY if set had a memory allocation error.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerAddPokemon(PokemonTrainer trainer,
                                              Pokemon pokemon,
                                              Pokedex pokedex);



Pokemon pokemonTrainerGetPokemon(PokemonTrainer trainer, int pokemon_id);

PokemonTrainerResult pokemonTrainerBuyItem(PokemonTrainer trainer, Item item,
										   Store store);


PokemonTrainerResult pokemonTrainerGoHunt(PokemonTrainer trainer,
										  char* location, WorldMap world_map,
										  Pokedex pokedex, FILE* output);


PokemonTrainerResult pokemonTrainerFight(PokemonTrainer trainer1,
										 PokemonTrainer trainer2,
										 int pokemon1_id,
										 int pokemon2_id, Pokedex pokedex,
										 FILE* output);

PokemonTrainerResult pokemonTrainerHealPokemon(PokemonTrainer trainer,
											   int pokemon_id);


PokemonTrainerResult pokemonTrainerTrainPokemon(PokemonTrainer trainer,
												int pokemon_id);


PokemonTrainerResult pokemonTrainerReport(PokemonTrainer trainer,
										  FILE* output);


/**
* Creates a new set of trainers.
*
* @return
* 	A new allocated pokemon trainers set.
* 	NULL - if allocation fails is NULL.
* 	Set - Otherwise
*
**/
Trainers trainersCreate();

/**
* Add a trainer to set of trainers. Using @setAdd
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or trainers are NULL.
* 	POKEMON_TRAINER_OUT_OF_MEMORY if set had a memory allocation error.
*	POKEMON_TRAINER_ALREADY_EXIST if trainer already exist
* 	POKEMON_SUCCESS otherwise.
*
**/
PokemonTrainerResult trainersAddTrainer(Trainers trainers,
										PokemonTrainer trainer);
/**
* Frees all memory allocated for the given pokemon trainers set.
* This function can receive NULL. In this case, no action will be taken.
*/
void trainersDestroy(Trainers trainers);


/**
* Find and return a trainer from a trainers set by name comparing.
*
* @return
* 	A pointer to the PokemonTrainer from set.
* 	NULL if trainer doesn't exists in set.
*
**/
PokemonTrainer trainersGetTrainer(Trainers trainers, char* trainer_name);

#endif // POKEMON_TRAINER_H_
