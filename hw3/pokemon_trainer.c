//
// Created by ohad on 27-Nov-16.
//


#include "pokemon_trainer.h"


struct pokemon_trainer_t {
    char* name;
    char* location;
    List pokemon_list;
    Store item_list;
    double xp;
    int pokecoins;
    int number_of_caught_pokemons;

} ;



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
static Item pokemonTrainerGetMaxValueItem(PokemonTrainer trainer,
                                         ItemType item_type);


/**
* Find and remove a given pokemon from a trainer's pokemon list.
*
*/
static void pokemonTrainerRemovePokemon(PokemonTrainer trainer,
                                                        Pokemon pokemon);


/* wrapper function to pokemonTrainerCopy so it
 * will be possible to work with Set GDT */
PokemonTrainerElement static pokemonTrainerCopyElement(
        PokemonTrainerElement trainer);

/*wrapper function to pokemonTrainerDestroy so it
 * will be possible to work with Set GDT*/
void static pokemonTrainerFreeElement(PokemonTrainerElement trainer);

/*wrapper function to pokemonTrainerCompare so it
 * will be possible to work with Set GDT*/
int static pokemonTrainerCompareElement(PokemonTrainerElement trainer1 ,
                                     PokemonTrainerElement trainer2);

/**
* compare between two pokemon trainers and return an int.
* check if has the same name
*
* @return
*   0 - if the same.
* 	strcmp result - otherwise.
*/
static int pokemonTrainerCompare(PokemonTrainer trainer1, PokemonTrainer pokemon2);


/**
* Add a given item to the mini-store(item list) of a given trainer.
* The new item is a copy of given item. related to @pokemonTrainerBuyItem
*
* @return
* 	POKEMON_TRAINER_NULL_ARG if trainer or item is NULL.
 * 	POKEMON_TRAINER_OUT_OF_MEMORY if set had a memory allocation error.
* 	POKEMON_SUCCESS otherwise.
*/
static PokemonTrainerResult pokemonTrainerAddItem(PokemonTrainer trainer, Item item);

/****************************************
 *    Assistent Pokemon Trainer Funcs   *
 ****************************************/

void pokemonTrainerFightAux(PokemonTrainer trainer1, Pokemon pokemon1,
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


Item pokemonTrainerGetMaxValueItem(PokemonTrainer trainer, ItemType item_type) {
    int max_value = NO_MAX_VALUE;
    Item item = NULL;
    STORE_FOREACH(Item, item_iter, trainer->item_list) {
        if (itemGetValue(item_iter) > max_value &&
                itemGetType(item_iter) == item_type) {
        	item = item_iter;
            max_value = itemGetValue(item_iter);
        }
    }

    return item;
}


void pokemonTrainerRemovePokemon(PokemonTrainer trainer,
                                                 Pokemon pokemon) {
    assert(trainer != NULL);
    assert(pokemon != NULL);

    LIST_FOREACH(Pokemon, pokemon_iter, trainer->pokemon_list) {

        if (pokemonCompareByID(pokemon_iter, pokemon) == POKEMON_EQUAL)
            listRemoveCurrent(trainer->pokemon_list);
    }
}


PokemonTrainerElement pokemonTrainerCopyElement(
        PokemonTrainerElement trainer) {
    return pokemonTrainerCopy( (PokemonTrainer)trainer );
}


void pokemonTrainerFreeElement( PokemonTrainerElement trainer ) {
    pokemonTrainerDestroy( (PokemonTrainer)trainer );
}


int  pokemonTrainerCompareElement( PokemonTrainerElement trainer1 ,
                                PokemonTrainerElement trainer2 ) {
    return pokemonTrainerCompare((PokemonTrainer)trainer1 ,
                                     (PokemonTrainer)trainer2 );
}


int pokemonTrainerCompare(PokemonTrainer trainer1 ,PokemonTrainer trainer2) {
    assert(trainer1 != NULL);
    assert(trainer2 != NULL);

    return strcmp(trainer1->name, trainer2->name);
}


PokemonTrainerResult pokemonTrainerAddItem(PokemonTrainer trainer,
                                           Item item) {
    if (trainer == NULL || item == NULL) return POKEMON_TRAINER_NULL_ARG;

    StoreResult result = storeAddItem(trainer->item_list, item);

    if (result == STORE_OUT_OF_MEMORY) {
        return POKEMON_TRAINER_OUT_OF_MEMORY;
    }

    return POKEMON_TRAINER_SUCCESS;
}

/********************************
 *    Pokemon Trainer Funcs     *
 ********************************/

bool pokemonTrainerIsValidArgs(char* name, char* location, int budget) {
    if (name == NULL || location == NULL) return false;
    if (!strcmp(name,"") || !strcmp(location,"")) return false;
    if (budget < NO_BUDGET) return false;
    return true;
}


PokemonTrainer pokemonTrainerCreate(char* name, char* location, int budget) {
    if (!pokemonTrainerIsValidArgs(name,location,budget))
        return NULL;

    PokemonTrainer trainer = malloc(sizeof(*trainer));
    if (trainer == NULL) return NULL;

    trainer->xp = DEFUALT_XP;
    trainer->pokecoins = budget;
    trainer->number_of_caught_pokemons = NO_POKEMONS;
    trainer->name = stringCopy(name);
    trainer->location = stringCopy(location);
    trainer->pokemon_list = listCreate(pokemonCopyElement, pokemonFreeElement);
    trainer->item_list = storeCreate();

    if (trainer->name == NULL || trainer->location == NULL || \
        trainer->pokemon_list == NULL || trainer->item_list == NULL) {
        pokemonTrainerDestroy(trainer);
        return NULL;
    }
    //PokemonTrainerResult result = pokemonTrainerGoHunt(trainer, location); //TODO:need to run in PokemonGO !

    return trainer;
}


void pokemonTrainerDestroy(PokemonTrainer trainer) {
    if (trainer != NULL) {
        stringDestroy(trainer->name);
        stringDestroy(trainer->location);

        storeDestroy(trainer->item_list);
        listDestroy(trainer->pokemon_list);

        free(trainer);
    }
}


PokemonTrainer pokemonTrainerCopy(PokemonTrainer trainer) {
    if (trainer == NULL) return NULL;
    PokemonTrainer new_trainer = pokemonTrainerCreate(trainer->name,
                                                      trainer->location,
                                                      trainer->pokecoins);
    if (new_trainer == NULL) return NULL;

    listDestroy(new_trainer->pokemon_list);
    new_trainer->pokemon_list = listCopy(trainer->pokemon_list);
    storeDestroy(new_trainer->item_list);
    new_trainer->item_list = storeCopy(trainer->item_list);

    if (new_trainer->pokemon_list == NULL || new_trainer->item_list == NULL) {
        pokemonTrainerDestroy(new_trainer);
        return NULL;
    }

    new_trainer->number_of_caught_pokemons = trainer->number_of_caught_pokemons;
    new_trainer->xp = trainer->xp;

    return new_trainer;
}


PokemonTrainerResult pokemonTrainerAddPokemon(PokemonTrainer trainer,
                                              Pokemon pokemon,
                                              Pokedex pokedex) {
    if (trainer == NULL || pokemon == NULL || pokedex == NULL)
        return POKEMON_TRAINER_NULL_ARG;

    Pokemon new_pokemon = pokemonCopy(pokemon);
    if (new_pokemon == NULL) return POKEMON_TRAINER_OUT_OF_MEMORY;

    pokemonUpdateID(new_pokemon, trainer->number_of_caught_pokemons + 1);

    ListResult result = listInsertLast(trainer->pokemon_list, new_pokemon);
    trainer->number_of_caught_pokemons++;
    trainer->pokecoins +=
            pokedexGetStarBonus(pokedex, pokemonGetName(new_pokemon));

    pokemonDestroy(new_pokemon);

    if (result == LIST_OUT_OF_MEMORY) {
        return POKEMON_TRAINER_OUT_OF_MEMORY;
    }

    return POKEMON_TRAINER_SUCCESS;
}



Pokemon pokemonTrainerGetPokemon(PokemonTrainer trainer, int pokemon_id) { //TODO: should be static?
    if (trainer == NULL) return NULL;

    Pokemon pokemon = NULL;

    LIST_FOREACH(Pokemon, pokemon_iter, trainer->pokemon_list) {
        if (pokemonGetID(pokemon_iter) == pokemon_id) {
            pokemon = pokemon_iter;
        }
    }

    return pokemon;
}


PokemonTrainerResult pokemonTrainerBuyItem(PokemonTrainer trainer, Item item,
                                            Store store) {
    if (trainer == NULL || item == NULL || store == NULL)
        return POKEMON_TRAINER_NULL_ARG;

    int price = itemGetPrice(item);
    if (trainer->pokecoins < price) return POKEMON_TRAINER_INSUFFICIENT_BUDGET;

    if (!storeDoesItemExist(store, item))
        return POKEMON_TRAINER_ITEM_OUT_OF_STOCK;

    Item new_item = storeSellItem(store, item);
    if (new_item == NULL) return POKEMON_TRAINER_OUT_OF_MEMORY;

    PokemonTrainerResult pokemon_result =
            pokemonTrainerAddItem(trainer, new_item);

    itemDestroy(new_item);

    trainer->pokecoins -= price;

    return pokemon_result;
}

PokemonTrainerResult pokemonTrainerGoHunt(PokemonTrainer trainer,
                                          char* location, WorldMap world_map,
                                          Pokedex pokedex, FILE* output) {
    if (trainer == NULL || location == NULL)
        return POKEMON_TRAINER_NULL_ARG;

    if (strcmp(trainer->location, location) == SAME_STRINGS)
        return POKEMON_TRAINER_ALREADY_IN_LOCATION;

    if (!worldMapIsLocationReachable(world_map, trainer->location, location))
        return POKEMON_TRAINER_LOCATION_IS_NOT_REACHABLE;

    stringDestroy(trainer->location);
    trainer->location = stringCopy(location);

    if (trainer->location == NULL)
        return POKEMON_TRAINER_OUT_OF_MEMORY;

    Pokemon pokemon = worldMapGetPokemonInLocation(world_map, location);

    if (pokemon == NULL) {
        mtmPrintCatchResult(output, trainer->name, NULL, location);
        return POKEMON_TRAINER_SUCCESS;
    }

    PokemonTrainerResult result = pokemonTrainerAddPokemon(trainer, pokemon,
                                                           pokedex);
    if (result == POKEMON_TRAINER_SUCCESS) {
        mtmPrintCatchResult(output, trainer->name,
                            pokemonGetName(pokemon), location);
    }

    return result;
}

PokemonTrainerResult pokemonTrainerFight(PokemonTrainer trainer1,
                                         PokemonTrainer trainer2,
                                         int pokemon1_id,
                                         int pokemon2_id, Pokedex pokedex,
                                         FILE* output) {
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

    mtmPrintBattle(output, trainer1->name, trainer2->name,
             pokemonGetName(pokemon1), pokemonGetName(pokemon2),
             pokemonGetCP(pokemon1), pokemonGetCP(pokemon2), old_hp1, old_hp2,
             pokemonGetHP(pokemon1), pokemonGetHP(pokemon2), old_level1,
             old_level2, pokemonGetLevel(pokemon1), pokemonGetLevel(pokemon2),
             old_xp1, old_xp2, trainer1->xp, trainer2->xp, is_dead1, is_dead2);

    PokemonResult result1 = pokemonCheckEvolution(pokemon1, pokedex);
    PokemonResult result2 = pokemonCheckEvolution(pokemon2, pokedex);
    if (result1 == POKEMON_OUT_OF_MEMORY || result2 == POKEMON_OUT_OF_MEMORY)
        return POKEMON_TRAINER_OUT_OF_MEMORY;

    if (is_dead1) pokemonTrainerRemovePokemon(trainer1, pokemon1);
    if (is_dead2) pokemonTrainerRemovePokemon(trainer2, pokemon2);
    return POKEMON_TRAINER_SUCCESS;
}

PokemonTrainerResult pokemonTrainerHealPokemon(PokemonTrainer trainer,
                                               int pokemon_id) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;

    Pokemon pokemon = pokemonTrainerGetPokemon(trainer, pokemon_id);
    if (pokemon == NULL) return POKEMON_TRAINER_POKEMON_DOESNT_EXIST;

    Item item = pokemonTrainerGetMaxValueItem(trainer, TYPE_POTION);
    if (item == NULL) return POKEMON_TRAINER_ITEM_OUT_OF_STOCK;

    if (pokemonGetHP(pokemon) == DEFAULT_HP)
        return POKEMON_TRAINER_POKEMON_HP_AT_MAX;


    STORE_FOREACH(Item, item_iter, trainer->item_list) {
        // if logic: potion *and*
        //  (pokemon_hp+value is bigger than 100 *and* smaller than max valued item))
        if ( itemGetType(item_iter) == TYPE_POTION &&
              (itemGetValue(item_iter) + pokemon->hp >= DEFAULT_HP &&
                  itemGetValue(item_iter) < itemGetValue(item)) ) {
            item = item_iter;
        }
    }

    pokemonUseItem(pokemon, item);
    storeRemoveItem(trainer->item_list, item);

    return POKEMON_TRAINER_SUCCESS;
}

PokemonTrainerResult pokemonTrainerTrainPokemon(PokemonTrainer trainer,
                                                int pokemon_id) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;

    Pokemon pokemon = pokemonTrainerGetPokemon(trainer, pokemon_id);
    if (pokemon == NULL) return POKEMON_TRAINER_POKEMON_DOESNT_EXIST;

    Item item = pokemonTrainerGetMaxValueItem(trainer, TYPE_CANDY);
    if (item == NULL) return POKEMON_TRAINER_ITEM_OUT_OF_STOCK;

    STORE_FOREACH(Item, item_iter, trainer->item_list) {
        if (itemGetValue(item_iter) == itemGetValue(item) &&
                itemGetType(item_iter) == TYPE_CANDY) {
            pokemonUseItem(pokemon, item_iter);
            storeRemoveItem(trainer->item_list, item_iter);
            return POKEMON_TRAINER_SUCCESS;
        }
    }

    return POKEMON_TRAINER_SUCCESS;
}


PokemonTrainerResult pokemonTrainerReport(PokemonTrainer trainer,
                                          FILE* output) {
    if (trainer == NULL) return POKEMON_TRAINER_NULL_ARG;
    StoreResult result = storeSort(trainer->item_list);
    if (result == STORE_OUT_OF_MEMORY) return POKEMON_TRAINER_OUT_OF_MEMORY;

    mtmPrintTrainerHeader(output,trainer->name,trainer->location,
                          trainer->pokecoins, trainer->xp);
    mtmPrintItemsHeaderForTrainer(output);
    storePrintStock(trainer->item_list , output);
    mtmPrintPokemonsHeaderForTrainer(output);
    LIST_FOREACH(Pokemon, pokemon, trainer->pokemon_list) {
        mtmPrintPokemon(output, pokemonGetID(pokemon), pokemonGetName(pokemon),
                        pokemonGetHP(pokemon), pokemonGetCP(pokemon),
                        pokemonGetLevel(pokemon));
    }

    return POKEMON_TRAINER_SUCCESS;
}


Trainers trainersCreate(){
    return setCreate(pokemonTrainerCopyElement, pokemonTrainerFreeElement,
                     pokemonTrainerCompareElement);
}

PokemonTrainerResult trainersAddTrainer(Trainers trainers,
                                        PokemonTrainer trainer) {
    if (trainers == NULL || trainer == NULL) return POKEMON_TRAINER_NULL_ARG;

    SetResult result = setAdd(trainers, trainer);

    if (result == SET_OUT_OF_MEMORY)
            return POKEMON_TRAINER_OUT_OF_MEMORY;

    if (result == SET_ITEM_ALREADY_EXISTS)
            return POKEMON_TRAINER_ALREADY_EXIST;

    return POKEMON_TRAINER_SUCCESS;
}

void trainersDestroy(Trainers trainers) {
    if (trainers != NULL)
        setDestroy(trainers);
}

PokemonTrainer trainersGetTrainer(Trainers trainers, char* trainer_name) {
	if (trainers == NULL || trainer_name == NULL) return NULL;

    SET_FOREACH(PokemonTrainer, trainer, trainers) {
        if (strcmp(trainer->name, trainer_name) == SAME_STRINGS)
            return trainer;
    }

    return NULL;
}

//TODO: add to tests!
bool trainersDoesTrainerExist(Trainers trainers, char* trainer_name) {
    assert(trainers != NULL);
    assert(trainer_name != NULL);

    PokemonTrainer trainer = trainersGetTrainer(trainers, trainer_name);
    if (trainer == NULL) return false;

    return true;

}