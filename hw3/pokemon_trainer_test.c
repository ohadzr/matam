#include <stdbool.h>
#include <string.h>
#include "aux_macros.h"
#include "pokemon.h"
#include "pokemon_trainer.h"

static bool testCombo() {
	bool result = true;

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);
    pokedexAddPokemonInfo(pokedex, raichu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
    Pokemon raichu = pokemonCreate("Raichu", pokedex);



    //TODO: add pokedex & location tests too


    pokemonDestroy(pikachu);
    pokemonDestroy(raichu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexPokemonInfoDestroy(raichu_info);
    pokedexDestroy(pokedex);

	return result;

}



static bool testPokemonTrainerCreateDestroy() {
    bool result = true;

    PokemonTrainer trainer = pokemonTrainerCreate("Ash", "paris",100);
    PokemonTrainer trainer0 = pokemonTrainerCreate("Ash", "paris",0);

    TEST_DIFFERENT(result,trainer , NULL);
    TEST_DIFFERENT(result,trainer0, NULL);
    TEST_EQUALS(result, pokemonTrainerCreate(NULL, "paris",100), NULL);
    TEST_EQUALS(result, pokemonTrainerCreate("Ash", NULL,100), NULL);
    TEST_EQUALS(result, pokemonTrainerCreate("Ash", "paris",-5), NULL);

    pokemonTrainerDestroy(trainer);
    pokemonTrainerDestroy(trainer0);

    return result;
}


static bool testPokemonTrainerCopy() {
    bool result = true;

    PokemonTrainer trainer = pokemonTrainerCreate("Ash", "paris",100);

    PokemonTrainer trainer_copy = pokemonTrainerCopy(trainer);

    TEST_DIFFERENT(result,trainer_copy , NULL);
    TEST_EQUALS(result,pokemonTrainerCopy(NULL) , NULL);
    TEST_DIFFERENT(result, trainer, trainer_copy);


    pokemonTrainerDestroy(trainer);
    pokemonTrainerDestroy(trainer_copy);

    return result;

}

static bool testPokemonTrainerAddPokemon() {
    bool result = true;

    PokemonTrainer trainer = pokemonTrainerCreate("Ash", "paris",100);

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 30);
    pokedexAddPokemonInfo(pokedex, pikachu_info);
    pokedexAddPokemonInfo(pokedex, raichu_info);
    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
    Pokemon raichu = pokemonCreate("Raichu", pokedex);



    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, pikachu, pokedex),
                POKEMON_SUCCESS );
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, raichu, pokedex),
                POKEMON_SUCCESS );
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, pikachu, pokedex),
                POKEMON_SUCCESS );

    TEST_EQUALS(result, pokemonTrainerAddPokemon(NULL, pikachu, pokedex),
                POKEMON_TRAINER_NULL_ARG );
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, NULL, pokedex),
                POKEMON_TRAINER_NULL_ARG );
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, pikachu, NULL),
                POKEMON_TRAINER_NULL_ARG );


    TEST_DIFFERENT(result,pokemonTrainerGetPokemon(trainer, 1), NULL);
    TEST_DIFFERENT(result,pokemonTrainerGetPokemon(trainer, 2), NULL);
    TEST_DIFFERENT(result,pokemonTrainerGetPokemon(trainer, 3), NULL);
    TEST_EQUALS(result,pokemonTrainerGetPokemon(trainer, 0), NULL);
    TEST_EQUALS(result,pokemonTrainerGetPokemon(trainer, 5), NULL);

    TEST_EQUALS(result, strcmp("Pikachu", pokemonGetName(
                                       pokemonTrainerGetPokemon(trainer,1)
                                          )) , 0);
    TEST_EQUALS(result, strcmp("Raichu", pokemonGetName(
                                       pokemonTrainerGetPokemon(trainer,2)
                                          )) , 0);
    TEST_EQUALS(result, strcmp("Pikachu", pokemonGetName(
                                       pokemonTrainerGetPokemon(trainer,3)
                                          )) , 0);

    pokemonDestroy(pikachu);
    pokemonDestroy(raichu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexPokemonInfoDestroy(raichu_info);
    pokedexDestroy(pokedex);

    pokemonTrainerDestroy(trainer);


    return result;
}


static bool testPokemonTrainerBuyItem() {
    bool result = true;


    PokemonTrainer trainer = pokemonTrainerCreate("Ash", "paris",100);

    Item item1 = itemCreate(10,TYPE_CANDY);
    Item item2 = itemCreate(40,TYPE_CANDY);
    Item item3 = itemCreate(100,TYPE_POTION);

    Store store = storeCreate();
    storeAddItem(store,item1);
    storeAddItem(store,item1);
    storeAddItem(store,item2);
    storeAddItem(store,item3);

    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item2),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item2),
                POKEMON_TRAINER_ITEM_OUT_OF_STOCK);
    TEST_EQUALS(result, pokemonTrainerBuyItem(trainer, item2),
                POKEMON_TRAINER_ITEM_OUT_OF_STOCK);

    storeDestroy(store);
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);

    pokemonTrainerDestroy(trainer);


    return result;

}



int main() {
    RUN_TEST(testCombo);
	RUN_TEST(testPokemonTrainerCreateDestroy);
	RUN_TEST(testPokemonTrainerCopy);
    RUN_TEST(testPokemonTrainerAddPokemon);
    //RUN_TEST(testPokemonTrainerGetPokemon);
    RUN_TEST(testPokemonTrainerBuyItem);
    RUN_TEST(testPokemonTrainerGoHunt);
    RUN_TEST(testPokemonTrainerFight);
    RUN_TEST(testPokemonTrainerHealPokemon);
    RUN_TEST(testPokemonTrainerTrainPokemon);
    RUN_TEST(testTrainersCreateDestroy);
    RUN_TEST(testTrainersAddTrainer);
    RUN_TEST(testTrainersGetTrainer);


	return 0;
}
