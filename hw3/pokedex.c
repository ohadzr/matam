//
// Created by ohad on 24-Dec-16.
//

#include <stdlib.h>
#include "pokedex.h"


/**************************************
 *              Defines               *
 **************************************/


#define SAME_STRINGS 0
#define NO_BONUS 0
#define REGULAR_BONUS 10
#define ONE_STAR_BONUS 20
#define TWO_STARS_BONUS 30

/*
* The pokemon in pokedex structure.
*/
struct pokemon_info_t {
    char* name;
    int cp_initial, evolution_level;
    Set type_set;
    char* next_evolution;
};

/********************************
 * Helper Function Declarations *
 ********************************/

/* wrapper function to pokedexPokemonInfoCopy so it
 * will be possible to work with Set GDT */
PokemonInfoElement static pokemonInfoCopyElement(
        PokemonInfoElement pokemon_info);

/*wrapper function to pokedexPokemonInfoCopy so it
 * will be possible to work with Set GDT*/
void static pokemonInfoFreeElement(PokemonInfoElement pokemon_info);

/*wrapper function to pokedexPokemonInfoCompare so it
 * will be possible to work with Set GDT*/
int static pokemonInfoCompareElement(PokemonInfoElement pokemon_info1 ,
                                      PokemonInfoElement pokemon_info2);

static int typeToBonus(PokemonType pokemon_type);

static PokemonInfo pokedexGetPokemonInfo(Pokedex pokedex, char* name);


/****************************************
 *    Assistent Pokemon Trainer Funcs   *
 ****************************************/


PokemonInfoElement pokemonInfoCopyElement(
        PokemonInfoElement pokemon_info) {
    return pokedexPokemonInfoCopy( (PokemonInfo)pokemon_info );
}


void pokemonInfoFreeElement( PokemonInfoElement pokemon_info ) {
    pokedexPokemonInfoDestroy( (PokemonInfo)pokemon_info );
}


int  pokemonInfoCompareElement( PokemonInfoElement pokemon_info1 ,
                               PokemonInfoElement pokemon_info2 ) {
    return pokedexPokemonInfoCompare((PokemonInfo)pokemon_info1 ,
                                     (PokemonInfo)pokemon_info2 );
}



int typeToBonus(PokemonType pokemon_type) {
    switch (pokemon_type) {
        case TYPE_BUG: return REGULAR_BONUS;
        case TYPE_GRASS: return REGULAR_BONUS;
        case TYPE_NORMAL: return REGULAR_BONUS;
        case TYPE_GROUND: return REGULAR_BONUS;
        case TYPE_GHOST: return REGULAR_BONUS;
        case TYPE_PSYCHIC: return REGULAR_BONUS;
        case TYPE_ROCK: return ONE_STAR_BONUS;
        case TYPE_ELECTRIC: return ONE_STAR_BONUS;
        case TYPE_WATER: return ONE_STAR_BONUS;
        case TYPE_FAIRY: return ONE_STAR_BONUS;
        case TYPE_ICE: return ONE_STAR_BONUS;
        case TYPE_FLYING: return TWO_STARS_BONUS;
        case TYPE_POISON: return TWO_STARS_BONUS;
        case TYPE_FIRE: return TWO_STARS_BONUS;
    }
    return NO_BONUS;
}

PokemonInfo pokedexGetPokemonInfo(Pokedex pokedex, char* name) {
    if (pokedex == NULL || name == NULL) return NULL;

    SET_FOREACH(PokemonInfo, pokemon_info, pokedex) {
        if (strcmp(pokemon_info->name, pokemon_name) == SAME_STRINGS)
            return pokemon_info;
    }
}

/********************************
 *          Pokedex Funcs       *
 ********************************/


PokemonInfo pokedexPokemonInfoCreate(char *name, Set type_set, int cp_initial) {
    if (name == NULL || type_set == NULL) return NULL;

    PokemonInfo pokemon_info = malloc(sizeof(*pokemon_info));
    if (pokemon_info == NULL) return NULL;

    pokemon_info->cp_initial = cp_initial;
    pokemon_info->next_evolution = NULL;

    pokemon_info->name = stringCopy(name);
    if (pokemon_info->name == NULL) {
        free(pokemon_info);
        return NULL;
    }

    pokemon_info->type_set = setCopy(type_set);
    if (pokemon_info->type_set == NULL) {
        free(pokemon_info->name);
        free(pokemon_info);
        return NULL;
    }

    return pokemon_info;
}

PokemonInfo pokedexPokemonInfoCopy(PokemonInfo pokemon_info) {
    if (pokemon_info == NULL) return NULL;
    PokemonInfo new_pokemon_info = pokedexPokemonInfoCreate(pokemon_info->name,
                             pokemon_info->type_set, pokemon_info->cp_initial);
    if (new_pokemon_info == NULL) return NULL;
    if (pokemon_info->next_evolution != NULL) {
        PokedexResult result = pokedexPokemonInfoUpdateNextEvolution(
                new_pokemon_info,
                pokemon_info->next_evolution,
                pokemon_info->evolution_level);
        if (result == POKEDEX_OUT_OF_MEMORY) {
            pokedexPokemonInfoDestroy(new_pokemon_info);
            return NULL;
        }
    }
    return new_pokemon_info;
}

void pokedexPokemonInfoDestroy(PokemonInfo pokemon_info) {
    if (pokemon_info != NULL) {
        stringDestroy(pokemon_info->name);
        stringDestroy(pokemon_info->next_evolution);
        setDestroy(pokemon_info->type_set);
        free(pokemon_info);
    }
}

PokedexResult pokedexPokemonInfoUpdateNextEvolution(PokemonInfo pokemon_info,
                                                    char* next_evolution,
                                                    int evolution_level) {
    if (pokemon_info == NULL || next_evolution == NULL)
        return POKEDEX_NULL_ARG;
    if (evolution_level <= 0) return POKEDEX_IVALID_ARG;

    pokemon_info->next_evolution = stringCopy(next_evolution);
    if (pokemon_info->next_evolution == NULL)
        return POKEDEX_OUT_OF_MEMORY;

    pokemon_info->evolution_level = evolution_level;

    return POKEDEX_SUCCESS;
}

//char* pokedexPokemonInfoGetNextEvolution(PokemonInfo pokemon_info) {
//    assert(pokemon_info != NULL);
//    return pokemon_info->next_evolution;
//}
//
//int pokedexPokemonInfoGetEvolutionLevel(PokemonInfo pokemon_info) {
//    assert(pokemon_info != NULL);
//    return pokemon_info->evolution_level;
//}

int pokedexPokemonInfoCompare(PokemonInfo pokemon_info1,
                                        PokemonInfo pokemon_info2) {
    assert(pokemon_info1 != NULL);
    assert(pokemon_info2 != NULL);

    return strcmp(pokemon_info1->name, pokemon_info2->name);
}

Pokedex pokedexCreate() {
    return setCreate(pokemonInfoCopyElement, pokemonInfoFreeElement,
                     pokemonInfoCompareElement);
}

void pokedexDestroy(Pokedex pokedex) {
    setDestroy(pokedex);
}

PokedexResult pokedexAddPokemonInfo(Pokedex pokedex, PokemonInfo pokemon_info) {
    if (pokedex == NULL || pokemon_info == NULL) return POKEDEX_NULL_ARG;

    SetResult result = setAdd(pokedex, pokemon_info);
    if (result == SET_OUT_OF_MEMORY)
        return POKEDEX_OUT_OF_MEMORY;

    return POKEDEX_SUCCESS;
}

int pokedexGetInitialCP(Pokedex pokedex, char* pokemon_name) {
    assert (pokedex != NULL);
    assert (pokemon_name!= NULL);

    PokemonInfo pokemon_info = pokedexGetPokemonInfo(pokedex, pokemon_name);

    return pokemon_info->cp_initial;
}

int pokedexGetStarBonus(Pokedex pokedex, char* pokemon_name) {
    assert(pokedex != NULL);
    assert(pokemon_name != NULL);

    PokemonInfo pokemon_info = pokedexGetPokemonInfo(pokedex, pokemon_name);

    int bonus = NO_BONUS;

    SET_FOREACH(PokemonType, type, pokemon_info->type_set) {
        if (typeToBonus(type) > bonus)
            bonus = typeToBonus(type);
    }

    return bonus;
}

pokedexTypeToChar;

pokedexCharToType;



