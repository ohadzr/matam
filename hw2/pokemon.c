//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pokemon.h"


#define NO_MOVES 0
#define SAME_STRINGS 0
#define LEVEL_PARAMETER 100
#define NORMAL_FACTOR 1
#define BIG_FACTOR 2
#define MAX_EXPERIENCE_POINTS 9901
#define NO_HEALTH_POINTS 0

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

// TODO: shouldn't be static? same function in pokemon_trainer.c
/**
* This function allocate new memory for given pokemon name / move name
* then copy (deep copy) the name into the pokemon / move
*
*
* @return
*   chr* - return the pointer of name if success, otherwise NULL
*/
static char* createName(char* name);

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
*   int* - return to a given pointer the index of the move
*/
static bool doesPokemonMoveExists(Pokemon pokemon, char* move_name,
                                  int* move_index);

/**
* This function find the index of the move that should be removed
* the removed move should be the first one lexicoraphic
*
*
* @return
*   int - the index of the move that should be removed
*/
static int findMoveIndexToUnteach(Pokemon pokemon);


/**
* This function checks the validation of the given parameters to
* pokemonTeachMove function
*
*
*
* @return
*   PokemonResult - result if found a result, otherwise NULL
*/
static PokemonResult checkMoveValidation(Pokemon pokemon, char* move_name,
                                        PokemonType type, int max_power_points,
                                        int strength);


/**
* This function checks if a big factor is supposed be to
* an attacking move
*
* @return
*   int - BIG_FACTOR or NORMAL_FACTOR
*/
static int pokemonGetFactor(PokemonType move_type, PokemonType opponent_type);

/**
* This function raise the experience points of a pokemon by the given points.
* A pokemon can't have more than MAX_EXPERIENCE_POINTS so if experience
* are more than MAX_EXPERIENCE_POINTS they become MAX_EXPERIENCE_POINTS
*
*/
static void raisePokemonExperience(Pokemon pokemon, int extra_experience);


/**
* This function checks if a character is a valid letter or not
*
* @return
*   bool - true if letter, otherwise false
*/
static bool isLetter(char letter);


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

char* createName(char* name) {
    char* dst_name = malloc(sizeof(*name)+1);
    if (dst_name != NULL) {
        strcpy(dst_name, name);
        dst_name[strlen(name)] = '\0';
        return dst_name;
    }
    return NULL;
}


void destroyPokemonMove(Pokemon pokemon, int move_index) {
    if (pokemon != NULL) {
        free(pokemon->moves[move_index]->name);
        free(pokemon->moves[move_index]);
    }
}

bool doesPokemonMoveExists(Pokemon pokemon, char* move_name, int* move_index) {
    int result;
    for (int i=0; i<pokemon->number_of_moves ; i++) {
        result = strcmp(pokemon->moves[i]->name, move_name);
        if (result == SAME_STRINGS) {
            *move_index = i;
            return true;
        }
    }
    return false;
}


int findMoveIndexToUnteach(Pokemon pokemon) {
    int max_index=0, result;
    for (int i=1; i<pokemon->number_of_moves; i++) {
        result = strcmp(pokemon->moves[max_index]->name, \
                        pokemon->moves[i]->name);
        if (result > 0) max_index=i; //second name is less lexicographic
    }
    return max_index;
}


PokemonResult checkMoveValidation(Pokemon pokemon, char* move_name,
                                  PokemonType type, int max_power_points,
                                  int strength) {
    int move_index;
    if (pokemon == NULL || move_name == NULL) return POKEMON_NULL_ARG;
    if (strcmp(move_name,"") == SAME_STRINGS)
        return POKEMON_INVALID_MOVE_NAME;
    if (!isValidType(type)) return POKEMON_INVALID_TYPE;
    if (max_power_points <= 0) return POKEMON_INVALID_POWER_POINTS;
    if (strength <= 0) return POKEMON_INVALID_STRENGTH;
    if (type != TYPE_NORMAL && type != pokemon->type)
        return POKEMON_INCOMPATIBLE_MOVE_TYPE;
    if (doesPokemonMoveExists(pokemon,move_name, &move_index))
        return POKEMON_MOVE_ALREADY_EXISTS;
    return POKEMON_SUCCESS;
}


int pokemonGetFactor(PokemonType move_type, PokemonType opponent_type) {
    if ((move_type == TYPE_WATER && opponent_type == TYPE_FIRE) || \
        (move_type == TYPE_FIRE && opponent_type == TYPE_GRASS) || \
        (move_type == TYPE_GRASS && opponent_type == TYPE_WATER) || \
        (move_type == TYPE_ELECTRIC && opponent_type == TYPE_WATER))
        return BIG_FACTOR;

    return NORMAL_FACTOR;
}


void raisePokemonExperience(Pokemon pokemon, int extra_experience) {
    int experience = pokemon->experience;
    experience += extra_experience;
    if (experience > MAX_EXPERIENCE_POINTS){
        experience = MAX_EXPERIENCE_POINTS;
    }
    pokemon->experience = experience;
}


bool isLetter(char letter) {
    if ((letter > 'a' && letter < 'z') ||
        (letter > 'A' && letter < 'Z')) {
        return true;
    }
    return false;
}


/********************************
 *          Pokemon Funcs       *
 ********************************/

Pokemon pokemonCreate(char* name, PokemonType type, int experience,
                      int max_number_of_moves){
    Pokemon pokemon = NULL;
    if (name == NULL || strcmp(name,"") == SAME_STRINGS \
        || isValidType(type) == POKEMON_INVALID_TYPE \
        || experience <= 0 || experience > MAX_EXPERIENCE_POINTS \
        || max_number_of_moves <= 0) {
        return NULL;
    }
    pokemon = malloc(sizeof(*pokemon));
    if (pokemon == NULL) return NULL;

    pokemon->type = type;
    pokemon->experience = experience;
    pokemon->number_of_moves = NO_MOVES;
    pokemon->max_number_of_moves = max_number_of_moves;
    pokemonHeal(pokemon);
    pokemon->moves =
            malloc(sizeof(*(pokemon->moves))*max_number_of_moves); //TODO: ask if this is correct
    if (pokemon->moves == NULL) {
        free(pokemon);
        return NULL;
    }
    pokemon->name = createName(name);
    if (pokemon->name == NULL) {
        free(pokemon->moves);
        free(pokemon);
        return NULL;
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


Pokemon pokemonCopy(Pokemon pokemon) {
    if (pokemon == NULL) return NULL;
    Pokemon new_pokemon = NULL;
    new_pokemon = pokemonCreate(pokemon->name, pokemon->type, \
                    pokemon->experience, pokemon->max_number_of_moves);
    if (new_pokemon != NULL) {
            new_pokemon->health_points = pokemon->health_points;
            for (int i=0 ; i<pokemon->number_of_moves; i++) {
                PokemonResult result = pokemonTeachMove(new_pokemon,
                                 pokemon->moves[i]->name,
                                 pokemon->moves[i]->type,
                                 pokemon->moves[i]->max_power_points,
                                 pokemon->moves[i]->strength);
                if (result != POKEMON_SUCCESS) {
                    pokemonDestroy(pokemon);
                    return NULL;
                }
                new_pokemon->moves[i]->power_points = \
                                    pokemon->moves[i]->power_points;
            }
    }
    return new_pokemon;
}


PokemonResult pokemonTeachMove(Pokemon pokemon, char* move_name,
                               PokemonType type, int max_power_points,
                               int strength) {
    PokemonResult result = checkMoveValidation(pokemon, move_name, type,
                                               max_power_points,strength);
    if (result != POKEMON_SUCCESS) return result;

    PokemonMove move = malloc(sizeof(*move));
    if (move == NULL) return POKEMON_OUT_OF_MEM;

    move->type = type;
    move->max_power_points = max_power_points;
    move->power_points = max_power_points;
    move->strength = strength;

    move->name = createName(move_name);
    if (move->name == NULL) {
        free(move);
        return POKEMON_OUT_OF_MEM;
    }
    if (pokemon->number_of_moves < pokemon->max_number_of_moves) {
        pokemon->moves[pokemon->number_of_moves] = move;
        pokemon->number_of_moves++;
    }
    else {
        int move_index = findMoveIndexToUnteach(pokemon);
        pokemonUnteachMove(pokemon, pokemon->moves[move_index]->name);
        pokemon->moves[move_index] = move;
    }
    return POKEMON_SUCCESS;
}

PokemonResult pokemonUnteachMove(Pokemon pokemon, char *move_name) {
    int move_index;
    if (pokemon == NULL || move_name == NULL)
        return POKEMON_NULL_ARG;
    if (strcmp(move_name, "") == 0)
        return POKEMON_INVALID_MOVE_NAME;
    if (!doesPokemonMoveExists(pokemon,move_name,&move_index))
        return POKEMON_MOVE_DOES_NOT_EXIST;

    free(pokemon->moves[move_index]->name);
    free(pokemon->moves[move_index]);

    // fix moves indexes
    int i=move_index;
    for ( ; i < pokemon->number_of_moves-1; i++){
        pokemon->moves[i] = pokemon->moves[i+1];
    }
    //pokemon->moves[i] = NULL; // remove duplicate pointer NOT freeing move TODO:should I remove duplicated pointer?
    pokemon->number_of_moves--;
    return POKEMON_SUCCESS;
}


int pokemonGetLevel(Pokemon pokemon) {
    assert(pokemon != NULL);
    int level;
    level = (pokemon->experience) / LEVEL_PARAMETER;
    if ((pokemon->experience % LEVEL_PARAMETER) > 0) level++;
    return level;
}

int pokemonGetRank(Pokemon pokemon) {
    assert(pokemon != NULL);
    int rank = pokemonGetLevel(pokemon);
    int average_move_strength=0;
    for (int i=0 ; i<pokemon->number_of_moves; i++) {
        average_move_strength += pokemon->moves[i]->strength;
    }
    if (pokemon->number_of_moves == 0)
        return 0;

    average_move_strength = average_move_strength/pokemon->number_of_moves;

    return rank + average_move_strength;
}


PokemonResult pokemonUseMove(Pokemon pokemon, Pokemon opponent_pokemon,
                             char* move_name) {
    int move_index;
    if (pokemon == NULL || opponent_pokemon == NULL || move_name == NULL)
        return POKEMON_NULL_ARG;
    if (strcmp(move_name,"") == SAME_STRINGS) return POKEMON_INVALID_MOVE_NAME;
    if (!doesPokemonMoveExists(pokemon,move_name,&move_index))
        return POKEMON_MOVE_DOES_NOT_EXIST;
    if (pokemon->moves[move_index]->power_points == 0)
        return POKEMON_NO_POWER_POINTS;
    if (pokemon->health_points == 0 || opponent_pokemon->health_points == 0)
        return POKEMON_NO_HEALTH_POINTS;

    int attacker_level = pokemonGetLevel(pokemon);
    int factor = pokemonGetFactor(pokemon->moves[move_index]->type,
                                  opponent_pokemon->type);
    int extra_experience = opponent_pokemon->health_points;

    opponent_pokemon->health_points -=
            factor*(attacker_level*2 + pokemon->moves[move_index]->strength); //TODO: should be macro?
    if (opponent_pokemon->health_points < NO_HEALTH_POINTS) {
        opponent_pokemon->health_points = NO_HEALTH_POINTS;
    }

    pokemon->moves[move_index]->power_points--;
    extra_experience -= opponent_pokemon->health_points;
    raisePokemonExperience(pokemon, extra_experience);
    return POKEMON_SUCCESS;
}


PokemonResult pokemonHeal(Pokemon pokemon) {
    if (pokemon == NULL) return POKEMON_NULL_ARG;
    int level = pokemonGetLevel(pokemon);
    pokemon->health_points = (100 + level)*10; //TODO: should be macro?

    for (int i=0; i<pokemon->number_of_moves; i++) {
        pokemon->moves[i]->power_points = pokemon->moves[i]->max_power_points;
    }
    return POKEMON_SUCCESS;
}


PokemonResult pokemonEvolve(Pokemon pokemon, char* new_name) {
    if (pokemon == NULL || new_name == NULL) return POKEMON_NULL_ARG;
    if (strcmp(new_name,"") == SAME_STRINGS) return POKEMON_INVALID_NAME;
    if (pokemon->experience == MAX_EXPERIENCE_POINTS)
        return POKEMON_CANNOT_EVOLVE;

    free(pokemon->name);
    pokemon->name = createName(new_name);
    if(pokemon->name == NULL) return POKEMON_OUT_OF_MEM;

    int experience = (pokemonGetLevel(pokemon)*LEVEL_PARAMETER)+1; //TODO: should be a macro?
    pokemon->experience = experience;

    return POKEMON_SUCCESS;
}


PokemonResult pokemonPrintName(Pokemon pokemon, FILE* file) {
    if (pokemon == NULL || file == NULL) return POKEMON_NULL_ARG;
    fprintf(file, pokemon->name);
    return POKEMON_SUCCESS;
}


PokemonResult pokemonPrintVoice(Pokemon pokemon, FILE* file) {
    if (pokemon == NULL || file == NULL) return POKEMON_NULL_ARG;

    char* pokemon_voice = malloc(sizeof(char)*strlen(pokemon->name));
    if (pokemon_voice == NULL) return POKEMON_OUT_OF_MEM;
    int pokemon_name_size=0, index=0;

    while(pokemon->name[index] != '\0') {
        if (isLetter(pokemon->name[index])) {
            pokemon_voice[pokemon_name_size] = pokemon->name[index];
            pokemon_name_size++;
        }
        index++;
    }

    int half_pokemon_name_size = (pokemon_name_size/2) + (pokemon_name_size%2);

    pokemon_voice[half_pokemon_name_size] = '\0';
    fprintf(file, "%s",pokemon_voice);
    fprintf(file, "-");
    fprintf(file, "%s",pokemon_voice);

    free(pokemon_voice);

    return POKEMON_SUCCESS;
}