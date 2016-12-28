#include <stdbool.h>
#include <string.h>
#include "aux_macros.h"
#include "pokemon.h"

static bool testCombo() {
	bool result = true;
    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 30);
    pokedexAddPokemonInfo(pokedex, pikachu_info);
    pokedexAddPokemonInfo(pokedex, raichu_info);
    pokedexUpdateNextEvolution(pokedex, "Pikachu","Raichu", 6);


	Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
    TEST_DIFFERENT(result, pikachu, NULL);
	Pokemon pikachu_copy = pokemonCopy(pikachu);
	TEST_DIFFERENT(result, pikachu_copy, NULL);
	pokemonDestroy(pikachu_copy);
	TEST_EQUALS(result, pokemonGetLevel(pikachu), 1);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
    TEST_EQUALS(result, pokemonGetCP(pikachu), 10);
    TEST_EQUALS(result, strcmp(pokemonGetName(pikachu),"Pikachu"), 0);
    TEST_EQUALS(result, pokemonUpdateHP(pikachu, 20),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
    TEST_EQUALS(result, pokemonUpdateHP(pikachu, -50),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 50);
    TEST_EQUALS(result, pokemonUpdateHP(pikachu, -70),POKEMON_NO_HEALTH_POINTS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 0);
    TEST_EQUALS(result, pokemonGetCP(pikachu), 30);
    TEST_EQUALS(result, pokemonUpdateLevel(pikachu,2), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetLevel(pikachu), 3);
    Pokemon pikachu2 = pokemonCreate("Pikachu", pokedex);
    TEST_EQUALS(result, pokemonUpdateID(pikachu, 1),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonUpdateID(pikachu2, 1),POKEMON_SUCCESS);
    PokemonInfo squirtle_info = pokedexPokemonInfoCreate("Squirtle", 15);
    pokedexAddPokemonInfo(pokedex, squirtle_info);
	Pokemon squirtle = pokemonCreate("Squirtle", pokedex);
    TEST_EQUALS(result, pokemonUpdateID(squirtle, 2),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonCompareByID(pikachu, pikachu2), POKEMON_EQUAL);
    TEST_EQUALS(result, pokemonCompareByID(pikachu, squirtle), POKEMON_DIFFERENT);
	TEST_EQUALS(result, pokemonCheckEvolution(pikachu,pokedex),POKEMON_SUCCESS);


    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexPokemonInfoDestroy(raichu_info);
    pokedexPokemonInfoDestroy(squirtle_info);
    pokedexDestroy(pokedex);
    pokemonDestroy(pikachu);
    pokemonDestroy(pikachu2);
    pokemonDestroy(squirtle);
	return result;

}

static bool testPokemonCreateDestroy() {
	bool result = true;
    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
    TEST_DIFFERENT(result, pikachu, NULL);
    pokemonDestroy(pikachu);
    TEST_EQUALS(result,pokemonCreate("",pokedex),NULL);
    TEST_EQUALS(result,pokemonCreate(NULL, pokedex),NULL);
    TEST_EQUALS(result,pokemonCreate("Pikachu", NULL),NULL);

    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);
    pokemonDestroy(pikachu);

    return result;
}

static bool testPokemonCopy() {
	bool result = true;
    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
    Pokemon pikachu1 = pokemonCopy(pikachu);

    TEST_DIFFERENT(result, pikachu1, NULL);
    TEST_EQUALS(result, pokemonGetLevel(pikachu), pokemonGetLevel(pikachu1));
    TEST_EQUALS(result, pokemonGetHP(pikachu), pokemonGetHP(pikachu1));
    TEST_EQUALS(result, pokemonGetCP(pikachu), pokemonGetCP(pikachu1));
    TEST_EQUALS(result, strcmp(pokemonGetName(pikachu),
                               pokemonGetName(pikachu1)), 0);

    pokemonDestroy(pikachu1);
    pokemonDestroy(pikachu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);

	return result;
}

static bool testPokemonUpdateLevel() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);

    TEST_EQUALS(result, pokemonUpdateLevel(pikachu,3), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetLevel(pikachu), 4);
    TEST_EQUALS(result, pokemonUpdateLevel(pikachu, -4),POKEMON_INVALID_VALUE);
    TEST_EQUALS(result, pokemonUpdateLevel(NULL, 2), POKEMON_NULL_ARG);


    pokemonDestroy(pikachu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);

    return result;
}


static bool testPokemonUpdateHP() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);

    TEST_EQUALS(result, pokemonUpdateHP(pikachu,-30), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 70);
    TEST_EQUALS(result, pokemonUpdateHP(pikachu, 50),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
    TEST_EQUALS(result, pokemonUpdateHP(pikachu, -100),
                POKEMON_NO_HEALTH_POINTS);

    pokemonDestroy(pikachu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);

    return result;
}

static bool testPokemonUseItem() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);

    Item potion = itemCreate(50, TYPE_POTION);
    Item candy = itemCreate(10, TYPE_CANDY);

    TEST_EQUALS(result, pokemonUpdateHP(pikachu,-30), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonUseItem(pikachu, potion), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonUseItem(pikachu, candy), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
    TEST_EQUALS(result, pokemonGetCP(pikachu), 40);

    TEST_EQUALS(result, pokemonUseItem(NULL, potion), POKEMON_NULL_ARG);
    TEST_EQUALS(result, pokemonUseItem(pikachu, NULL), POKEMON_NULL_ARG);


    itemDestroy(potion);
    itemDestroy(candy);
    pokemonDestroy(pikachu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);


    return result;
}

static bool testPokemonCompare() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
    Pokemon pikachu2 = pokemonCopy(pikachu);
    Pokemon pikachu3 = pokemonCreate("Pikachu", pokedex);

    TEST_EQUALS(result, pokemonUpdateID(pikachu, 1),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonUpdateID(pikachu2, 1),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonUpdateID(pikachu3, 2),POKEMON_SUCCESS);


    TEST_EQUALS(result, pokemonCompareByID(pikachu, pikachu2), POKEMON_EQUAL);
    TEST_EQUALS(result, pokemonCompareByID(pikachu, pikachu3), POKEMON_DIFFERENT);
    TEST_EQUALS(result, pokemonCompareByID(pikachu, NULL), POKEMON_NULL_ARG);
    TEST_EQUALS(result, pokemonCompareByID(NULL, pikachu), POKEMON_NULL_ARG);



    pokemonDestroy(pikachu3);
    pokemonDestroy(pikachu2);
    pokemonDestroy(pikachu);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);

    return result;
}

static bool testPokemonCheckEvolution() {
	bool result = true;

    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 30);
    PokemonInfo big_raichu_info = pokedexPokemonInfoCreate("BigRaichu", 50);
    pokedexAddPokemonInfo(pokedex, pikachu_info);
    pokedexAddPokemonInfo(pokedex, raichu_info);
    pokedexAddPokemonInfo(pokedex, big_raichu_info);
    pokedexUpdateNextEvolution(pokedex, "Pikachu","Raichu", 6);
    pokedexUpdateNextEvolution(pokedex, "Raichu", "BigRaichu", 10);

    Pokemon pikachu = pokemonCreate("Pikachu", pokedex);

    TEST_EQUALS(result, pokemonCheckEvolution(pikachu, pokedex),
                POKEMON_CANT_EVOLVE);
    TEST_EQUALS(result, pokemonUpdateLevel(pikachu,5),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonCheckEvolution(pikachu, pokedex),
                POKEMON_SUCCESS);
    TEST_EQUALS(result, strcmp(pokemonGetName(pikachu),"Raichu") , 0);
    TEST_EQUALS(result, pokemonUpdateLevel(pikachu,5),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonCheckEvolution(pikachu, pokedex),
                POKEMON_SUCCESS);
    TEST_EQUALS(result, strcmp(pokemonGetName(pikachu),"BigRaichu") , 0);

    pokedexPokemonInfoDestroy(big_raichu_info);
    pokedexPokemonInfoDestroy(raichu_info);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokemonDestroy(pikachu);
    pokedexDestroy(pokedex);

	return result;
}

int main() {
    RUN_TEST(testCombo);
	RUN_TEST(testPokemonCreateDestroy);
	RUN_TEST(testPokemonCopy);
    //RUN_TEST(testPokemonGetLevel);
    RUN_TEST(testPokemonUpdateLevel);
    //RUN_TEST(testPokemonGetHP);
    RUN_TEST(testPokemonUpdateHP);
    //RUN_TEST(testPokemonGetCP);
    RUN_TEST(testPokemonUseItem);
    RUN_TEST(testPokemonCompare);
    RUN_TEST(testPokemonCheckEvolution);
	return 0;
}
