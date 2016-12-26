//
// Created by ohad on 24-Dec-16.
//

#ifndef MATAM_POKEDEX_H
#define MATAM_POKEDEX_H

#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"
#include "utilities.h"
#include "string.h"

/**************************************
 *        Structs declarations        *
 **************************************/

typedef Set Pokedex;

typedef struct pokemon_info_t* PokemonInfo;

typedef enum {
    POKEDEX_OUT_OF_MEMORY,
    POKEDEX_NULL_ARG,
    POKEDEX_IVALID_ARG,
    POKEDEX_SUCCESS
} PokedexResult;

typedef void* PokemonInfoElement;



PokemonInfo pokedexPokemonInfoCreate(char *name, int cp_initial);

PokemonInfo pokedexPokemonInfoCopy(PokemonInfo pokemon_info);

void pokedexPokemonInfoDestroy(PokemonInfo pokemon_info);

int pokedexPokemonInfoCompare(PokemonInfo pokemon_info1,
                              PokemonInfo pokemon_info2);


PokedexResult pokedexPokemonInfoUpdateNextEvolution(PokemonInfo pokemon_info,
                                                    char* next_evolution,
                                                    int evolution_level);



Pokedex pokedexCreate();

void pokedexDestroy(Pokedex pokedex);

PokedexResult pokedexAddPokemonInfo(Pokedex pokedex, PokemonInfo pokemon_info);

char* pokedexGetNextEvolution(Pokedex pokedex, char* pokemon_name,
                              int pokemon_level);

int pokedexGetEvolutionLevel(Pokedex pokedex, char* pokemon_name);

int pokedexGetInitialCP(Pokedex pokedex, char* pokemon_name);

int pokedexGetStarBonus(Pokedex pokedex, char* pokemon_name);


#endif //MATAM_POKEDEX_H
