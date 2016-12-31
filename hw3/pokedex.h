//
// Created by ohad on 24-Dec-16.
//

#ifndef MATAM_POKEDEX_H
#define MATAM_POKEDEX_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include "utilities.h"

/********************************
 *          Defines             *
 ********************************/

typedef Set Pokedex;

typedef struct pokemon_info_t* PokemonInfo;

typedef void* PokemonInfoElement;


/*
* The pokemon in pokedex structure.
*/
struct pokemon_info_t {
    char* name;
    int cp_initial, evolution_level;
    int pokecoin_bonus;
    char* next_evolution;
};

/**************************************
 *        Structs declarations        *
 **************************************/

typedef enum {
    POKEDEX_OUT_OF_MEMORY,
    POKEDEX_NULL_ARG,
    POKEDEX_IVALID_ARG,
    POKEDEX_POKEMON_NOT_IN_POKEDEX,
    POKEDEX_SUCCESS
} PokedexResult;


/**************************************
 *        Functions declarations      *
 **************************************/


/**
* Creates a new pokemon Info.
* The name, pokecoin_bonus, next evolution name and level and initial cp
* are parameters set the corresponding properties of the pokemon info.
*
* @return
* 	A new allocated pokemon info.
* 	If name is NULL or empty, cp is invalid(not positive),
*   or in case of a memory allocation failure - return NULL.
**/
PokemonInfo pokedexPokemonInfoCreate(char *name, int cp_initial);

/**
* Creates a newly allocated copy of a given pokemon info.
*
* @return
*   A newly allocated copy of the original pokemon.
*   NULL if the pokemon is NULL or in any case of memory allocation failure.
*/
PokemonInfo pokedexPokemonInfoCopy(PokemonInfo pokemon_info);

/**
* Frees all memory allocated for the given pokemon info.
* This function can receive NULL. In this case, no action will be taken.
*/
void pokedexPokemonInfoDestroy(PokemonInfo pokemon_info);


/**
* Compare between two pokemons info by pokemon name.
*
* @return
*   int - same as @strcmp
*/
int pokedexPokemonInfoCompare(PokemonInfo pokemon_info1,
                              PokemonInfo pokemon_info2);



/**
* Creates a new pokedex.
* Basically a SET of pokemon info.
*
* @return
* 	A new allocated pokemon info.
* 	NULL if memory allocation failure.
**/
Pokedex pokedexCreate();

/**
* Frees all memory allocated for the given pokedex
* This function can receive NULL. In this case, no action will be taken.
*/
void pokedexDestroy(Pokedex pokedex);

/**
* Add pokemon info to pokedex
*
* @return
* 	POKEDEX_NULL_ARG - pokedex or pokemon info are NULL
 * 	POKEDEX_OUT_OF_MEMORY - if memory allocation error
 * 	POKEDEX_SUCCESS - otherwise.
**/
PokedexResult pokedexAddPokemonInfo(Pokedex pokedex, PokemonInfo pokemon_info);

/**
* get the pokemon next evolution
*
* This function asserts (pokedex != NULL) , (pokemon_name != NULL);
*/
char* pokedexGetNextEvolution(Pokedex pokedex, char* pokemon_name,
                              int pokemon_level);

/**
* get the pokemon initical CP
*
* This function asserts (pokedex != NULL) , (pokemon_name != NULL);
*/
int pokedexGetInitialCP(Pokedex pokedex, char* pokemon_name);

/**
* get the pokemon star bonus of the pokemon
*
* This function asserts (pokedex != NULL) , (pokemon_name != NULL);
*/
int pokedexGetStarBonus(Pokedex pokedex, char* pokemon_name);

/**
* Add a new type to pokemon info. Practically, doesn't add the type but
 * calcs the bonus, check if it's higher than current bonus and if so update it
*
* @return
 * 	POKEDEX_POKEMON_NOT_IN_POKEDEX - if pokemon info not in pokedex
 * 	POKEDEX_SUCCESS - otherwise.
 *
*/
PokedexResult pokedexAddType(Pokedex pokedex, char* pokemon_name,
                             char* type_name);

/**
* Update a pokemon info (that is inside the pokedex) with his next evolution
 * name and level
*
* @return
 *  POKEDEX_IVALID_ARG - if one of the args is NULL
 * 	POKEDEX_POKEMON_NOT_IN_POKEDEX - if pokemon info not in pokedex
 * 	POKEDEX_OUT_OF_MEMORY - in allocation error
 * 	POKEDEX_SUCCESS - otherwise.
 *
*/
PokedexResult pokedexUpdateNextEvolution(Pokedex pokedex, char* pokemon_name,
                                   char* next_evolution, int evolution_level);

/**
* get the pokemon info from pokedex (set)
*
* @return
*   NULL if no pokemon in that name
*   PokemonInfo - if found.
*
*/
PokemonInfo pokedexGetPokemonInfo(Pokedex pokedex, char* name);

#endif //MATAM_POKEDEX_H
