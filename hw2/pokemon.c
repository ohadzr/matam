//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pokemon.h"


#define NO_MOVES 0

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

/**
* This function allocate new memory for given pokemon name
* then copy (deep copy) the name into the pokemon
*
* @return
*   bool - return true if allocation successed, otherwise false
*/
static bool createPokemonName(Pokemon pokemon, char* name);

/**
* This function free the memory of a pokemon move (it's name
* and move itself) by a given index
*
*/
static void destroyPokemonMove(Pokemon pokemon, int move_index);


/**
* This function check if a pokemon already has move
*
* @return
*   bool - return true if move exists, otherwise false
*/
static bool doesPokemonMoveExists(Pokemon pokemon, char* move_name);

/**
* This function allocate new memory for given pokemon move
* then copy (deep copy) the name into the pokemon
*
* @return
*   bool - return true if allocation successed, otherwise false
*/
static bool createPokemonMove(Pokemon pokemon, char* name);


/********************************
 *    Assistent Pokemon Funcs   *
 ********************************/

bool isValidType(PokemonType type) {
    bool is_valid = false;
    if (type == TYPE_NORMAL || type == TYPE_FIRE || type == TYPE_GRASS \
       || type == TYPE_WATER || type == TYPE_ELECTRIC) {
        is_valid = true;
    }
    return is_valid;
}

bool createPokemonName(Pokemon pokemon, char* name){
    if (pokemon != NULL) {
        pokemon->name = malloc(sizeof(*name)+1);
        if (pokemon->name != NULL) {
            strcpy(pokemon->name, name);
            pokemon->name[sizeof(*name)] = '\0';
            return true;
        }

    }
    return false;
}



void destroyPokemonMove(Pokemon pokemon, int move_index) {
    if (pokemon != NULL) {
        free(pokemon->moves[move_index]->name);
        free(pokemon->moves[move_index]);
    }
}

bool doesPokemonMoveExists(Pokemon pokemon, char* move_name) {
    int result;
    for (int i=0; i<pokemon->number_of_moves ; i++) {
        result = strcmp(pokemon->moves[i]->name, move_name);
        if (result==0) { // same name
            return true;
        }
    }
    return false;
}

/********************************
 *          Pokemon Funcs       *
 ********************************/

Pokemon pokemonCreate(char* name, PokemonType type, int experience,
                      int max_number_of_moves){
    Pokemon pokemon = NULL;
    bool allocate_successfully;
    if (name != NULL && strlen(name) != 0 \
        && isValidType(type) != POKEMON_INVALID_TYPE \
        && experience > 0 && experience <= 9901 && max_number_of_moves > 0) {

        pokemon = malloc(sizeof(*pokemon));
        if (pokemon != NULL) {
            pokemon->type = type;
            pokemon->experience = experience;
            pokemon->number_of_moves = NO_MOVES;
            pokemon->max_number_of_moves = max_number_of_moves;
            pokemonHeal(pokemon);
            pokemon->moves =
                    malloc(sizeof(*(pokemon->moves))*max_number_of_moves); //TODO: ask if this is correct
            if (pokemon->moves == NULL) return NULL;
            allocate_successfully = createPokemonName(pokemon, name);
            if (!allocate_successfully){
                pokemonDestroy(pokemon);
                return NULL;
            }
        }
    }
    return pokemon;
}

void pokemonDestroy(Pokemon pokemon) {
    if (pokemon != NULL) {
        free(pokemon->name); // free name
        // free moves
        for (int i = pokemon->number_of_moves-1; i >= 0 ; i--) {
            destroyPokemonMove(pokemon,i);
        }
        free(pokemon->moves); // free moves pointer array TODO: ask if this is correct
        free(pokemon); // free pokemon
    }
}

// TODO: check if can be replaced with pokemonCreate()
Pokemon pokemonCopy(Pokemon pokemon) {
    Pokemon new_pokemon = NULL;
    bool allocate_successfully;
    if (pokemon != NULL) {
        new_pokemon = malloc(sizeof(*new_pokemon));
        if (new_pokemon != NULL) {
            new_pokemon->type = pokemon->type;
            new_pokemon->health_points = pokemon->health_points;
            new_pokemon->experience = pokemon->experience;
            new_pokemon->number_of_moves = NO_MOVES;
            new_pokemon->max_number_of_moves = pokemon->max_number_of_moves;
            allocate_successfully =
                            createPokemonName(new_pokemon, pokemon->name);
            if (!allocate_successfully){
                free(new_pokemon);
                return NULL;
            }

            for (int i=0 ; i<pokemon->number_of_moves; i++) {
                pokemonTeachMove(new_pokemon,
                                 pokemon->moves[i]->name,
                                 pokemon->moves[i]->type,
                                 pokemon->moves[i]->max_power_points,
                                 pokemon->moves[i]->strength);
            }
            //TODO: copy moves
        }
    }
    return new_pokemon;
}


PokemonResult pokemonTeachMove(Pokemon pokemon, char* move_name,
                               PokemonType type, int max_power_points,
                               int strength){
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    if (move_name == NULL || move_name == "") return POKEMON_INVALID_MOVE_NAME;
    if (!isValidType(type)) return POKEMON_INVALID_TYPE;
    if (max_power_points <= 0) return POKEMON_INVALID_POWER_POINTS;
    if (strength <= 0) return POKEMON_INVALID_STRENGTH;
    if (type != TYPE_NORMAL && type != pokemon->type) {
        return POKEMON_INCOMPATIBLE_MOVE_TYPE;
    }
    if (doesPokemonMoveExists(move_name)) return POKEMON_MOVE_ALREADY_EXISTS;
    // TODO:finish this function

}