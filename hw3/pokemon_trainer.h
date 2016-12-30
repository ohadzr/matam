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


/********************************
 *          Defines             *
 ********************************/

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


/**************************************
 *        Functions declarations      *
 **************************************/



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



/**
* Find and return a pokemon by a given id
*
* @return
*   NULL if trainer is NULL or if no pokemon in that id was found
*   Pokemon from trainer's pokemon list otherwise.
*/
Pokemon pokemonTrainerGetPokemon(PokemonTrainer trainer, int pokemon_id);


/**
* Buying item from store and moving it from store to trainer item list.
* item must be valid, exist in store and the trainer must have sufficent
* funds to buy item. After buying the trainer's budget is reduced by the
* price of the item.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or store or item are NULL.
* 	POKEMON_TRAINER_INSUFFICIENT_BUDGET if trainer doesn't have enough budget
* 	POKEMON_TRAINER_ITEM_OUT_OF_STOCK if item not in store
* 	POKEMON_TRAINER_OUT_OF_MEMORY if set had a memory allocation error.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerBuyItem(PokemonTrainer trainer, Item item,
										   Store store);

/**
* Trainer goes hunting in a given location. If there's a pokemon in location
* he catch him (first one, if there are many).
* pokemon is being added to trainer's pokemon list and being giving an ID of
* the next pokemon. The location must not be the trainer's current location and
* must be reachable from current trainer location.
* After hunting print results using @mtmPrint functions from print utilities.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or location, world_map, pokedex or
* 	output are NULL.
* 	POKEMON_TRAINER_ALREADY_IN_LOCATION if trainer is already in the same
* 	location
* 	POKEMON_TRAINER_LOCATION_IS_NOT_REACHABLE if trainer can't reach location
* 	POKEMON_TRAINER_OUT_OF_MEMORY if set had a memory allocation error.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerGoHunt(PokemonTrainer trainer,
										  char* location, WorldMap world_map,
										  Pokedex pokedex, FILE* output);


/**
* A battle between 2 trainers and 2 pokemons.
* In the battle the pokemons HP and level are changed and also the trainers XP.
* A pokemon can die and be deleted from a game if its HP reaches zero.
* A pokemon can evolve after a battle (even a few evolutions) if it reaches
* to his evolution level.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or location, world_map, pokedex or
* 	output are NULL.
* 	POKEMON_TRAINER_POKEMON_DOESNT_EXIST if one of the pokemons doesn't exist
* 	POKEMON_TRAINER_INVALID_AGR if trainers name is the same
* 	POKEMON_TRAINER_OUT_OF_MEMORY if set had a memory allocation error (in case
* 	of evolution)
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerFight(PokemonTrainer trainer1,
										 PokemonTrainer trainer2,
										 int pokemon1_id,
										 int pokemon2_id, Pokedex pokedex,
										 FILE* output);


/**
* Heal a pokemon from trainer's pokemon list by given id with a potion.
* if the trainer has a potion that can heal pokemon to full HP without use it,
 * unless there's a potion with smaller value that can HP to full HP.
 * If there's no potion to heal to full HP, uses max valued potion.
 * If trainer doesn't have potions - doesn't heal pokemon.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer is NULL.
* 	POKEMON_TRAINER_POKEMON_DOESNT_EXIST if one the pokemon doesn't exist in
* 	trainer's pokemon list (dead or invalid)
* 	POKEMON_TRAINER_ITEM_OUT_OF_STOCK if trainer doesn't have potions
* 	POKEMON_TRAINER_POKEMON_HP_AT_MAX if the pokemon's HP is already at max
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerHealPokemon(PokemonTrainer trainer,
											   int pokemon_id);

/**
* Train a pokemon from trainer's pokemon list by given id  with a candy.
* Use the trainer's highest valued candy to train pokemon.
* If trainer doesn't have candies - doesn't train pokemon.
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer is NULL.
* 	POKEMON_TRAINER_POKEMON_DOESNT_EXIST if one the pokemon doesn't exist in
* 	trainer's pokemon list (dead or invalid)
* 	POKEMON_TRAINER_ITEM_OUT_OF_STOCK if trainer doesn't have potions
* 	POKEMON_SUCCESS otherwise.
*/
PokemonTrainerResult pokemonTrainerTrainPokemon(PokemonTrainer trainer,
												int pokemon_id);


/**
*   Print the trainers report. First all candies (ascending value), second
*   potion and then pokemons (by ID, ascending).
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer is NULL.
* 	POKEMON_TRAINER_OUT_OF_MEMORY if store sorting failed (allocation error).
* 	POKEMON_SUCCESS otherwise.
*/
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

/**
* Check if a trainer exists in a trainers set.
*
* @return
* 	true - if exists.
* 	false - if not.
**/
bool trainersDoesTrainerExist(Trainers trainers, char* trainer_name);

#endif // POKEMON_TRAINER_H_
