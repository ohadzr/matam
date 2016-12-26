#ifndef POKEMON_H_
#define POKEMON_H_


#include <stdio.h>
#include <stdbool.h>
#include "store.h"
#include "set.h"
#include "utilities.h"

typedef enum {
	POKEMON_SUCCESS,
	POKEMON_NULL_ARG,
	POKEMON_OUT_OF_MEMORY,
	POKEMON_INVALID_TYPE,
    POKEMON_INVALID_VALUE,
    POKEMON_CANT_EVOLVE,
	POKEMON_INVALID_NAME,
	POKEMON_EQUAL,
	POKEMON_DIFFERENT,
	POKEMON_NO_HEALTH_POINTS,
} PokemonResult;


/**************************************
 *        Structs declarations        *
 **************************************/

typedef struct pokemon_t* Pokemon;

/*
* The pokemon structure.
*/
struct pokemon_t {
    char *name;
    int cp, cp_bonus, level, id;
    double hp;
};

typedef void* PokemonElement;

/**
* Creates a new pokemon.
* The name, type and cp are parameters set the corresponding
* properties of the pokemon.
* The pokemon is created at level 1 and 100 HP.
*
* @return
* 	A new allocated pokemon.
* 	If name is NULL or empty, type is invalid, experience or max_number_of_moves
*   is not positive, or in case of a memory allocation failure - return NULL.
**/
Pokemon pokemonCreate(char* name);

/**
* Frees all memory allocated for the given pokemon.
* This function can receive NULL. In this case, no action will be taken.
*/
void pokemonDestroy(Pokemon pokemon);

/**
* Creates a newly allocated copy of a given pokemon.
*
* @return
*   A newly allocated copy of the original pokemon.
*   NULL if the pokemon is NULL or in any case of memory allocation failure.
*/
Pokemon pokemonCopy(Pokemon pokemon);


/**
* get the pokemon level
*
* This function asserts (pokemon != NULL).
*/
int pokemonGetLevel(Pokemon pokemon);

/**
* Changes the pokemon's level - by given value.
* value must be >= 0
*
* @return
* 	POKEMON_NULL_ARG if pokemon is NULL.
* 	POKEMON_INVALID_VALUE - if value is < 0
* 	POKEMON_SUCCESS otherwise.
*/
PokemonResult pokemonUpdateLevel(Pokemon pokemon, int added_value);

/**
* get the pokemon HP
*
* This function asserts (pokemon != NULL).
*/
double pokemonGetHP(Pokemon pokemon);

/**
* get the pokemon CP - including bonus from items.
*
* This function asserts (pokemon != NULL).
*/
int pokemonGetCP(Pokemon pokemon);

/**
* get the pointer to the pokemon name
*
* This function asserts (pokemon != NULL).
*/
char* pokemonGetName(Pokemon pokemon);


/**
* Update the given pokemon HP by given value.
* If new HP is zero or below - pokemon is dead
* If new HP is above DEFAULT_HP - DEFAULT_HP is set.
*
* @return
* 	POKEMON_NULL_ARG if pokemon is NULL.
* 	POKEMON_NO_HEALTH_POINTS if HP is not positive.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonResult pokemonUpdateHP(Pokemon pokemon, double value);

/**
* Use an item on a pokemon.
* If potion - add to hp points (can't exceed more than DEFAULT_HP)
* If candy - add to cp points.
*
* @return
* 	POKEMON_NULL_ARG if pokemon or Item are NULL.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonResult pokemonUseItem(Pokemon pokemon, Item item);

/**
* compare between two pokemons and return a bool. check if has the same name
* and if the type is the same type.
*
* @return
*   POKEMON_EQUAL - if the same.
* 	POKEMON_DIFFERENT - if one of the pokemons is NULL or if not same.
*/
PokemonResult pokemonCompare(Pokemon first_pokemon, Pokemon second_pokemon);

/**
* Check if a pokemon should get evolved. If so, evolves the given pokemon.
* If the function succeeds, the pokemon gets a new name, and its cp
* value grow by given cp from pokedex.
*
* @return
* 	POKEMON_NULL_ARG if pokemon or new_name is NULL.
*   POKEMON_CANNOT_EVOLVE if the pokemon level is not enough or no next
*   evolution.
*   POKEMON_OUT_OF_MEM - if faild allocating new name for the pokemon.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonResult pokemonCheckEvolution(Pokemon pokemon);

/**
* Update the given pokemon ID.
*
* @return
* 	POKEMON_NULL_ARG if pokemon is NULL.
* 	POKEMON_SUCCESS otherwise.
*/
PokemonResult pokemonUpdateID(Pokemon pokemon, int new_id);


/**
* Get the pokemon's unique ID.
*
* @return
* 	return int of the pokemon's id
**/
int pokemonGetID(Pokemon pokemon);


/**
* Wrapping the @pokemonCopy for @listCreate (lish.h) with void* element
*
* @return
* 	PokemonElement (void*)
**/
PokemonElement pokemonCopyElement( PokemonElement pokemon );

/**
* Wrapping the @pokemonDestroy for @listCreate (lish.h)
*
**/
void pokemonFreeElement( PokemonElement pokemon );

#endif // POKEMON_H_
