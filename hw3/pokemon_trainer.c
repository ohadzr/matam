//
// Created by ohad on 27-Nov-16.
//

#include <stdlib.h>
#include <string.h>
#include "pokemon_trainer.h"


#define SAME_STRINGS 0
#define DEFUALT_XP 1.0
#define DEFAULT_HP 100.0
#define NO_BUDGET 0
#define NO_POKEMONS 0
#define NO_MAX_VALUE -1
#define CALC_DELTA(xp, cp ,hp)    ((xp)*(cp)*(1+(hp/200)))
//if doesn't devide by 4 add 1:
#define CALC_LEVEL_BONUS(level1, level2)    (((level1)+(level2))%4) ?   \
                                            (((level1)+(level2)+4)/4) : \
                                            (((level1)+(level2))/4)
#define CALC_XP_BONUS(delta)    ((delta)/10)


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

/**
* This function gather all the inforamation needed to @pokemonTrainerFight
* And calculate all battle numbers. It also update the trainers with new XP
* And pokemons with new HP, CP and Level.
*
* @return
*   values to the pointers of current pokemon's HP, CP, level trainer XP
*/
static void pokemonTrainerFightAux(PokemonTrainer trainer1, Pokemon pokemon1,
                                   PokemonTrainer trainer2, Pokemon pokemon2,
                                   int* old_cp1, double* old_hp1,
                                   int* old_level1, double* old_xp1,
                                   bool* is_dead1, int* old_cp2,
                                   double* old_hp2, int* old_level2,
                                   double* old_xp2, bool* is_dead2);

/**
* Finds the item with the highest value the trainer has by given item type.
*
* @return
*   int - Highest value of item the trainer has (of given type)
*   NO_MAX_VALUE - if no item found (set to -1)
*/
static int pokemonTrainerGetMaxValueItem(PokemonTrainer trainer,
                                         ItemType item_type);


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


void pokemonTrainerFightAux(PokemonTrainer trainer1, Pokemon pokemon1, //TODO: check if there is a prettier way?
                                  PokemonTrainer trainer2, Pokemon pokemon2,
                                  int* old_cp1, double* old_hp1,
                                  int* old_level1, double* old_xp1,
                                  bool* is_dead1, int* old_cp2,
                                  double* old_hp2, int* old_level2,
                                  double* old_xp2, bool* is_dead2) {
    *old_cp1 = pokemonGetCP(pokemon1);
    *old_hp1 = pokemonGetHP(pokemon1);
    *old_level1 = pokemonGetLevel(pokemon1);
    *old_xp1 = trainer1->xp;
    // dup but extra function is redundant (too many pointers moving)
    *old_cp2 = pokemonGetCP(pokemon2);
    *old_hp2 = pokemonGetHP(pokemon2);
    *old_level2 = pokemonGetLevel(pokemon2);
    *old_xp2 = trainer2->xp;

    double delta1, delta2;
    PokemonResult result;

    delta1 = CALC_DELTA(*old_xp2, *old_cp2, *old_hp2);
    delta2 = CALC_DELTA(*old_xp1, *old_cp1, *old_hp1);

    result = pokemonUpdateHP(pokemon1, -delta1);
    if (result == POKEMON_NO_HEALTH_POINTS) *is_dead1=true;
    result = pokemonUpdateHP(pokemon2, -delta2);
    if (result == POKEMON_NO_HEALTH_POINTS) *is_dead2=true;

    pokemonUpdateLevel(pokemon1, CALC_LEVEL_BONUS(*old_level1, *old_level2));
    pokemonUpdateLevel(pokemon2, CALC_LEVEL_BONUS(*old_level2, *old_level1));

    trainer1->xp += CALC_XP_BONUS(delta2);
    trainer2->xp += CALC_XP_BONUS(delta1);
}


int pokemonTrainerGetMaxValueItem(PokemonTrainer trainer, ItemType item_type) {
    int max_value = NO_MAX_VALUE;
    LIST_FOREACH(Item, item_iter, trainer->item_list) {
        if (itemGetValue(item_iter) > max_value &&
                itemGetType(item_iter) == item_type) {
            max_value = itemGetValue(item_iter);
        }
    }

    return max_value;
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
    trainer->location = NULL;
    trainer->name = createName(name);
    trainer->pokemon_set = setCreate((SetElement) pokemonCopy,     // TODO: should this in an aux function? *void / **void ?
                          (freeSetElements) pokemonDestroy,
                          (compareSetElements) pokemonCompare);
    trainer->item_list = listCreate((SetElement) itemCopy,
                          (freeSetElements) itemDestroy);

    if (trainer->name == NULL || \
        trainer->pokemon_set == NULL || trainer->item_list == NULL) {
        pokemonTrainerDestroy(trainer);
        return NULL;
    }
    //PokemonTrainerResult result = pokemonTrainerGoHunt(trainer, location); //TODO:need to run in PokemonGO !

    return trainer;
}


void pokemonTrainerDestroy(PokemonTrainer trainer) {
    if (trainer != NULL) {
        free(trainer->name);
        free(trainer->location);

        listDestroy(trainer->item_list);
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

    new_trainer->item_list = listCopy(trainer->item_list);
    if (new_trainer->item_list == NULL && trainer->item_list != NULL) {
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

    //Pokemon new_pokemon = pokemonCopy(pokemon);
    //if (new_pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEM;

    pokemonUpdateID(pokemon, trainer->number_of_caught_pokemons + 1);

    SetResult result = setAdd(trainer->pokemon_set, pokemon);
    trainer->number_of_caught_pokemons++;

    if (result == SET_OUT_OF_MEMORY) { //TODO: should I delete trainer? pokemonGO.c should?
        return POKEMON_TRAINER_OUT_OF_MEM;
    }

    return POKEMON_TRAINER_SUCCESS;
}


PokemonTrainerResult pokemonTrainerAddItem(PokemonTrainer trainer,
                                              Item item) {
    if (trainer == NULL || item == NULL) return POKEMON_TRAINER_NULL_ARG;


    ListResult result = listInsertLast(trainer->item_list, item);

    if (result == LIST_OUT_OF_MEMORY) { //TODO: should I delete trainer? pokemonGO.c should?
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

    ItemResult result = storeDoesItemExist(store, item);

    if (result == STORE_OUT_OF_STOCK) //TODO: add more errors here?
        return POKEMON_TRAINER_ITEM_OUT_OF_STOCK;

    if (result == STORE_SUCCESS) {
        Item new_item = storeSellItem(store, item);
        if (new_item == NULL) return POKEMON_TRAINER_OUT_OF_MEM;

        PokemonTrainerResult pokemon_result =
                pokemonTrainerAddItem(trainer, new_item);

        if (pokemon_result == POKEMON_TRAINER_OUT_OF_MEM)
            return POKEMON_TRAINER_OUT_OF_MEM;

    }

    return POKEMON_TRAINER_SUCCESS;
}

PokemonTrainerResult pokemonTrainerGoHunt(PokemonTrainer trainer,
                                          char* location, WorldMap world_map,
                                          FILE* output) {
    if (trainer == NULL || location == NULL)
        return POKEMON_TRAINER_NULL_ARG;

    if (strcmp(trainer->location, location) == SAME_STRINGS)
        return POKEMON_TRAINER_ALREADY_IN_LOCATION;

    if (!pokemonTrainerIsLocationReachable(trainer, location)) //TODO: is bool? should be result?
        return POKEMON_TRAINER_LOCATION_IS_NOT_REACHABLE;

    trainer->location = createName(location);

    if (trainer->location == NULL)
        return POKEMON_TRAINER_OUT_OF_MEM;

    Pokemon pokemon = worldMapGetPokemonFromLocation(world_map);

    if (pokemon == NULL) {
        mtmPrintCatchResult(output, trainer->name, NULL, location);
        return POKEMON_TRAINER_SUCCESS;
    }

    PokemonTrainerResult result = pokemonTrainerAddPokemon(trainer, pokemon);
    if (result == POKEMON_TRAINER_SUCCESS) {
        mtmPrintCatchResult(output, trainer->name,
                            pokemonGetName(pokemon), location);
    }

    return result;
}

PokemonTrainerResult pokemonTrainerFight(PokemonTrainer trainer1,
                                         PokemonTrainer trainer2,
                                         int pokemon1_id,
                                         int pokemon2_id, FILE* output) { //TODO: should be first_trainer instead trainer1?
    if (trainer1 == NULL || trainer2 == NULL) return POKEMON_TRAINER_NULL_ARG;
    Pokemon pokemon1 = pokemonTrainerGetPokemon(trainer1,pokemon1_id);
    Pokemon pokemon2 = pokemonTrainerGetPokemon(trainer2,pokemon2_id);
    if (pokemon1 == NULL || pokemon2 == NULL)
        return POKEMON_TRAINER_POKEMON_DOESNT_EXIST;

    if (strcmp(trainer1->name, trainer2->name) == SAME_STRINGS)
        return POKEMON_TRAINER_INVALID_AGR;

    int old_cp1, old_level1, old_cp2, old_level2;
    double old_hp1, old_xp1, old_hp2, old_xp2;
    bool is_dead1=false, is_dead2=false;

    pokemonTrainerFightAux(trainer1, pokemon1, trainer2, pokemon2,
                          &old_cp1, &old_hp1, &old_level1, &old_xp1, &is_dead1,
                          &old_cp2, &old_hp2, &old_level2, &old_xp2, &is_dead2);

    mtmPrintBattle(output, trainer1->name, trainer2->name, pokemon1->name,
        pokemon2->name, pokemonGetCP(pokemon1), pokemonGetCP(pokemon2), old_hp1,
        old_hp2, pokemonGetHP(pokemon1), pokemonGetHP(pokemon2), old_level1,
        old_level2, pokemonGetLevel(pokemon1), pokemonGetLevel(pokemon2),
        old_xp1, old_xp2, trainer1->xp, trainer2->xp, is_dead1, is_dead2);

    return POKEMON_TRAINER_SUCCESS;
}

PokemonTrainerResult pokemonTrainerHealPokemon(PokemonTrainer trainer,
                                               int pokemon_id) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;

    Pokemon pokemon = pokemonTrainerGetPokemon(trainer, pokemon_id);
    if (pokemon == NULL) return POKEMON_TRAINER_POKEMON_DOESNT_EXIST;

    double max_value = pokemonTrainerGetMaxValueItem(trainer, TYPE_POTION);
    if (max_value == NO_MAX_VALUE) return POKEMON_TRAINER_ITEM_OUT_OF_STOCK;

    if (pokemonGetHP(pokemon) == DEFAULT_HP)
        return POKEMON_TRAINER_POKEMON_HP_AT_MAX;

    Item item = NULL;

    LIST_FOREACH(Item, item_iter, trainer->item_list) {
        // if logic: potion *and*
        //  (pokemon_hp+value is bigger than 100 *and* smaller than max_value))
        if ( itemGetType(item_iter) == TYPE_POTION &&
              (itemGetValue(item) + pokemon->hp >= DEFAULT_HP &&
                  itemGetValue(item) < max_value) ) {
            item = item_iter;
            max_value = itemGetValue(item);
        }
    }

    pokemonUseItem(pokemon, item);

    LIST_FOREACH(Item, item_iter, trainer->item_list) {
        if (itemCompare(item, item_iter) == ITEM_EQUAL) {
            listRemoveCurrent(trainer->item_list); //TODO: should I check result?
            return POKEMON_TRAINER_SUCCESS;
        }
    }

    return POKEMON_TRAINER_SUCCESS;
}

PokemonTrainerResult pokemonTrainerTrainPokemon(PokemonTrainer trainer,
                                                int pokemon_id) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;

    Pokemon pokemon = pokemonTrainerGetPokemon(trainer, pokemon_id);
    if (pokemon == NULL) return POKEMON_TRAINER_POKEMON_DOESNT_EXIST;

    int max_value = pokemonTrainerGetMaxValueItem(trainer, TYPE_CANDY);
    if (max_value == NO_MAX_VALUE) return POKEMON_TRAINER_ITEM_OUT_OF_STOCK;

    LIST_FOREACH(Item, item_iter, trainer->item_list) {
        if (itemGetValue(item_iter) == max_value &&
                itemGetType(item_iter) == TYPE_CANDY) {
            pokemonUseItem(pokemon, item_iter);
            listRemoveCurrent(trainer->item_list);
            return POKEMON_TRAINER_SUCCESS;
        }
    }

    return POKEMON_TRAINER_SUCCESS;
}