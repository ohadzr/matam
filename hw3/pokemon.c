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


/********************************
 * Helper Function Declarations *
 ********************************/


/**
* This function allocate new memory for given pokemon name / move name
* then copy (deep copy) the name into the pokemon / move
* Name must not be NULL or empty string
*
* @return
*   chr* - return the pointer of name if success, otherwise NULL
*/
static char* createName(char* name);

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


char* createName(char* name) { //TODO: should this function be in utils.c? what is utils?
    char* dst_name = malloc(strlen(name)+1);
    if (dst_name != NULL) {
        strcpy(dst_name, name);
        dst_name[strlen(name)] = '\0';
        return dst_name;
    }
    return NULL;
}

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

Pokemon pokemonCreate(char* name, PokemonType type, int cp) {
    Pokemon pokemon = NULL;
    if (name == NULL || strcmp(name,"")== SAME_STRINGS || cp <=0)
        return NULL;
    if (!isValidType(type)) return NULL;

    pokemon = malloc(sizeof(*pokemon));
    if (pokemon == NULL) return NULL;

    pokemon->type = type;
    pokemon->cp = cp; //TODO: get this from pokedex! // agree
    pokemon->cp_bonus = DEFAULT_CP_BONUS;
    pokemon->level = DEFAULT_LEVEL;
    pokemon->hp = DEFAULT_HP;
    //pokemon->next_pokemon = NULL; //TODO:remove this // agree
    pokemon->name = createName(name);

    if (pokemon->name == NULL) {
        free(pokemon);
        return NULL;
    }

    return pokemon;
}

void pokemonDestroy(Pokemon pokemon) {
    if (pokemon != NULL) {
        free(pokemon->name);
        //if (pokemon->next_pokemon != NULL) //TODO: remove this
        //    free(pokemon->next_pokemon);
        free(pokemon);
    }
}


Pokemon pokemonCopy(Pokemon pokemon) {
    if (pokemon == NULL) return NULL;
    Pokemon new_pokemon = NULL;
    new_pokemon = pokemonCreate(pokemon->name,pokemon->type,pokemon->cp);
    if (new_pokemon != NULL) {
            new_pokemon->hp = pokemon->hp;
            new_pokemon->level = pokemon->level;
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

PokemonResult pokemonUpdateHP(Pokemon pokemon, int value) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    pokemon->hp += value;
    if (pokemon->hp <= 0) {
        pokemon->hp = 0; //TODO: should I destroy pokemon or trainer? do separate function of destroy pokemon and destroy trainer
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


PokemonResult pokemonUseItem(Pokemon pokemon, Item item) { // TODO: does this function need a different implementation? (not using Item but only bools)
    if (pokemon == NULL || item == NULL) return POKEMON_NULL_ARG;
    ItemType item_type = itemGetType(item); //TODO: should be here? //why not? how else a dedicated func?
    int value = itemGetValue(item);

    if (item_type == TYPE_POTION) { //TODO: can I use this enum? yes if you do include to store.h
        pokemonUpdateHP(pokemon, value);
    }
    if (item_type == TYPE_CANDY) {
        pokemon->cp_bonus += value;
    }
    return POKEMON_SUCCESS;
}

PokemonResult pokemonCompare(Pokemon first_pokemon, Pokemon second_pokemon) { //TODO: change in tests -?don't understand
    if (first_pokemon == NULL || second_pokemon == NULL)
        return POKEMON_NULL_ARG;

    if (first_pokemon->id == second_pokemon->id)
        return POKEMON_EQUAL;

    return POKEMON_DIFFERENT;
}

/* TODO: remove this when pokedex is implemented
PokemonResult pokemonCheckEvolution(Pokemon pokemon) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    char* next_evolution = NULL;
    int new_cp = pokemon->cp;
    PokedexResult result = pokedexCheckNextEvolution(pokemon); //TODO: add pokedex function
    if (result == POKEDEX_POKEMON_EVOLVE) {
        next_evolution = pokedexGetNextEvolutionName(pokemon);
        new_cp = pokedexGetNextEvolutionCP(pokemon);
        if (next_evolution == NULL) return POKEMON_CANT_EVOLVE;
    }

    if (next_evolution != NULL) {
        free(pokemon->name);
        pokemon->name = createName(next_evolution);
    }
    if (pokemon->name == NULL) return POKEMON_OUT_OF_MEM;

    pokemon->cp = new_cp;
    return POKEMON_SUCCESS;
}

 */


PokemonResult pokemonUpdateID(Pokemon pokemon, int new_id) { //TODO: add to tests -> to think who is giving pokemon the id trainer/ pokadex?
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    pokemon->id = new_id;
    return POKEMON_SUCCESS;
}

int pokemonGetID(Pokemon pokemon) {
    assert(pokemon != NULL);
    return pokemon->id;
}


//TODO: remove this:

/*
Pokemon pokemonGetNextPokemon(Pokemon pokemon) {
    assert(pokemon != NULL);
    return pokemon->next_pokemon;
}


PokemonResult pokemonUpdateNextPokemon(Pokemon pokemon, Pokemon next_pokemon) { //TODO: add to tests
    if (pokemon == NULL || next_pokemon == NULL)
        return POKEMON_NULL_ARG;

    pokemon->next_pokemon = next_pokemon;

    return POKEMON_SUCCESS

}




PokemonResult pokemonRemovePokemonFromList(Pokemon first_pokemon,
                                           Pokemon pokemon_to_remove) {
    Pokemon
}

 */
