#include <stdbool.h>
#include <string.h>
#include "aux_macros.h"
#include "pokemon.h"

static bool testCombo() {
	bool result = true;
	Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    	TEST_DIFFERENT(result, pikachu, NULL);
	Pokemon pikachu_copy = pokemonCopy(pikachu);
	TEST_DIFFERENT(result, pikachu_copy, NULL);
	pokemonDestroy(pikachu_copy);
	TEST_EQUALS(result, pokemonGetLevel(pikachu), 1);
    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
    //TEST_EQUALS(result, pokemonGetCP(pikachu), ????); //TODO: add pokedex tests too
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
    Pokemon pikachu2 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 50);
	Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10);
    TEST_EQUALS(result, pokemonCompare(pikachu, pikachu2), POKEMON_EQUAL);
    TEST_EQUALS(result, pokemonCompare(pikachu, squirtle), POKEMON_DIFFERENT);
	//TEST_EQUALS(result, pokemonCheckEvolution(pikachu)...???) //TODO: add when function is done

    TEST_EQUALS(result, pokemonGetNextPokemon(pikachu), NULL);

    pokemonDestroy(pikachu);
    pokemonDestroy(pikachu2);
    pokemonDestroy(squirtle);
	return result;

}

static bool testPokemonCreate() {
	bool result = true;
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
    // many tests for valgrind
    Pokemon pikachu0 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu0);
    Pokemon pikachu1 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu1);
    Pokemon pikachu2 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu2);
    Pokemon pikachu3 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu3);
    Pokemon pikachu4 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu4);
    Pokemon pikachu5 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu5);
    Pokemon pikachu6 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu6);
    Pokemon pikachu7 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu7);
    Pokemon pikachu8 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu8);
    Pokemon pikachu9 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu9);
    Pokemon pikachu10 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu10);
    Pokemon pikachu11 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu11);
    Pokemon pikachu12 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu12);
    Pokemon pikachu13 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu13);
    Pokemon pikachu14 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu14);
    Pokemon pikachu15 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu15);
    Pokemon pikachu16 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu16);
    Pokemon pikachu17 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu17);
    Pokemon pikachu18 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu18);
    Pokemon pikachu19 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu19);
    Pokemon pikachu20 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu20);
    Pokemon pikachu21 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu21);
    Pokemon pikachu22 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu22);
    Pokemon pikachu23 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu23);
    Pokemon pikachu24 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu24);
    Pokemon pikachu25 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu25);
    Pokemon pikachu26 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu26);
    Pokemon pikachu27 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu27);
    Pokemon pikachu28 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu28);
    Pokemon pikachu29 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    pokemonDestroy(pikachu29);
	return result;
}

static bool testPokemonCopy() {
	bool result = true;
    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
    // many tests for valgrid
    Pokemon pikachu0 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu0, NULL);
    pokemonDestroy(pikachu0);
    Pokemon pikachu1 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu1, NULL);
    pokemonDestroy(pikachu1);
    Pokemon pikachu2 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu2, NULL);
    pokemonDestroy(pikachu2);
    Pokemon pikachu3 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu3, NULL);
    pokemonDestroy(pikachu3);
    Pokemon pikachu4 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu4, NULL);
    pokemonDestroy(pikachu4);
    Pokemon pikachu5 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu5, NULL);
    pokemonDestroy(pikachu5);
    Pokemon pikachu6 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu6, NULL);
    pokemonDestroy(pikachu6);
    Pokemon pikachu7 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu7, NULL);
    pokemonDestroy(pikachu7);
    Pokemon pikachu8 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu8, NULL);
    pokemonDestroy(pikachu8);
    Pokemon pikachu9 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu9, NULL);
    pokemonDestroy(pikachu9);
    Pokemon pikachu10 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu10, NULL);
    pokemonDestroy(pikachu10);
    Pokemon pikachu11 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu11, NULL);
    pokemonDestroy(pikachu11);
    Pokemon pikachu12 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu12, NULL);
    pokemonDestroy(pikachu12);
    Pokemon pikachu13 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu13, NULL);
    pokemonDestroy(pikachu13);
    Pokemon pikachu14 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu14, NULL);
    pokemonDestroy(pikachu14);
    Pokemon pikachu15 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu15, NULL);
    pokemonDestroy(pikachu15);
    Pokemon pikachu16 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu16, NULL);
    pokemonDestroy(pikachu16);
    Pokemon pikachu17 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu17, NULL);
    pokemonDestroy(pikachu17);
    Pokemon pikachu18 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu18, NULL);
    pokemonDestroy(pikachu18);
    Pokemon pikachu19 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu19, NULL);
    pokemonDestroy(pikachu19);
    Pokemon pikachu20 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu20, NULL);
    pokemonDestroy(pikachu20);
    Pokemon pikachu21 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu21, NULL);
    pokemonDestroy(pikachu21);
    Pokemon pikachu22 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu22, NULL);
    pokemonDestroy(pikachu22);
    Pokemon pikachu23 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu23, NULL);
    pokemonDestroy(pikachu23);
    Pokemon pikachu24 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu24, NULL);
    pokemonDestroy(pikachu24);
    Pokemon pikachu25 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu25, NULL);
    pokemonDestroy(pikachu25);
    Pokemon pikachu26 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu26, NULL);
    pokemonDestroy(pikachu26);
    Pokemon pikachu27 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu27, NULL);
    pokemonDestroy(pikachu27);
    Pokemon pikachu28 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu28, NULL);
    pokemonDestroy(pikachu28);
    Pokemon pikachu29 = pokemonCopy(pikachu);
    TEST_DIFFERENT(result, pikachu29, NULL);
    pokemonDestroy(pikachu29);

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
    RUN_TEST(testPokemonUpdateLevel);
    RUN_TEST(testPokemonUpdateHP);
    RUN_TEST(testPokemonUseItem);
    RUN_TEST(testPokemonCompare);
    RUN_TEST(testPokemonCheckEvolution);
	return 0;
}
