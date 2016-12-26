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


/**************************************
 *        Structs declarations        *
 **************************************/

typedef enum {
    POKEDEX_OUT_OF_MEMORY,
    POKEDEX_NULL_ARG,
    POKEDEX_IVALID_ARG,
    POKEDEX_SUCCESS
} PokedexResult;


/**************************************
 *        Functions declarations      *
 **************************************/


PokemonInfo pokedexPokemonInfoCreate(char *name, int cp_initial);

PokemonInfo pokedexPokemonInfoCopy(PokemonInfo pokemon_info);

void pokedexPokemonInfoDestroy(PokemonInfo pokemon_info);

int pokedexPokemonInfoCompare(PokemonInfo pokemon_info1,
                              PokemonInfo pokemon_info2);





Pokedex pokedexCreate();

void pokedexDestroy(Pokedex pokedex);

PokedexResult pokedexAddPokemonInfo(Pokedex pokedex, PokemonInfo pokemon_info);

char* pokedexGetNextEvolution(Pokedex pokedex, char* pokemon_name,
                              int pokemon_level);

int pokedexGetInitialCP(Pokedex pokedex, char* pokemon_name);

int pokedexGetStarBonus(Pokedex pokedex, char* pokemon_name);

PokedexResult pokedexAddType(Pokedex pokedex, char* pokemon_name,
                             char* type_name);

PokedexResult pokedexUpdateNextEvolution(Pokedex pokedex, char* pokemon_name,
                                   char* next_evolution, int evolution_level);

#endif //MATAM_POKEDEX_H
