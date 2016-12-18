#include <stdbool.h>
#include "aux_macros.h"
#include "pokemon.h"

static bool testCombo() {
	bool result = true;
	Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    	TEST_DIFFERENT(result, pikachu, NULL);
	Pokemon pikachu_copy = pokemonCopy(pikachu);
	TEST_DIFFERENT(result, pikachu_copy, NULL);
	pokemonDestroy(pikachu_copy);
	TEST_EQUALS(result, pokemonTeachMove(
		pikachu, "Thunder", TYPE_ELECTRIC, 10, 110), POKEMON_SUCCESS);
	TEST_EQUALS(result, pokemonUnteachMove(pikachu, "Thunder"), POKEMON_SUCCESS);
	TEST_EQUALS(result, pokemonGetLevel(pikachu), 1);
	TEST_EQUALS(result, pokemonGetRank(pikachu), 0);
	Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
	pokemonTeachMove(squirtle, "Bubble", TYPE_WATER, 30, 40);
	TEST_EQUALS(result, pokemonUseMove(
		squirtle, pikachu, "Bubble"), POKEMON_SUCCESS);
	TEST_EQUALS(result, pokemonHeal(pikachu), POKEMON_SUCCESS);
	TEST_EQUALS(result, pokemonEvolve(squirtle, "Wartortle"), POKEMON_SUCCESS);
	pokemonDestroy(pikachu);
	pokemonDestroy(squirtle);
	return result;
}

static bool testPokemonCreate() {
	bool result = true;
    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    TEST_DIFFERENT(result, pikachu, NULL);
    pokemonDestroy(pikachu);
    TEST_EQUALS(result,pokemonCreate("", TYPE_ELECTRIC, 20, 4),NULL);
    TEST_EQUALS(result,pokemonCreate(NULL, TYPE_ELECTRIC, 20, 4),NULL);
    TEST_EQUALS(result,pokemonCreate("Pikachu", TYPE_ELECTRIC, -20, 4),NULL);
    TEST_EQUALS(result,pokemonCreate("Pikachu", TYPE_ELECTRIC, 20000, 4),NULL);
    TEST_EQUALS(result,pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, -4),NULL);
    return result;
}

static bool testPokemonDestroy() {
	bool result = true;
    // many tests for valgrind
    Pokemon pikachu0 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu0);
    Pokemon pikachu1 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu1);
    Pokemon pikachu2 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu2);
    Pokemon pikachu3 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu3);
    Pokemon pikachu4 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu4);
    Pokemon pikachu5 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu5);
    Pokemon pikachu6 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu6);
    Pokemon pikachu7 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu7);
    Pokemon pikachu8 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu8);
    Pokemon pikachu9 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu9);
    Pokemon pikachu10 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu10);
    Pokemon pikachu11 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu11);
    Pokemon pikachu12 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu12);
    Pokemon pikachu13 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu13);
    Pokemon pikachu14 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu14);
    Pokemon pikachu15 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu15);
    Pokemon pikachu16 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu16);
    Pokemon pikachu17 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu17);
    Pokemon pikachu18 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu18);
    Pokemon pikachu19 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu19);
    Pokemon pikachu20 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu20);
    Pokemon pikachu21 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu21);
    Pokemon pikachu22 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu22);
    Pokemon pikachu23 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu23);
    Pokemon pikachu24 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu24);
    Pokemon pikachu25 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu25);
    Pokemon pikachu26 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu26);
    Pokemon pikachu27 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu27);
    Pokemon pikachu28 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu28);
    Pokemon pikachu29 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    pokemonDestroy(pikachu29);
	return result;
}

static bool testPokemonCopy() {
	bool result = true;
    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
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

static bool testPokemonGetLevel() {
	bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 1, 4);
    TEST_DIFFERENT(result, pikachu, NULL);

    TEST_EQUALS(result, pokemonGetLevel(pikachu), 1);
    pokemonDestroy(pikachu);
    pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 100, 4);
    TEST_EQUALS(result, pokemonGetLevel(pikachu), 1);
    pokemonDestroy(pikachu);
    pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 101, 4);
    TEST_EQUALS(result, pokemonGetLevel(pikachu), 2);
    pokemonDestroy(pikachu);
    pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 9901, 4);
    TEST_EQUALS(result, pokemonGetLevel(pikachu), 100);
    pokemonDestroy(pikachu);

	return result;
}

static bool testPokemonEvolve() {
	bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    TEST_DIFFERENT(result, pikachu, NULL);
    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_DIFFERENT(result, squirtle, NULL);

    TEST_EQUALS(result, pokemonEvolve(squirtle, "Wartortle"), POKEMON_SUCCESS);
    TEST_EQUALS(result, squirtle->experience, 101);
    pokemonDestroy(squirtle);

    squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_DIFFERENT(result, squirtle, NULL);

    TEST_EQUALS(result, pokemonTeachMove(
            pikachu, "Thunder", TYPE_ELECTRIC, 2, 600), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonUseMove(
            pikachu, squirtle, "Thunder"), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonEvolve(squirtle, "Wartortle"), POKEMON_SUCCESS);
    pokemonDestroy(squirtle);

    squirtle = pokemonCreate("Squirtle", TYPE_WATER, 9901, 4);
    TEST_DIFFERENT(result, squirtle, NULL);
    TEST_EQUALS(result, pokemonEvolve(squirtle, "Wartortle"),
                POKEMON_CANNOT_EVOLVE);
    TEST_EQUALS(result, pokemonEvolve(NULL, "Raichu"),POKEMON_NULL_ARG);
    TEST_EQUALS(result, pokemonEvolve(pikachu, NULL),POKEMON_NULL_ARG);
    TEST_EQUALS(result, pokemonEvolve(pikachu, ""),POKEMON_INVALID_NAME);

    pokemonDestroy(pikachu);
    pokemonDestroy(squirtle);

	return result;
}

int main() {
    RUN_TEST(testCombo);
	RUN_TEST(testPokemonCreate);
	RUN_TEST(testPokemonDestroy);
	RUN_TEST(testPokemonCopy);
	RUN_TEST(testPokemonGetLevel);
	RUN_TEST(testPokemonEvolve);
	return 0;
}
