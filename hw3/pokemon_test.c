#include <stdbool.h>
#include <string.h>
#include "aux_macros.h"
#include "pokemon.h"
#include "pokedex.h"

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
    TEST_EQUALS(result, pokemonCompare(pikachu, pikachu2), POKEMON_EQUAL);
    TEST_EQUALS(result, pokemonCompare(pikachu, squirtle), POKEMON_DIFFERENT);
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

static bool testPokemonCreate() {
	bool result = true;
    Pokedex pokedex = pokedexCreate();
    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pikachu_info);

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    TEST_DIFFERENT(result, pikachu, NULL);
    pokemonDestroy(pikachu);
    TEST_EQUALS(result,pokemonCreate("", TYPE_ELECTRIC, 20),NULL);
    TEST_EQUALS(result,pokemonCreate(NULL, TYPE_ELECTRIC, 20),NULL);
    TEST_EQUALS(result,pokemonCreate("Pikachu", TYPE_ELECTRIC, -20),NULL);
    return result;
}

static bool testPokemonDestroy() {
	bool result = true;
    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu);
	return result;
}

static bool testPokemonCopy() {
	bool result = true;
    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    Pokemon pikachu1 = pokemonCopy(pikachu);

    TEST_DIFFERENT(result, pikachu1, NULL);

    pokemonDestroy(pikachu1);
    pokemonDestroy(pikachu);
	return result;
}

static bool testPokemonUpdateLevel() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);

    TEST_EQUALS(result, pokemonUpdateLevel(pikachu,3), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetLevel(pikachu), 4);
    TEST_EQUALS(result, pokemonUpdateLevel(pikachu, -4),POKEMON_INVALID_VALUE);
    TEST_EQUALS(result, pokemonUpdateLevel(NULL, 2), POKEMON_NULL_ARG);

    pokemonDestroy(pikachu);
    return result;
}


static bool testPokemonUpdateHP() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);

    TEST_EQUALS(result, pokemonUpdateHP(pikachu,-30), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 70);
    TEST_EQUALS(result, pokemonUpdateHP(pikachu, 50),POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
    TEST_EQUALS(result, pokemonUpdateHP(pikachu, -100),
                POKEMON_NO_HEALTH_POINTS);

    pokemonDestroy(pikachu);

    return result;
}

static bool testPokemonUseItem() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    Item potion = itemCreate(TYPE_POTION, 50);
    Item candy = itemCreate(TYPE_CANDY, 10);

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


    return result;
}

static bool testPokemonCompare() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    Pokemon pikachu2 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    Pokemon pikachu3 = pokemonCreate("Pikachu", TYPE_NORMAL, 30);
    Pokemon pikach = pokemonCreate("Pikach", TYPE_ELECTRIC, 30);

    TEST_EQUALS(result, pokemonCompare(pikachu, pikachu2), POKEMON_EQUAL);
    TEST_EQUALS(result, pokemonCompare(pikachu, pikachu3), POKEMON_DIFFERENT);
    TEST_EQUALS(result, pokemonCompare(pikachu, pikach), POKEMON_DIFFERENT);
    TEST_EQUALS(result, pokemonCompare(pikachu, NULL), POKEMON_NULL_ARG);
    TEST_EQUALS(result, pokemonCompare(NULL, pikachu), POKEMON_NULL_ARG);



    pokemonDestroy(pikachu3);
    pokemonDestroy(pikachu2);
    pokemonDestroy(pikachu);
    pokemonDestroy(pikach);

    return result;
}

static bool testPokemonCheckEvolution() { //TODO: change this when function is ready
	bool result = true;

	return result;
}

int main() {
    RUN_TEST(testCombo);
	RUN_TEST(testPokemonCreate);
	RUN_TEST(testPokemonDestroy);
	RUN_TEST(testPokemonCopy);
    //RUN_TEST(testPokemonGetLevel);
    RUN_TEST(testPokemonUpdateLevel);
    //RUN_TEST(testPokemonGetHP);
    RUN_TEST(testPokemonUpdateHP);
    //RUN_TEST(testPokemonGetCP);
    RUN_TEST(testPokemonGetName);
    RUN_TEST(testPokemonUseItem);
    RUN_TEST(testPokemonCompare);
    RUN_TEST(testPokemonCheckEvolution);
    //RUN_TEST(testPokemonGetID);
    RUN_TEST(testPokemonUpdateID);
	return 0;
}
