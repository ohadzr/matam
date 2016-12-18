#ifndef POKEMON_H_
#define POKEMON_H_


#include <stdio.h>
#include <stdbool.h>
#include "store.h"

typedef enum {
	TYPE_BUG,
    TYPE_FIRE,
    TYPE_GRASS,
    TYPE_NORMAL,
    TYPE_ROCK,
    TYPE_ELECTRIC,
    TYPE_FLYING,
    TYPE_GROUND,
    TYPE_POISON,
    TYPE_WATER,
    TYPE_FAIRY,
    TYPE_GHOST,
    TYPE_ICE,
    TYPE_PSYCHIC
} PokemonType;

typedef enum {
	POKEMON_SUCCESS,
	POKEMON_NULL_ARG,
	POKEMON_OUT_OF_MEM,
	POKEMON_INVALID_TYPE,
    POKEMON_CANT_EVOLVE,
	POKEMON_INVALID_NAME,
    POKEMON_EQUAL,
    POKEMON_DIFFERENT,
	POKEMON_NO_HEALTH_POINTS,
} PokemonResult;


typedef struct pokemon_t* Pokemon;
/*
* The pokemon structure.
*/
typedef struct pokemon_t {
	char* name;
    char* location;
	PokemonType type;
	int cp, cp_bonus, level;
    double hp; //TODO: should be float?
	Pokemon* next_pokemon;
};

/**
* Creates a new pokemon.
* The name, type, location and cp are parameters set the corresponding
* properties of the pokemon.
* The pokemon is created at level 1 and 100 HP.
*
* @return
* 	A new allocated pokemon.
* 	If name is NULL or empty, type is invalid, experience or max_number_of_moves
*   is not positive, or in case of a memory allocation failure - return NULL.
**/
Pokemon pokemonCreate(char* name, char* location, PokemonType type, int cp);

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
* get the pointer to the pokemon's location
*
* This function asserts (pokemon != NULL).
*/
char* pokemonGetLocation(Pokemon pokemon);

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
PokemonResult pokemonUpdateHP(Pokemon pokemon, int value);

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


#endif // POKEMON_H_
