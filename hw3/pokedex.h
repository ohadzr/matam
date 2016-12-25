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
    POKEDEX_EQUAL,
    POKEDEX_DIFFERENT,
    POKEDEX_SUCCESS
} PokedexResult;

typedef void* PokemonInfoElement;

typedef enum {
    TYPE_BUG,
    TYPE_GRASS,
    TYPE_NORMAL,
    TYPE_GROUND,
    TYPE_GHOST,
    TYPE_PSYCHIC,

    TYPE_ROCK,
    TYPE_ELECTRIC,
    TYPE_WATER,
    TYPE_FAIRY,
    TYPE_ICE,

    TYPE_FLYING,
    TYPE_POISON,
    TYPE_FIRE
} PokemonType;



PokemonInfo pokedexPokemonInfoCreate(char *name, Set type_set, int cp_initial);

PokemonInfo pokedexPokemonInfoCopy(PokemonInfo pokemon_info);

void pokedexPokemonInfoDestroy(PokemonInfo pokemon_info);

PokedexResult pokedexPokemonInfoUpdateNextEvolution(PokemonInfo pokemon_info,
                                                    char* next_evolution,
                                                    int evolution_level);

//char* pokedexPokemonInfoGetNextEvolution(PokemonInfo pokemon_info);
//
//int pokedexPokemonInfoGetEvolutionLevel(PokemonInfo pokemon_info);

int pokedexPokemonInfoCompare(PokemonInfo pokemon_info1,
                              PokemonInfo pokemon_info2);



Pokedex pokedexCreate();

void pokedexDestroy(Pokedex pokedex);

PokedexResult pokedexAddPokemonInfo(Pokedex pokedex, PokemonInfo pokemon_info);

int pokedexGetInitialCP(Pokedex pokedex, char* pokemon_name);

int pokedexGetStarBonus(Pokedex pokedex, char* pokemon_name);

pokedexTypeToChar;

pokedexCharToType;

//pokedexIsValidtype;



#endif //MATAM_POKEDEX_H
