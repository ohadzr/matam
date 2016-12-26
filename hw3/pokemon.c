//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pokemon.h"

/********************************
 *          Defines             *
 ********************************/

#define SAME_STRINGS 0
#define DEFAULT_LEVEL 1
#define DEFAULT_HP 100.0
#define DEFAULT_CP_BONUS 0


/********************************
 *          Pokemon Funcs       *
 ********************************/

Pokemon pokemonCreate(char* name, Pokedex pokedex) {
    Pokemon pokemon = NULL;
    if (name == NULL || strcmp(name,"")== SAME_STRINGS || pokedex == NULL)
        return NULL;

    pokemon = malloc(sizeof(*pokemon));
    if (pokemon == NULL) return NULL;
    pokemon->cp = pokedexGetInitialCP(pokedex, name);
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
    Pokemon new_pokemon = malloc(sizeof(*pokemon));

    if (new_pokemon != NULL) {
            new_pokemon->hp = pokemon->hp;
            new_pokemon->level = pokemon->level;
            new_pokemon->cp_bonus = pokemon->cp_bonus;
            new_pokemon->cp = pokemon->cp;
            new_pokemon->id = pokemon->id;
            new_pokemon->name = stringCopy(pokemon->name);
            if (new_pokemon->name == NULL) {
                pokemonDestroy(new_pokemon);
                return NULL;
            }
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

PokemonResult pokemonCompare(Pokemon first_pokemon, Pokemon second_pokemon) {
    if (first_pokemon == NULL || second_pokemon == NULL)
        return POKEMON_NULL_ARG;

    if (first_pokemon->id == second_pokemon->id)
        return POKEMON_EQUAL;

    return POKEMON_DIFFERENT;
}

PokemonResult pokemonCheckEvolution(Pokemon pokemon, Pokedex pokedex) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;

    char* next_evolution = pokedexGetNextEvolution(pokedex, pokemon->name,
                                                   pokemon->level);

    if (strcmp(next_evolution, pokemon->name) == SAME_STRINGS)
        return POKEMON_CANT_EVOLVE;

    int new_cp = pokedexGetInitialCP(pokedex, next_evolution);
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


PokemonElement pokemonCopyElement(PokemonElement pokemon) {
    return pokemonCopy((Pokemon)pokemon);
}

void pokemonFreeElement(PokemonElement pokemon) {
    pokemonDestroy((Pokemon)pokemon);
}
