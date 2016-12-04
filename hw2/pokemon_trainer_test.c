#include <stdbool.h>
#include "aux_macros.h"
#include "pokemon_trainer.h"

static bool testCombo() {
	bool result = true;
	Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
	PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 6, 20);
	TEST_DIFFERENT(result, trainer, NULL);
	pokemonDestroy(pikachu);
	PokemonTrainer trainer_copy = pokemonTrainerCopy(trainer);
	TEST_DIFFERENT(result, trainer_copy, NULL);
	pokemonTrainerDestroy(trainer_copy);
	Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
	TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
		POKEMON_TRAINER_SUCCESS);
	pokemonDestroy(squirtle);
	TEST_EQUALS(result, pokemonTrainerGetNumberOfPokemons(trainer), 2);
	TEST_DIFFERENT(result, pokemonTrainerGetPokemon(trainer, 2), NULL);
	TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer, 2),
		POKEMON_TRAINER_SUCCESS);
	TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(trainer, 1),
		POKEMON_TRAINER_SUCCESS);
	TEST_EQUALS(result, pokemonTrainerRemovePokemon(trainer, 2),
		POKEMON_TRAINER_SUCCESS);
	TEST_EQUALS(result, pokemonTrainerGetMostRankedPokemon(trainer),
		pokemonTrainerGetPokemon(trainer, 1));
	TEST_EQUALS(result, pokemonTrainerMakeMostRankedParty(trainer),
		POKEMON_TRAINER_SUCCESS);
	pokemonTrainerDestroy(trainer);
	return result;
}

static bool testPokemonTrainerCreate() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerDestroy() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerCopy() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerAddPokemon() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerGetPokemon() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerRemovePokemon() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerDepositPokemon() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerWithdrawPokemon() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerGetNumberOfPokemons() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerGetMostRankedPokemon() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerMakeMostRankedParty() {
    bool result = true;


    return result;
}

static bool testPokemonTrainerPrintEnumeration() {
    bool result = true;


    return result;
}


int main() {
	RUN_TEST(testCombo);
	// MY_TESTS
	RUN_TEST(testPokemonTrainerCreate);
    RUN_TEST(testPokemonTrainerDestroy);
    RUN_TEST(testPokemonTrainerCopy);
    RUN_TEST(testPokemonTrainerAddPokemon);
    RUN_TEST(testPokemonTrainerGetPokemon);
    RUN_TEST(testPokemonTrainerRemovePokemon);
    RUN_TEST(testPokemonTrainerDepositPokemon);
    RUN_TEST(testPokemonTrainerWithdrawPokemon);
    RUN_TEST(testPokemonTrainerGetNumberOfPokemons);
    RUN_TEST(testPokemonTrainerGetMostRankedPokemon);
    RUN_TEST(testPokemonTrainerMakeMostRankedParty);
    RUN_TEST(testPokemonTrainerPrintEnumeration);
	return 0;
}
