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

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer0 = pokemonTrainerCreate(NULL, pikachu, 6, 20);
    TEST_EQUALS(result, trainer0, NULL);
    PokemonTrainer trainer1 = pokemonTrainerCreate("Ash", NULL, 6, 20);
    TEST_EQUALS(result, trainer1, NULL);
    PokemonTrainer trainer2 = pokemonTrainerCreate("Ash", pikachu, -6, 20);
    TEST_EQUALS(result, trainer2, NULL);
    PokemonTrainer trainer3 = pokemonTrainerCreate("Ash", pikachu, 6, -20);
    TEST_EQUALS(result, trainer3, NULL);

    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer, NULL);

    pokemonDestroy(pikachu);
    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerDestroy() {
    bool result = true;
    // many tests for valgrid
    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);

    PokemonTrainer trainer0 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer0, NULL);
    pokemonTrainerDestroy(trainer0);
    PokemonTrainer trainer1 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer1, NULL);
    pokemonTrainerDestroy(trainer1);
    PokemonTrainer trainer2 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer2, NULL);
    pokemonTrainerDestroy(trainer2);
    PokemonTrainer trainer3 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer3, NULL);
    pokemonTrainerDestroy(trainer3);
    PokemonTrainer trainer4 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer4, NULL);
    pokemonTrainerDestroy(trainer4);
    PokemonTrainer trainer5 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer5, NULL);
    pokemonTrainerDestroy(trainer5);
    PokemonTrainer trainer6 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer6, NULL);
    pokemonTrainerDestroy(trainer6);
    PokemonTrainer trainer7 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer7, NULL);
    pokemonTrainerDestroy(trainer7);
    PokemonTrainer trainer8 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer8, NULL);
    pokemonTrainerDestroy(trainer8);
    PokemonTrainer trainer9 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer9, NULL);
    pokemonTrainerDestroy(trainer9);
    PokemonTrainer trainer10 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer10, NULL);
    pokemonTrainerDestroy(trainer10);
    PokemonTrainer trainer11 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer11, NULL);
    pokemonTrainerDestroy(trainer11);
    PokemonTrainer trainer12 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer12, NULL);
    pokemonTrainerDestroy(trainer12);
    PokemonTrainer trainer13 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer13, NULL);
    pokemonTrainerDestroy(trainer13);
    PokemonTrainer trainer14 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer14, NULL);
    pokemonTrainerDestroy(trainer14);
    PokemonTrainer trainer15 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer15, NULL);
    pokemonTrainerDestroy(trainer15);
    PokemonTrainer trainer16 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer16, NULL);
    pokemonTrainerDestroy(trainer16);
    PokemonTrainer trainer17 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer17, NULL);
    pokemonTrainerDestroy(trainer17);
    PokemonTrainer trainer18 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer18, NULL);
    pokemonTrainerDestroy(trainer18);
    PokemonTrainer trainer19 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer19, NULL);
    pokemonTrainerDestroy(trainer19);
    PokemonTrainer trainer20 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer20, NULL);
    pokemonTrainerDestroy(trainer20);
    PokemonTrainer trainer21 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer21, NULL);
    pokemonTrainerDestroy(trainer21);
    PokemonTrainer trainer22 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer22, NULL);
    pokemonTrainerDestroy(trainer22);
    PokemonTrainer trainer23 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer23, NULL);
    pokemonTrainerDestroy(trainer23);
    PokemonTrainer trainer24 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer24, NULL);
    pokemonTrainerDestroy(trainer24);
    PokemonTrainer trainer25 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer25, NULL);
    pokemonTrainerDestroy(trainer25);
    PokemonTrainer trainer26 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer26, NULL);
    pokemonTrainerDestroy(trainer26);
    PokemonTrainer trainer27 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer27, NULL);
    pokemonTrainerDestroy(trainer27);
    PokemonTrainer trainer28 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer28, NULL);
    pokemonTrainerDestroy(trainer28);
    PokemonTrainer trainer29 = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    TEST_DIFFERENT(result, trainer29, NULL);
    pokemonTrainerDestroy(trainer29);

    pokemonDestroy(pikachu);

    return result;
}

static bool testPokemonTrainerCopy() {
    bool result = true;

    TEST_EQUALS(result, pokemonTrainerCopy(NULL), NULL);

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 6, 20);
    pokemonDestroy(pikachu);

    // many tests for valgrid
    PokemonTrainer trainer0 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer0, NULL);
    pokemonTrainerDestroy(trainer0);
    PokemonTrainer trainer1 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer1, NULL);
    pokemonTrainerDestroy(trainer1);
    PokemonTrainer trainer2 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer2, NULL);
    pokemonTrainerDestroy(trainer2);
    PokemonTrainer trainer3 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer3, NULL);
    pokemonTrainerDestroy(trainer3);
    PokemonTrainer trainer4 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer4, NULL);
    pokemonTrainerDestroy(trainer4);
    PokemonTrainer trainer5 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer5, NULL);
    pokemonTrainerDestroy(trainer5);
    PokemonTrainer trainer6 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer6, NULL);
    pokemonTrainerDestroy(trainer6);
    PokemonTrainer trainer7 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer7, NULL);
    pokemonTrainerDestroy(trainer7);
    PokemonTrainer trainer8 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer8, NULL);
    pokemonTrainerDestroy(trainer8);
    PokemonTrainer trainer9 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer9, NULL);
    pokemonTrainerDestroy(trainer9);
    PokemonTrainer trainer10 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer10, NULL);
    pokemonTrainerDestroy(trainer10);
    PokemonTrainer trainer11 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer11, NULL);
    pokemonTrainerDestroy(trainer11);
    PokemonTrainer trainer12 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer12, NULL);
    pokemonTrainerDestroy(trainer12);
    PokemonTrainer trainer13 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer13, NULL);
    pokemonTrainerDestroy(trainer13);
    PokemonTrainer trainer14 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer14, NULL);
    pokemonTrainerDestroy(trainer14);
    PokemonTrainer trainer15 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer15, NULL);
    pokemonTrainerDestroy(trainer15);
    PokemonTrainer trainer16 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer16, NULL);
    pokemonTrainerDestroy(trainer16);
    PokemonTrainer trainer17 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer17, NULL);
    pokemonTrainerDestroy(trainer17);
    PokemonTrainer trainer18 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer18, NULL);
    pokemonTrainerDestroy(trainer18);
    PokemonTrainer trainer19 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer19, NULL);
    pokemonTrainerDestroy(trainer19);
    PokemonTrainer trainer20 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer20, NULL);
    pokemonTrainerDestroy(trainer20);
    PokemonTrainer trainer21 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer21, NULL);
    pokemonTrainerDestroy(trainer21);
    PokemonTrainer trainer22 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer22, NULL);
    pokemonTrainerDestroy(trainer22);
    PokemonTrainer trainer23 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer23, NULL);
    pokemonTrainerDestroy(trainer23);
    PokemonTrainer trainer24 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer24, NULL);
    pokemonTrainerDestroy(trainer24);
    PokemonTrainer trainer25 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer25, NULL);
    pokemonTrainerDestroy(trainer25);
    PokemonTrainer trainer26 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer26, NULL);
    pokemonTrainerDestroy(trainer26);
    PokemonTrainer trainer27 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer27, NULL);
    pokemonTrainerDestroy(trainer27);
    PokemonTrainer trainer28 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer28, NULL);
    pokemonTrainerDestroy(trainer28);
    PokemonTrainer trainer29 = pokemonTrainerCopy(trainer);
    TEST_DIFFERENT(result, trainer29, NULL);
    pokemonTrainerDestroy(trainer29);

    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerAddPokemon() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 3, 20);
    pokemonDestroy(pikachu);

    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(NULL, squirtle),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, NULL),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_PARTY_FULL);

    pokemonDestroy(squirtle);

    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerGetPokemon() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 3, 20);
    pokemonDestroy(pikachu);
    TEST_DIFFERENT(result, pokemonTrainerGetPokemon(trainer, 1), NULL);
    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    pokemonDestroy(squirtle);
    TEST_DIFFERENT(result, pokemonTrainerGetPokemon(trainer, 2), NULL);
    TEST_EQUALS(result, pokemonTrainerGetPokemon(trainer, 3), NULL);
    TEST_EQUALS(result, pokemonTrainerGetPokemon(NULL, 1), NULL);

    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerRemovePokemon() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 3, 20);
    pokemonDestroy(pikachu);

    TEST_EQUALS(result, pokemonTrainerRemovePokemon(NULL,1),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerRemovePokemon(trainer,2),
                POKEMON_TRAINER_INVALID_INDEX);
    TEST_EQUALS(result, pokemonTrainerRemovePokemon(trainer,1),
                POKEMON_TRAINER_REMOVE_LAST);

    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    pokemonDestroy(squirtle);

    squirtle = pokemonTrainerGetPokemon(trainer,2);
    TEST_EQUALS(result, pokemonTrainerRemovePokemon(trainer,1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerGetPokemon(trainer,1),squirtle);

    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerDepositPokemon() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 4, 2);
    pokemonDestroy(pikachu);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(NULL,1),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,2),
                POKEMON_TRAINER_INVALID_INDEX);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,0),
                POKEMON_TRAINER_INVALID_INDEX);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,1),
                POKEMON_TRAINER_DEPOSIT_LAST);

    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    pokemonDestroy(squirtle);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,4),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,3),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,2),
                POKEMON_TRAINER_DEPOSIT_FULL);


    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerWithdrawPokemon() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 4, 20);
    pokemonDestroy(pikachu);

    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    pokemonDestroy(squirtle);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,2),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(NULL,1),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(trainer,1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(trainer,2),
                POKEMON_TRAINER_INVALID_INDEX);
    Pokemon ho_ho = pokemonCreate("Ho-ho", TYPE_GRASS, 30, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, ho_ho),
                POKEMON_TRAINER_SUCCESS);
    pokemonDestroy(ho_ho);
    TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(trainer,1),
                POKEMON_TRAINER_PARTY_FULL);


    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerGetNumberOfPokemons() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 4, 2);
    pokemonDestroy(pikachu);

    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_PARTY_FULL);

    TEST_EQUALS(result, pokemonTrainerGetNumberOfPokemons(trainer), 4);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,2),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,2),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,2),
                POKEMON_TRAINER_DEPOSIT_FULL);

    TEST_EQUALS(result, pokemonTrainerGetNumberOfPokemons(trainer), 4);

    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    pokemonDestroy(squirtle);

    TEST_EQUALS(result, pokemonTrainerGetNumberOfPokemons(trainer), 5);

    TEST_EQUALS(result, pokemonTrainerRemovePokemon(trainer, 3),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerRemovePokemon(trainer, 2),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerGetNumberOfPokemons(trainer), 3);

    TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(trainer,1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(trainer,1),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerWithdrawPokemon(trainer,1),
                POKEMON_TRAINER_INVALID_INDEX);

    TEST_EQUALS(result, pokemonTrainerGetNumberOfPokemons(trainer), 3);

    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerGetMostRankedPokemon() {
    bool result = true;

    TEST_EQUALS(result, pokemonTrainerGetMostRankedPokemon(NULL), NULL);

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    TEST_EQUALS(result, pokemonTeachMove(
            pikachu, "Thunder1", TYPE_ELECTRIC, 10, 100), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonGetRank(pikachu), 101);
    TEST_EQUALS(result, pokemonTeachMove(
            pikachu, "Thunder2", TYPE_ELECTRIC, 10, 80), POKEMON_SUCCESS);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 4, 2);
    pokemonDestroy(pikachu);

    TEST_EQUALS(result, pokemonTrainerGetMostRankedPokemon(trainer),
    pokemonTrainerGetPokemon(trainer,1));

    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);
    pokemonDestroy(squirtle);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,2),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerGetMostRankedPokemon(trainer),
                pokemonTrainerGetPokemon(trainer,1));

    TEST_EQUALS(result, pokemonTrainerRemovePokemon(trainer, 1),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerGetMostRankedPokemon(trainer),
                pokemonTrainerGetPokemon(trainer,1));

    pokemonTrainerDestroy(trainer);

    return result;
}

static bool testPokemonTrainerMakeMostRankedParty() {
    bool result = true;

    TEST_EQUALS(result, pokemonTrainerMakeMostRankedParty(NULL),
                POKEMON_TRAINER_NULL_ARG);

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    TEST_EQUALS(result, pokemonTeachMove(
            pikachu, "Thunder1", TYPE_ELECTRIC, 10, 100), POKEMON_SUCCESS);
    TEST_EQUALS(result, pokemonTeachMove(
            pikachu, "Thunder2", TYPE_ELECTRIC, 10, 80), POKEMON_SUCCESS);

    Pokemon squirtle = pokemonCreate("Squirtle", TYPE_WATER, 10, 4);
    TEST_EQUALS(result, pokemonTeachMove(
            squirtle, "Bubble", TYPE_WATER, 10, 50), POKEMON_SUCCESS);

    Pokemon ho_ho = pokemonCreate("Ho-ho", TYPE_GRASS, 30, 4);

    PokemonTrainer trainer = pokemonTrainerCreate("Ash", ho_ho, 3, 3);

    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, pikachu),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, pikachu),
                POKEMON_TRAINER_SUCCESS);

    Pokemon local_pokemon1_ptr = pokemonTrainerGetPokemon(trainer,2);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,3),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);

    //Pokemon remote_pokemon2 = pokemonTrainerGetPokemon(trainer,1);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer,3),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer, squirtle),
                POKEMON_TRAINER_SUCCESS);

    Pokemon local_pokemon3_ptr = pokemonTrainerGetPokemon(trainer,3);

    TEST_EQUALS(result,pokemonTrainerMakeMostRankedParty(trainer),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerGetPokemon(trainer,1),
                local_pokemon1_ptr);
    TEST_EQUALS(result, pokemonTrainerGetPokemon(trainer,3),
                local_pokemon3_ptr);


    //TEST_EQUALS(result, trainer->pokemons_remote[1], remote_pokemon2);


    // SAME TEST ONLY THIS TIME TRAINER HAS 4 LOCAL POKEMONS
    PokemonTrainer trainer2 = pokemonTrainerCreate("Ash", ho_ho, 4, 3);

    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer2, pikachu),
                POKEMON_TRAINER_SUCCESS);
    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer2, pikachu),
                POKEMON_TRAINER_SUCCESS);

    local_pokemon1_ptr = pokemonTrainerGetPokemon(trainer2,2);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer2,3),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer2, squirtle),
                POKEMON_TRAINER_SUCCESS);

    //Pokemon remote_pokemon1 = pokemonTrainerGetPokemon(trainer2,1);

    TEST_EQUALS(result, pokemonTrainerDepositPokemon(trainer2,3),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerAddPokemon(trainer2, squirtle),
                POKEMON_TRAINER_SUCCESS);

    local_pokemon3_ptr = pokemonTrainerGetPokemon(trainer2,3);

    TEST_EQUALS(result,pokemonTrainerMakeMostRankedParty(trainer2),
                POKEMON_TRAINER_SUCCESS);

    TEST_EQUALS(result, pokemonTrainerGetPokemon(trainer2,1),
                local_pokemon1_ptr);
    TEST_EQUALS(result, pokemonTrainerGetPokemon(trainer2,3),
                local_pokemon3_ptr);

    //TEST_EQUALS(result, trainer2->pokemons_remote[0], remote_pokemon1);

    pokemonDestroy(pikachu);
    pokemonDestroy(squirtle);
    pokemonDestroy(ho_ho);

    pokemonTrainerDestroy(trainer);
    pokemonTrainerDestroy(trainer2);

    return result;
}

static bool testPokemonTrainerPrintEnumeration() {
    bool result = true;

    Pokemon pikachu = pokemonCreate("Pikachu", TYPE_ELECTRIC, 20, 4);
    PokemonTrainer trainer = pokemonTrainerCreate("Ash", pikachu, 4, 2);
    pokemonDestroy(pikachu);

    TEST_EQUALS(result, pokemonTrainerPrintEnumeration(trainer, NULL),
                POKEMON_TRAINER_NULL_ARG);
    TEST_EQUALS(result, pokemonTrainerPrintEnumeration(NULL, NULL),
                POKEMON_TRAINER_NULL_ARG);

    pokemonTrainerDestroy(trainer);

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
