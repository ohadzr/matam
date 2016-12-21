//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include "pokemon_trainer.h"


#define SAME_STRINGS 0
#define DEFUALT_XP 1.0
#define NO_BUDGET 0
#define NO_POKEMONS 0


/********************************
 * Helper Function Declarations *
 ********************************/

/**
* This function allocate new memory for given pokemon name / move name
* then copy (deep copy) the name into the pokemon / move
* Name must not be NULL or empty string
*
*
* @return
*   chr* - return the pointer of name if success, otherwise NULL
*/
static char* createName(char* name);


/****************************************
 *    Assistent Pokemon Trainer Funcs   *
 ****************************************/

char* createName(char* name) { //TODO: should this function be in utils.c?
    char* dst_name = malloc(strlen(name)+1);
    if (dst_name != NULL) {
        strcpy(dst_name, name);
        dst_name[strlen(name)] = '\0';
        return dst_name;
    }
    return NULL;
}


/********************************
 *    Pokemon Trainer Funcs     *
 ********************************/

PokemonTrainer pokemonTrainerCreate(char* name, char* location, int budget) {
    if (name == NULL || strcmp(name,"") == SAME_STRINGS ||
        location == NULL || strcmp(location,"") == SAME_STRINGS ||
        budget < NO_BUDGET)
        return NULL;

    PokemonTrainer trainer = malloc(sizeof(*trainer));
    if (trainer == NULL) return NULL;

    trainer->xp = DEFUALT_XP;
    trainer->pokecoins = budget;
    trainer->number_of_caught_pokemons = NO_POKEMONS;
    trainer->name = createName(name);
    trainer->location = createName(location);
    trainer->pokemon_set = setCreate((SetElement) pokemonCopy,     // TODO: should this in an aux function? *void / **void ?
                          (freeSetElements) pokemonDestroy,
                          (compareSetElements) pokemonCompare);
    trainer->item_set = setCreate((SetElement) itemCopy,
                          (freeSetElements) itemDestroy,
                          (compareSetElements) itemCompare);

    if (trainer->name == NULL || trainer->location == NULL || \
        trainer->pokemon_set == NULL || trainer->item_set == NULL) {
        pokemonTrainerDestroy(trainer);
        return NULL;
    }

    return trainer;
}


void pokemonTrainerDestroy(PokemonTrainer trainer) {
    if (trainer != NULL) {
        free(trainer->name);
        free(trainer->location);

        setDestroy(trainer->item_set);
        setDestroy(trainer->pokemon_set);

        free(trainer);
    }
}


PokemonTrainer pokemonTrainerCopy(PokemonTrainer trainer) {
    if (trainer == NULL) return NULL;
    PokemonTrainer new_trainer = pokemonTrainerCreate(trainer->name,
                                                      trainer->location,
                                                      trainer->pokecoins);
    if (new_trainer == NULL) return NULL;

    new_trainer->pokemon_set = setCopy(trainer->pokemon_set);
    if (new_trainer->pokemon_set == NULL && trainer->pokemon_set != NULL) {
        pokemonTrainerDestroy(new_trainer);
        return NULL;
    }

    new_trainer->item_set = setCopy(trainer->item_set);
    if (new_trainer->item_set == NULL && trainer->item_set != NULL) {
        pokemonTrainerDestroy(new_trainer);
        return NULL;
    }

    new_trainer->number_of_caught_pokemons = trainer->number_of_caught_pokemons;
    new_trainer->xp = trainer->xp;

    return new_trainer;
}

PokemonTrainerResult pokemonTrainerAddPokemon(PokemonTrainer trainer,
                                              Pokemon pokemon) {
    if (trainer == NULL || pokemon == NULL) return POKEMON_TRAINER_NULL_ARG;

    Pokemon new_pokemon = pokemonCopy(pokemon);
    if (new_pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEM;

    pokemonUpdateID(new_pokemon, trainer->number_of_caught_pokemons + 1);

    SetResult result = setAdd(trainer->pokemon_set, new_pokemon);

    if (result == SET_OUT_OF_MEMORY) { //TODO: should I delete trainer? pokemonGO.c should?
        return POKEMON_TRAINER_OUT_OF_MEM;
    }

    return POKEMON_TRAINER_SUCCESS;
}


PokemonTrainerResult pokemonTrainerAddItem(PokemonTrainer trainer, //TODO: dup with pokemonTrainerAddPokemon function.. should be GDT
                                              Item item) {
    if (trainer == NULL || item == NULL) return POKEMON_TRAINER_NULL_ARG;

    SetResult result = setAdd(trainer->item_set, item);

    if (result == SET_OUT_OF_MEMORY) { //TODO: should I delete trainer? pokemonGO.c should?
        return POKEMON_TRAINER_OUT_OF_MEM;
    }

    return POKEMON_TRAINER_SUCCESS;
}


Pokemon pokemonTrainerGetPokemon(PokemonTrainer trainer, int pokemon_id) {
    if (trainer == NULL) return NULL;

    Pokemon pokemon = NULL;

    SET_FOREACH(Pokemon, pokemon_iter, trainer->pokemon_set) {
        if (pokemonGetID(pokemon_iter) == pokemon_id) {
            pokemon = pokemon_iter;
        }
    }

    return pokemon;
}


PokemonTrainerResult pokemonTrainerBuyItem(PokemonTrainer trainer, Item item,
                                            Store store) { //TODO: should get item or char* & value?
    if (trainer == NULL || item == NULL) return POKEMON_TRAINER_NULL_ARG;

    int price = itemGetPrice(item);
    if (trainer->pokecoins < price) return POKEMON_TRAINER_INSUFFICIENT_BUDGET;

    getItemFromStore(store, item); //TODO: continue from here.. need to think how to implement this

    return POKEMON_TRAINER_SUCCESS;
}
