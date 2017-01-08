#include <stdbool.h>
#include "aux_macros.h"
#include "../pokemon.h"
#include "../pokemon_trainer.h"

static bool testCombo() {
	bool result = true;

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);
    pokedexAddPokemonInfo(pokedex, raichu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
    Pokemon raichu = pokemonCreate("Raichu", pokedex);

    PokemonTrainer trainer = pokemonTrainerCreate("Ash",100);
    Trainers trainers = trainersCreate();

    Item item1 = itemCreate(10,"potion");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"candy");

    Store store = storeCreate();
    storeAddItem(store,item1);
    storeAddItem(store,item1);
    storeAddItem(store,item2);
    storeAddItem(store,item3);

    TEST_DIFFERENT(result,trainer , NULL);
    TEST_EQUALS(result,trainersAddTrainer(trainers, trainer),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result,trainersAddTrainer(trainers, trainer),
                POKEMON_TRAINER_ALREADY_EXIST);
    PokemonTrainer ash = trainersGetTrainer(trainers, "Ash");
    PokemonTrainer ash_copy = pokemonTrainerCopy(ash);
    TEST_DIFFERENT(result,ash , NULL);
    TEST_DIFFERENT(result,ash_copy , NULL);

    PokemonTrainer trainer2 = pokemonTrainerCreate("Ohad",100);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer2, item1, store),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer2, item1, store),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer2, item1, store),
                POKEMON_TRAINER_ITEM_OUT_OF_STOCK);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer2, item2, store),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer2, item3, store),
                POKEMON_TRAINER_INSUFFICIENT_BUDGET);

    TEST_EQUALS(result,pokemonTrainerAddPokemon(trainer2,pikachu, pokedex),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result,pokemonTrainerAddPokemon(trainer2,raichu, pokedex),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer2, 1),
                POKEMON_TRAINER_POKEMON_HP_AT_MAX);

    pokemonUpdateHP(pokemonTrainerGetPokemon(trainer2,1),-90);
    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer2, 1),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonGetHP(pokemonTrainerGetPokemon(trainer2,1)), 20);
    TEST_EQUALS(result,trainersAddTrainer(trainers, trainer2),
                POKEMON_TRAINER_SUCCESS);

    storeDestroy(store);
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    pokemonTrainerDestroy(trainer);
    pokemonTrainerDestroy(trainer2);
    pokemonTrainerDestroy(ash_copy);
    trainersDestroy(trainers);
    pokemonDestroy(pikachu);
    pokemonDestroy(raichu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexPokemonInfoDestroy(raichu_info);
    pokedexDestroy(pokedex);

	return result;

}



static bool testPokemonTrainerCreateDestroy() {
    bool result = true;

    PokemonTrainer trainer = pokemonTrainerCreate("Ash",100);
    PokemonTrainer trainer0 = pokemonTrainerCreate("Ash",0);

    TEST_DIFFERENT(result,trainer , NULL);
    TEST_DIFFERENT(result,trainer0, NULL);
    TEST_EQUALS(result, pokemonTrainerCreate(NULL,100), NULL);
    TEST_EQUALS(result, pokemonTrainerCreate("Ash",-5), NULL);

    pokemonTrainerDestroy(trainer);
    pokemonTrainerDestroy(trainer0);

    return result;
}


static bool testPokemonTrainerCopy() {
    bool result = true;

    PokemonTrainer trainer = pokemonTrainerCreate("Ash",100);

    PokemonTrainer trainer_copy = pokemonTrainerCopy(trainer);

    TEST_DIFFERENT(result,trainer_copy , NULL);
    TEST_EQUALS(result,pokemonTrainerCopy(NULL) , NULL);
    TEST_DIFFERENT(result, trainer, trainer_copy);


    pokemonTrainerDestroy(trainer);
    pokemonTrainerDestroy(trainer_copy);

    return result;

}

static bool testPokemonTrainerBuyItem() {
    bool result = true;


    PokemonTrainer trainer = pokemonTrainerCreate("Ash",100);

    Item item1 = itemCreate(10,"potion");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"candy");

    Store store = storeCreate();
    storeAddItem(store,item1);
    storeAddItem(store,item1);
    storeAddItem(store,item2);
    storeAddItem(store,item3);

    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item1, store),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item1, store),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item1, store),
                POKEMON_TRAINER_ITEM_OUT_OF_STOCK);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item2, store),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item3, store),
                POKEMON_TRAINER_INSUFFICIENT_BUDGET);

    TEST_EQUALS(result, pokemonTrainerBuyItem(NULL, item1, store),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, NULL, store),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item1, NULL),
                POKEMON_TRAINER_NULL_ARG);

    storeDestroy(store);
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);

    pokemonTrainerDestroy(trainer);


    return result;

}

static bool testPokemonTrainerTrainHealPokemon() {
    bool result = true;

    PokemonTrainer trainer = pokemonTrainerCreate("Ash",10000);

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);
    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);

    TEST_EQUALS(result,pokemonTrainerAddPokemon(trainer,pikachu, pokedex),
                POKEMON_TRAINER_SUCCESS);
    pokemonUpdateHP(pokemonTrainerGetPokemon(trainer,1),-20);

    Item item1 = itemCreate(30,"potion");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(50,"potion");
    Item item4 = itemCreate(20,"candy");

    Store store = storeCreate();
    storeAddItem(store,item1);
    storeAddItem(store,item1);
    storeAddItem(store,item2);
    storeAddItem(store,item3);
    storeAddItem(store,item4);

    pokemonTrainerBuyItem(trainer, item4, store);
    pokemonTrainerBuyItem(trainer, item1, store);
    pokemonTrainerBuyItem(trainer, item1, store);
    pokemonTrainerBuyItem(trainer, item2, store);
    pokemonTrainerBuyItem(trainer, item3, store);

    // Pokemon Heal Testing
    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer, 1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pokemonTrainerGetPokemon(trainer,1)), 100);
    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer, 1),
                POKEMON_TRAINER_POKEMON_HP_AT_MAX);

    pokemonUpdateHP(pokemonTrainerGetPokemon(trainer,1),-90);

    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer, 1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pokemonTrainerGetPokemon(trainer,1)), 60);
    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer, 1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pokemonTrainerGetPokemon(trainer,1)), 90);
    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer, 1),
                POKEMON_TRAINER_NO_AVAILABLE_ITEM_FOUND);
    TEST_EQUALS(result, pokemonTrainerHealPokemon(trainer, 2),
                POKEMON_TRAINER_POKEMON_DOESNT_EXIST);


    // Pokemon Train Testing
    TEST_EQUALS(result, pokemonTrainerTrainPokemon(trainer, 1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonGetCP(pokemonTrainerGetPokemon(trainer,1)), 50);
    TEST_EQUALS(result, pokemonTrainerTrainPokemon(trainer, 1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonGetCP(pokemonTrainerGetPokemon(trainer,1)), 70);
    TEST_EQUALS(result, pokemonTrainerTrainPokemon(trainer, 1),
                POKEMON_TRAINER_NO_AVAILABLE_ITEM_FOUND);
    TEST_EQUALS(result, pokemonTrainerTrainPokemon(trainer, 2),
                POKEMON_TRAINER_POKEMON_DOESNT_EXIST);


    storeDestroy(store);
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);

    pokemonDestroy(pikachu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);

    pokemonTrainerDestroy(trainer);


    return result;

}



static bool testTrainersCreateDestroy() {
    bool result = true;

    Trainers trainers = trainersCreate();
    TEST_DIFFERENT(result,trainers , NULL);
    trainersDestroy(trainers);

    return result;
}



static bool testTrainersAddGetTrainer() {
    bool result = true;

    Trainers trainers = trainersCreate();

    PokemonTrainer trainer1 = pokemonTrainerCreate("Ash",1000);
    PokemonTrainer trainer_copy = pokemonTrainerCopy(trainer1);
    PokemonTrainer trainer2 = pokemonTrainerCreate("Ohad",10);

    TEST_EQUALS(result,trainersAddTrainer(trainers, trainer1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result,trainersAddTrainer(trainers, trainer1),
                POKEMON_TRAINER_ALREADY_EXIST);
    TEST_EQUALS(result,trainersAddTrainer(trainers, trainer_copy),
                POKEMON_TRAINER_ALREADY_EXIST);
    TEST_EQUALS(result,trainersAddTrainer(trainers, trainer2),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result,trainersAddTrainer(NULL, trainer2),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result,trainersAddTrainer(trainers, NULL),
                POKEMON_TRAINER_NULL_ARG);

    TEST_DIFFERENT(result,trainersGetTrainer(trainers,"Ash"), NULL);
    TEST_DIFFERENT(result,trainersGetTrainer(trainers,"Ohad"), NULL);
    TEST_EQUALS(result,trainersGetTrainer(trainers,"ohad"), NULL);

    TEST_EQUALS(result,trainersGetTrainer(trainers,NULL), NULL);
    TEST_EQUALS(result,trainersGetTrainer(NULL,"Ash"), NULL);

    TEST_EQUALS(result, trainersDoesTrainerExist(trainers, "Ohad"),true);
    TEST_EQUALS(result, trainersDoesTrainerExist(trainers, "Ash"),true);
    TEST_EQUALS(result, trainersDoesTrainerExist(trainers, "ohad"),false);


    pokemonTrainerDestroy(trainer1);
    pokemonTrainerDestroy(trainer2);
    pokemonTrainerDestroy(trainer_copy);
    trainersDestroy(trainers);

    return result;
}

//static bool testPokemonTrainerGoHunt() {
//    bool result = true;
//
//    PokemonTrainer trainer = pokemonTrainerCreate("Ash", "israel",100);
//
//    WorldMap world_map = worldMapCreate();
//
//    Pokedex pokedex = pokedexCreate();
//    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
//    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 30);
//    pokedexAddPokemonInfo(pokedex, pikachu_info);
//    pokedexAddPokemonInfo(pokedex, raichu_info);
//    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
//    Pokemon raichu = pokemonCreate("Raichu", pokedex);
//
//    TEST_EQUALS(result, pokemonTrainerGoHunt(trainer, "israel",world_map,
//                                             pokedex,stdout)
//                                             ,POKEMON_TRAINER_SUCCESS);
//
//    Location location = locationCreate("israel");
//    locationAddPokemon(location, pikachu);
//
//
//
//
//    TEST_DIFFERENT(result,pokemonTrainerGetPokemon(trainer, 1), NULL);
//    TEST_DIFFERENT(result,pokemonTrainerGetPokemon(trainer, 2), NULL);
//    TEST_DIFFERENT(result,pokemonTrainerGetPokemon(trainer, 3), NULL);
//    TEST_EQUALS(result,pokemonTrainerGetPokemon(trainer, 0), NULL);
//    TEST_EQUALS(result,pokemonTrainerGetPokemon(trainer, 5), NULL);
//
//    TEST_EQUALS(result, strcmp("Pikachu", pokemonGetName(
//            pokemonTrainerGetPokemon(trainer,1)
//    )) , 0);
//    TEST_EQUALS(result, strcmp("Raichu", pokemonGetName(
//            pokemonTrainerGetPokemon(trainer,2)
//    )) , 0);
//    TEST_EQUALS(result, strcmp("Pikachu", pokemonGetName(
//            pokemonTrainerGetPokemon(trainer,3)
//    )) , 0);
//
//    pokemonDestroy(pikachu);
//    pokemonDestroy(raichu);
//    pokedexPokemonInfoDestroy(pikachu_info);
//    pokedexPokemonInfoDestroy(raichu_info);
//    pokedexDestroy(pokedex);
//
//    pokemonTrainerDestroy(trainer);
//
//
//    return result;
//}



int main() {
    RUN_TEST(testCombo);
	RUN_TEST(testPokemonTrainerCreateDestroy);
	RUN_TEST(testPokemonTrainerCopy);
    //RUN_TEST(testPokemonTrainerGetPokemon);
    RUN_TEST(testPokemonTrainerBuyItem);
    //RUN_TEST(testPokemonTrainerGoHunt);
    //RUN_TEST(testPokemonTrainerAddPokemon);
    //RUN_TEST(testPokemonTrainerFight);
    RUN_TEST(testPokemonTrainerTrainHealPokemon);
    RUN_TEST(testTrainersCreateDestroy);
    RUN_TEST(testTrainersAddGetTrainer);
    //RUN_TEST(testTrainersGetTrainer);


	return 0;
}
