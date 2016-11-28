//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pokemon.h"


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
 *     Pokemon Funcs      *
 ********************************/


/*void freeMoves(PokemonMove ptr) {
    if (ptr != NULL) {
        while (ptr) {
            PokemonMove to_delete = ptr;
            ptr = ptr->next;
            free(to_delete);
        }
    }
}*/

bool isValidType(PokemonType type) {
    bool is_valid = false;
    if (type == TYPE_NORMAL || type == TYPE_FIRE || type == TYPE_GRASS \
       || type == TYPE_WATER || type == TYPE_ELECTRIC) {
        is_valid = true;
    }
    return is_valid;
}


Pokemon pokemonCreate(char* name, PokemonType type, int experience,
                      int max_number_of_moves){
    Pokemon pokemon = NULL;
    if (name != NULL && strlen(name) != 0 \
        && isValidType(type) != POKEMON_INVALID_TYPE \
        && experience > 0 && experience <= 9901 && max_number_of_moves > 0) {

        pokemon = malloc(sizeof(*pokemon));
        if (pokemon != NULL) {
            pokemon->name = name;
            pokemon->type = type;
            pokemon->experience = experience;
            pokemon->max_number_of_moves = max_number_of_moves;
            pokemonHeal(pokemon);
        }
    }
    return pokemon;
}

void pokemonDestroy(Pokemon pokemon) {
    if (pokemon != NULL) {
        // TODO: free moves and name
        free(pokemon);
    }
}