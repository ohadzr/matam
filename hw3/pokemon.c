//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pokemon.h"


#define SAME_STRINGS 0
#define DEFAULT_LEVEL 1
#define DEFAULT_HP 100.0
#define DEFAULT_CP_BONUS 0
#define POKEMON_EQUAL 0
#define LEFT_POKEMON 1
#define RIGHT_POKEMON -1


/********************************
 * Helper Function Declarations *
 ********************************/


/**
* This function checks if given type is valid
*
* @return
*   bool - if valid return true, otherwise false
*/
static bool isValidType(PokemonType type);


/********************************
 *    Assistent Pokemon Funcs   *
 ********************************/


bool isValidType(PokemonType type) {
    bool is_valid = false;
    if (type == TYPE_NORMAL || type == TYPE_FIRE || type == TYPE_GRASS \
       || type == TYPE_WATER || type == TYPE_ELECTRIC || type == TYPE_BUG \
       || type == TYPE_ROCK || type == TYPE_FLYING || type == TYPE_GROUND \
       || type == TYPE_POISON || type == TYPE_FAIRY || type == TYPE_GHOST \
       || type == TYPE_ICE || type == TYPE_PSYCHIC) {
        is_valid = true;
    }
    return is_valid;
}




/********************************
 *          Pokemon Funcs       *
 ********************************/

Pokemon pokemonCreate(char* name) {
    Pokemon pokemon = NULL;
    if (name == NULL || strcmp(name,"")== SAME_STRINGS)
        return NULL;

    pokemon = malloc(sizeof(*pokemon));
    if (pokemon == NULL) return NULL;
    pokemon->cp = pokedexGetCP(name);
    pokemon->cp_bonus = DEFAULT_CP_BONUS;
    pokemon->level = DEFAULT_LEVEL;
    pokemon->hp = DEFAULT_HP;
    pokemon->name = stringCopy(name);

    if (pokemon->name == NULL) {
        pokemonDestroy(pokemon);
        return NULL;
    }

    return pokemon;
}

void pokemonDestroy(Pokemon pokemon) {
    if (pokemon != NULL) {
        free(pokemon->name);
        free(pokemon);
    }
}


Pokemon pokemonCopy(Pokemon pokemon) {
    if (pokemon == NULL) return NULL;
    Pokemon new_pokemon = NULL;
    new_pokemon = pokemonCreate(pokemon->name);
    if (new_pokemon != NULL) {
            new_pokemon->hp = pokemon->hp;
            new_pokemon->level = pokemon->level;
            new_pokemon->cp_bonus = pokemon->cp_bonus;
    }
    return new_pokemon;
}


int pokemonGetLevel(Pokemon pokemon) {
    assert(pokemon != NULL);
    return pokemon->level;
}

PokemonResult pokemonUpdateLevel(Pokemon pokemon, int added_value) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    if (added_value < 0)
        return POKEMON_INVALID_VALUE;
    pokemon->level += added_value;
    return POKEMON_SUCCESS;
}

int pokemonGetCP(Pokemon pokemon) {
    assert(pokemon != NULL);
    return pokemon->cp + pokemon->cp_bonus;
}

double pokemonGetHP(Pokemon pokemon) {
    assert(pokemon != NULL);
    return pokemon->hp;
}

PokemonResult pokemonUpdateHP(Pokemon pokemon, double value) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    pokemon->hp += value;
    if (pokemon->hp <= 0) {
        pokemon->hp = 0;
        return POKEMON_NO_HEALTH_POINTS;
    }
    if (pokemon->hp > DEFAULT_HP)
        pokemon->hp = DEFAULT_HP;
    return POKEMON_SUCCESS;
}

char* pokemonGetName(Pokemon pokemon) {
    assert(pokemon != NULL);
    return pokemon->name;
}


PokemonResult pokemonUseItem(Pokemon pokemon, Item item) {
    if (pokemon == NULL || item == NULL) return POKEMON_NULL_ARG;
    ItemType item_type = itemGetType(item);
    int value = itemGetValue(item);

    if (item_type == TYPE_POTION) {
        pokemonUpdateHP(pokemon, value);
    }
    if (item_type == TYPE_CANDY) {
        pokemon->cp_bonus += value;
    }
    return POKEMON_SUCCESS;
}

int pokemonCompare(Pokemon first_pokemon, Pokemon second_pokemon) {
    assert(first_pokemon != NULL);
    assert(second_pokemon != NULL);

    if (first_pokemon->id == second_pokemon->id)
        return POKEMON_EQUAL;

    if (first_pokemon->id < second_pokemon->id)
        return LEFT_POKEMON;

    return RIGHT_POKEMON;
}

PokemonResult pokemonCheckEvolution(Pokemon pokemon) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;

    int new_cp = pokemon->cp;
    char* next_evolution = pokedexFindNextEvolution(pokemon); //TODO: return the last evolution (A>B , B>C) will return C

    if (next_evolution == NULL) return POKEMON_CANT_EVOLVE;

    new_cp = pokedexGetCP(next_evolution);
    stringDestroy(pokemon->name);

    pokemon->cp = new_cp;
    pokemon->name = stringCopy(next_evolution);

    if (pokemon->name == NULL) return POKEMON_OUT_OF_MEMORY;

    return POKEMON_SUCCESS;
}




PokemonResult pokemonUpdateID(Pokemon pokemon, int new_id) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    pokemon->id = new_id;
    return POKEMON_SUCCESS;
}

int pokemonGetID(Pokemon pokemon) {
    assert(pokemon != NULL);
    return pokemon->id;
}


PokemonElement pokemonCopyElement( PokemonElement pokemon ) {
    return pokemonCopy( (Pokemon)pokemon );
}

void pokemonFreeElement( PokemonElement pokemon ) {
    pokemonDestroy( (Pokemon)pokemon );
}
