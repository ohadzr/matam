//#include <stdbool.h>
//#include <string.h>
//#include "aux_macros.h"
//#include "pokemon.h"
//#include "pokedex.h"
//
//static bool testCombo() {
//	bool result = true;
//    Pokedex pokedex = pokedexCreate();
//
//	Pokemon pikachu = pokemonCreate("Pikachu", pokedex);
//    	TEST_DIFFERENT(result, pikachu, NULL);
//	Pokemon pikachu_copy = pokemonCopy(pikachu);
//	TEST_DIFFERENT(result, pikachu_copy, NULL);
//	pokemonDestroy(pikachu_copy);
//	TEST_EQUALS(result, pokemonGetLevel(pikachu), 1);
//    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
//    //TEST_EQUALS(result, pokemonGetCP(pikachu), ????); //TODO: add pokedex tests too
//    TEST_EQUALS(result, strcmp(pokemonGetName(pikachu),"Pikachu"), 0);
//    TEST_EQUALS(result, pokemonUpdateHP(pikachu, 20),POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
//    TEST_EQUALS(result, pokemonUpdateHP(pikachu, -50),POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonGetHP(pikachu), 50);
//    TEST_EQUALS(result, pokemonUpdateHP(pikachu, -70),POKEMON_NO_HEALTH_POINTS);
//    TEST_EQUALS(result, pokemonGetHP(pikachu), 0);
//    TEST_EQUALS(result, pokemonGetCP(pikachu), 30);
//    TEST_EQUALS(result, pokemonUpdateLevel(pikachu,2), POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonGetLevel(pikachu), 3);
//    Pokemon pikachu2 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 50);
//	Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10);
//    TEST_EQUALS(result, pokemonCompare(pikachu, pikachu2), POKEMON_EQUAL);
//    TEST_EQUALS(result, pokemonCompare(pikachu, squirtle), POKEMON_DIFFERENT);
//	//TEST_EQUALS(result, pokemonCheckEvolution(pikachu)...???) //TODO: add when function is done
//
//    TEST_EQUALS(result, pokemonGetNextPokemon(pikachu), NULL);
//
//    pokemonDestroy(pikachu);
//    pokemonDestroy(pikachu2);
//    pokemonDestroy(squirtle);
//	return result;
//
//}
//
//static bool testPokemonCreate() {
//	bool result = true;
//    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//    TEST_DIFFERENT(result, pikachu, NULL);
//    pokemonDestroy(pikachu);
//    TEST_EQUALS(result,pokemonCreate("", TYPE_ELECTRIC, 20),NULL);
//    TEST_EQUALS(result,pokemonCreate(NULL, TYPE_ELECTRIC, 20),NULL);
//    TEST_EQUALS(result,pokemonCreate("Pikachu", TYPE_ELECTRIC, -20),NULL);
//    return result;
//}
//
//static bool testPokemonDestroy() {
//	bool result = true;
//    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//    pokemonDestroy(pikachu);
//	return result;
//}
//
//static bool testPokemonCopy() {
//	bool result = true;
//    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//    Pokemon pikachu1 = pokemonCopy(pikachu);
//
//    TEST_DIFFERENT(result, pikachu1, NULL);
//
//    pokemonDestroy(pikachu1);
//    pokemonDestroy(pikachu);
//	return result;
//}
//
//static bool testPokemonUpdateLevel() {
//    bool result = true;
//
//    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//
//    TEST_EQUALS(result, pokemonUpdateLevel(pikachu,3), POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonGetLevel(pikachu), 4);
//    TEST_EQUALS(result, pokemonUpdateLevel(pikachu, -4),POKEMON_INVALID_VALUE);
//    TEST_EQUALS(result, pokemonUpdateLevel(NULL, 2), POKEMON_NULL_ARG);
//
//    pokemonDestroy(pikachu);
//    return result;
//}
//
//
//static bool testPokemonUpdateHP() {
//    bool result = true;
//
//    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//
//    TEST_EQUALS(result, pokemonUpdateHP(pikachu,-30), POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonGetHP(pikachu), 70);
//    TEST_EQUALS(result, pokemonUpdateHP(pikachu, 50),POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
//    TEST_EQUALS(result, pokemonUpdateHP(pikachu, -100),
//                POKEMON_NO_HEALTH_POINTS);
//
//    pokemonDestroy(pikachu);
//
//    return result;
//}
//
//static bool testPokemonUseItem() {
//    bool result = true;
//
//    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//    Item potion = itemCreate(TYPE_POTION, 50);
//    Item candy = itemCreate(TYPE_CANDY, 10);
//
//    TEST_EQUALS(result, pokemonUpdateHP(pikachu,-30), POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonUseItem(pikachu, potion), POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonUseItem(pikachu, candy), POKEMON_SUCCESS);
//    TEST_EQUALS(result, pokemonGetHP(pikachu), 100);
//    TEST_EQUALS(result, pokemonGetCP(pikachu), 40);
//
//    TEST_EQUALS(result, pokemonUseItem(NULL, potion), POKEMON_NULL_ARG);
//    TEST_EQUALS(result, pokemonUseItem(pikachu, NULL), POKEMON_NULL_ARG);
//
//
//    itemDestroy(potion);
//    itemDestroy(candy);
//    pokemonDestroy(pikachu);
//
//
//    return result;
//}
//
//static bool testPokemonCompare() {
//    bool result = true;
//
//    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//    Pokemon pikachu2 = pokemonCreate("Pikachu", TYPE_ELECTRIC, 30);
//    Pokemon pikachu3 = pokemonCreate("Pikachu", TYPE_NORMAL, 30);
//    Pokemon pikach = pokemonCreate("Pikach", TYPE_ELECTRIC, 30);
//
//    TEST_EQUALS(result, pokemonCompare(pikachu, pikachu2), POKEMON_EQUAL);
//    TEST_EQUALS(result, pokemonCompare(pikachu, pikachu3), POKEMON_DIFFERENT);
//    TEST_EQUALS(result, pokemonCompare(pikachu, pikach), POKEMON_DIFFERENT);
//    TEST_EQUALS(result, pokemonCompare(pikachu, NULL), POKEMON_NULL_ARG);
//    TEST_EQUALS(result, pokemonCompare(NULL, pikachu), POKEMON_NULL_ARG);
//
//
//
//    pokemonDestroy(pikachu3);
//    pokemonDestroy(pikachu2);
//    pokemonDestroy(pikachu);
//    pokemonDestroy(pikach);
//
//    return result;
//}
//
//static bool testPokemonCheckEvolution() { //TODO: change this when function is ready
//	bool result = true;
//
//	return result;
//}
//
//int main() {
//    RUN_TEST(testCombo);
//	RUN_TEST(testPokemonCreate);
//	RUN_TEST(testPokemonDestroy);
//	RUN_TEST(testPokemonCopy);
//    //RUN_TEST(testPokemonGetLevel);
//    RUN_TEST(testPokemonUpdateLevel);
//    //RUN_TEST(testPokemonGetHP);
//    RUN_TEST(testPokemonUpdateHP);
//    //RUN_TEST(testPokemonGetCP);
//    RUN_TEST(testPokemonGetName);
//    RUN_TEST(testPokemonUseItem);
//    RUN_TEST(testPokemonCompare);
//    RUN_TEST(testPokemonCheckEvolution);
//    //RUN_TEST(testPokemonGetID);
//    RUN_TEST(testPokemonUpdateID);
//	return 0;
//}
