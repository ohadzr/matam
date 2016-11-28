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

/********************************
 *          Pokemon Funcs       *
 ********************************/

Pokemon pokemonCreate(char* name, PokemonType type, int experience,
                      int max_number_of_moves){
    Pokemon pokemon = NULL;
    if (name != NULL && strlen(name) != 0 \
        && isValidType(type) != POKEMON_INVALID_TYPE \
        && experience > 0 && experience <= 9901 && max_number_of_moves > 0) {

        pokemon = malloc(sizeof(*pokemon));
        if (pokemon != NULL) {
            createPokemonName(pokemon, name);
            pokemon->type = type;
            pokemon->experience = experience;
            pokemon->number_of_moves = NO_MOVES;
            pokemon->max_number_of_moves = max_number_of_moves;
            pokemonHeal(pokemon);
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
        free(pokemon->moves); // free moves pointer array
        free(pokemon); // free pokemon
    }
}

Pokemon pokemonCopy(Pokemon pokemon) {
    Pokemon new_pokemon = NULL;
    if (pokemon != NULL) {
        new_pokemon = malloc(sizeof(*new_pokemon));
        if (new_pokemon != NULL){
            createPokemonName(new_pokemon, pokemon->name);
            new_pokemon->type = pokemon->type;
            new_pokemon->health_points = pokemon->health_points;
            new_pokemon->experience = pokemon->experience;
            //TODO: copy moves
            new_pokemon->number_of_moves = pokemon->number_of_moves;
            new_pokemon->max_number_of_moves = pokemon->max_number_of_moves;
        }
    }
    return new_pokemon;
}


PokemonResult pokemonTeachMove(Pokemon pokemon, char* move_name,
                               PokemonType type, int max_power_points,
                               int strength){

}