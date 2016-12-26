//
// Created by ohad on 24-Dec-16.
//

#include "pokedex.h"


/**************************************
 *              Defines               *
 **************************************/


#define SAME_STRINGS 0
#define NO_BONUS 0
#define REGULAR_BONUS 10
#define ONE_STAR_BONUS 20
#define TWO_STARS_BONUS 30
#define NO_NEXT_EVOLUTION -1


/**************************************
 *        Structs declarations        *
 **************************************/

/*
* The pokemon in pokedex structure.
*/
struct pokemon_info_t {
    char* name;
    int cp_initial, evolution_level;
    int pokecoin_bonus;
    char* next_evolution;
};


/********************************
 * Helper Function Declarations *
 ********************************/

/* wrapper function to pokedexPokemonInfoCopy so it
 * will be possible to work with Set GDT */
PokemonInfoElement static pokemonInfoCopyElement(
        PokemonInfoElement pokemon_info);

/*wrapper function to pokedexPokemonInfoDestroy so it
/*wrapper function to pokedexPokemonInfoDestroy so it
 * will be possible to work with Set GDT*/
void static pokemonInfoFreeElement(PokemonInfoElement pokemon_info);

/*wrapper function to pokedexPokemonInfoCompare so it
 * will be possible to work with Set GDT*/
int static pokemonInfoCompareElement(PokemonInfoElement pokemon_info1 ,
                                      PokemonInfoElement pokemon_info2);

static int typeToBonus(char* type_name);

static PokemonInfo pokedexGetPokemonInfo(Pokedex pokedex, char* name);

static int pokedexGetEvolutionLevel(Pokedex pokedex, char* pokemon_name);

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


int typeToBonus(char* type_name) {
    if (strcmp(type_name, "BUG") == SAME_STRINGS) return REGULAR_BONUS;
    if (strcmp(type_name, "GRASS") == SAME_STRINGS) return REGULAR_BONUS;
    if (strcmp(type_name, "NORMAL") == SAME_STRINGS) return REGULAR_BONUS;
    if (strcmp(type_name, "GROUND") == SAME_STRINGS) return REGULAR_BONUS;
    if (strcmp(type_name, "GHOST") == SAME_STRINGS) return REGULAR_BONUS;
    if (strcmp(type_name, "PSYCHIC") == SAME_STRINGS) return REGULAR_BONUS;
    if (strcmp(type_name, "ROCK") == SAME_STRINGS) return ONE_STAR_BONUS;
    if (strcmp(type_name, "ELECTRIC") == SAME_STRINGS) return ONE_STAR_BONUS;
    if (strcmp(type_name, "WATER") == SAME_STRINGS) return ONE_STAR_BONUS;
    if (strcmp(type_name, "FAIRY") == SAME_STRINGS) return ONE_STAR_BONUS;
    if (strcmp(type_name, "ICE") == SAME_STRINGS) return ONE_STAR_BONUS;
    if (strcmp(type_name, "FLYING") == SAME_STRINGS) return TWO_STARS_BONUS;
    if (strcmp(type_name, "POISON") == SAME_STRINGS) return TWO_STARS_BONUS;
    if (strcmp(type_name, "FIRE") == SAME_STRINGS) return TWO_STARS_BONUS;
    return NO_BONUS;
}

PokemonInfo pokedexGetPokemonInfo(Pokedex pokedex, char* pokemon_name) {
    if (pokedex == NULL || pokemon_name == NULL) return NULL;

    SET_FOREACH(PokemonInfo, pokemon_info, pokedex) {
        if (strcmp(pokemon_info->name, pokemon_name) == SAME_STRINGS)
            return pokemon_info;
    }
    return NULL;
}


int pokedexGetEvolutionLevel(Pokedex pokedex, char* pokemon_name) {
    assert(pokedex != NULL);
    assert(pokemon_name != NULL);

    PokemonInfo pokemon_info = pokedexGetPokemonInfo(pokedex, pokemon_name);
    if (pokemon_info->next_evolution != NULL)
        return pokemon_info->evolution_level;

    return NO_NEXT_EVOLUTION;
}

/********************************
 *          Pokedex Funcs       *
 ********************************/


PokemonInfo pokedexPokemonInfoCreate(char *name, int cp_initial) {
    if (name == NULL) return NULL;

    PokemonInfo pokemon_info = malloc(sizeof(*pokemon_info));
    if (pokemon_info == NULL) return NULL;

    pokemon_info->cp_initial = cp_initial;
    pokemon_info->pokecoin_bonus = 0;
    pokemon_info->next_evolution = NULL;

    pokemon_info->name = stringCopy(name);
    if (pokemon_info->name == NULL) {
        free(pokemon_info);
        return NULL;
    }

    return pokemon_info;
}

PokemonInfo pokedexPokemonInfoCopy(PokemonInfo pokemon_info) {
    if (pokemon_info == NULL) return NULL;
    PokemonInfo new_pokemon_info = pokedexPokemonInfoCreate(pokemon_info->name,
                                                     pokemon_info->cp_initial);
    if (new_pokemon_info == NULL) return NULL;

    new_pokemon_info->pokecoin_bonus = pokemon_info->pokecoin_bonus;

    if (pokemon_info->next_evolution != NULL) {
        new_pokemon_info->next_evolution =
                stringCopy(pokemon_info->next_evolution);
        if (new_pokemon_info->next_evolution == NULL) {
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
        free(pokemon_info);
    }
}

PokedexResult pokedexUpdateNextEvolution(Pokedex pokedex, char* pokemon_name,
                                   char* next_evolution, int evolution_level) {
    if (pokedex == NULL || pokemon_name == NULL || next_evolution == NULL)
        return POKEDEX_NULL_ARG;
    if (evolution_level <= 0) return POKEDEX_IVALID_ARG;

    PokemonInfo pokemon_info = pokedexGetPokemonInfo(pokedex, pokemon_name);

    pokemon_info->next_evolution = stringCopy(next_evolution);
    if (pokemon_info->next_evolution == NULL)
        return POKEDEX_OUT_OF_MEMORY;

    pokemon_info->evolution_level = evolution_level;

    return POKEDEX_SUCCESS;
}


int pokedexPokemonInfoCompare(PokemonInfo pokemon_info1,
                                        PokemonInfo pokemon_info2) {
    assert(pokemon_info1 != NULL);
    assert(pokemon_info2 != NULL);

    return strcmp(pokemon_info1->name, pokemon_info2->name);
}



Pokedex pokedexCreate() {
    return setCreate(pokemonInfoCopyElement,pokemonInfoFreeElement,
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


char* pokedexGetNextEvolution(Pokedex pokedex, char* pokemon_name,
                              int pokemon_level) {
    assert(pokedex != NULL);
    assert(pokemon_name != NULL);

    PokemonInfo pokemon_info = pokedexGetPokemonInfo(pokedex, pokemon_name);
    int evolution_level = pokedexGetEvolutionLevel(pokedex, pokemon_name);

    if (pokemon_level >= evolution_level &&
            evolution_level != NO_NEXT_EVOLUTION) {
        char* next_evolution = pokedexGetNextEvolution(pokedex,
                                             pokemon_info->next_evolution,
                                             pokemon_level);
        return next_evolution;
    }

    return pokemon_name;
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

    return pokemon_info->pokecoin_bonus;
}

PokedexResult pokedexAddType(Pokedex pokedex, char* pokemon_name,
                             char* type_name) {
    PokemonInfo pokemon_info = pokedexGetPokemonInfo(pokedex, pokemon_name);

    if (pokemon_info->pokecoin_bonus < typeToBonus(type_name))
        pokemon_info->pokecoin_bonus = typeToBonus(type_name);

    return POKEDEX_SUCCESS;
}



