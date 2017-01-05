/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../location.h"
#include "test_utilities.h"
/**************************************
 *         Static Functions           *
 **************************************/

static bool testNearLocationCombo() {
    bool result = true;

    /* -----------------------  initialization  ----------------------- */
    NearLocation nearLocation1 = nearLocationCreate("Israel");
    NearLocation nearLocation2 = nearLocationCreate("USA");
    NearLocation nearLocation3 = nearLocationCreate("Japan");
    NearLocation nearLocation4 = nearLocationCreate("");
    NearLocation nearLocation5 = nearLocationCreate(NULL);
    /* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result, nearLocation1, NULL);
    TEST_DIFFERENT(result, nearLocation2, NULL);
    TEST_DIFFERENT(result, nearLocation3, NULL);
    TEST_EQUALS(result, nearLocation4, NULL);
    TEST_EQUALS(result, nearLocation5, NULL);
    /* ------------------------  destruction  ------------------------- */
    nearLocationDestroy(nearLocation1);
    nearLocationDestroy(nearLocation2);
    nearLocationDestroy(nearLocation3);
    nearLocationDestroy(nearLocation4);
    nearLocationDestroy(nearLocation5);

    return result;
}

static bool testLocationCreateAndDestroy() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	Location location5 = NULL;
	Location location6 = locationCreate("");
	Location location7 = locationCreate(NULL);
	Location location8 = locationCreate("Israel");
	/* ----------------------------- tests ---------------------------- */
	TEST_DIFFERENT(result, location1, NULL);
	TEST_DIFFERENT(result, location2, NULL);
	TEST_DIFFERENT(result, location3, NULL);
	TEST_DIFFERENT(result, location4, NULL);
	TEST_DIFFERENT(result, location8, NULL);
	TEST_EQUALS(result, location5, NULL);
	TEST_EQUALS(result, location6, NULL);
	TEST_EQUALS(result, location7, NULL);
	/* ------------------------  destruction  ------------------------- */
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	locationDestroy(location5);
	locationDestroy(location6);
	locationDestroy(location7);
	locationDestroy(location8);

	return result;
}

static bool testLocationAddPokemon() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	Location location5 = NULL;
	Location location6 = locationCreate("");
	Location location7 = locationCreate(NULL);
	Pokedex pokedex = pokedexCreate();
	PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
	PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
	PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
	pokedexAddPokemonInfo(pokedex, pokemon_info1);
	pokedexAddPokemonInfo(pokedex, pokemon_info2);
	pokedexAddPokemonInfo(pokedex, pokemon_info3);
	Pokemon pokemon1 = pokemonCreate("Pikachu", pokedex);
	Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
	Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
	Pokemon pokemon4 = NULL;
	/* ----------------------------- tests ---------------------------- */
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon1),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon1),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon2),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon1),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon3),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon3),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon3),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location2, pokemon1),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location4, pokemon4),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddPokemon(location4, pokemon2),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location5, pokemon2),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddPokemon(location6, pokemon2),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddPokemon(location7, pokemon2),
			LOCATION_NULL_ARGUMENT);
	/* ------------------------  destruction  ------------------------- */
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	locationDestroy(location5);
	locationDestroy(location6);
	locationDestroy(location7);
	pokedexDestroy(pokedex);
	pokedexPokemonInfoDestroy(pokemon_info1);
	pokedexPokemonInfoDestroy(pokemon_info2);
	pokedexPokemonInfoDestroy(pokemon_info3);
	pokemonDestroy(pokemon1);
	pokemonDestroy(pokemon2);
	pokemonDestroy(pokemon3);
	pokemonDestroy(pokemon4);

	return result;
}

static bool testLocationAddNearLocation() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	Location location5 = NULL;
	Location location6 = locationCreate("");
	Location location7 = locationCreate(NULL);
	NearLocation nearLocation1 = nearLocationCreate("Israel");
	NearLocation nearLocation2 = nearLocationCreate("USA");
	NearLocation nearLocation3 = nearLocationCreate("Japan");
	NearLocation nearLocation4 = nearLocationCreate("");
	NearLocation nearLocation5 = nearLocationCreate(NULL);
	/* ----------------------------- tests ---------------------------- */
	TEST_EQUALS(result, locationAddNearLocation(location1, nearLocation2),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddNearLocation(location1, nearLocation1),
			LOCATION_ALREADY_IN_LOCATION);
	TEST_EQUALS(result, locationAddNearLocation(location2, nearLocation2),
			LOCATION_ALREADY_IN_LOCATION);
	TEST_EQUALS(result, locationAddNearLocation(location2, nearLocation3),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddNearLocation(location5, nearLocation3),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location6, nearLocation3),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location7, nearLocation3),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location1, nearLocation5),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location1, nearLocation4),
			LOCATION_NULL_ARGUMENT);
	/* ------------------------  destruction  ------------------------- */
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	locationDestroy(location5);
	locationDestroy(location6);
	locationDestroy(location7);
	nearLocationDestroy(nearLocation1);
	nearLocationDestroy(nearLocation2);
	nearLocationDestroy(nearLocation3);
	nearLocationDestroy(nearLocation4);
	nearLocationDestroy(nearLocation5);

	return result;
}

static bool testLocationCombo() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Pokedex pokedex = pokedexCreate();
	PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
	PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
	PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
	pokedexAddPokemonInfo(pokedex, pokemon_info1);
	pokedexAddPokemonInfo(pokedex, pokemon_info2);
	pokedexAddPokemonInfo(pokedex, pokemon_info3);
	Pokemon pokemon1 = pokemonCreate("Pikachu", pokedex);
	Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
	Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
	Pokemon pokemon4 = NULL;
	NearLocation nearLocation1 = nearLocationCreate("Israel");
	NearLocation nearLocation2 = nearLocationCreate("USA");
	NearLocation nearLocation3 = nearLocationCreate(NULL);
	NearLocation nearLocation4 = nearLocationCreate("");
	NearLocation nearLocation5 = NULL;
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location5 = NULL;
	Location location6 = locationCreate("");
	Location location7 = locationCreate(NULL);
	locationAddNearLocation(location1, nearLocation2);
	locationAddNearLocation(location1, nearLocation3);
	locationAddNearLocation(location2, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	/* ----------------------------- tests ---------------------------- */
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon1),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon2),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location1, pokemon1),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location2, pokemon2),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location2, pokemon3),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location3, pokemon1),
			LOCATION_SUCCESS);
	TEST_EQUALS(result, locationAddPokemon(location3, pokemon4),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddPokemon(location5, pokemon1),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddPokemon(location6, pokemon1),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddPokemon(location7, pokemon1),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location1, nearLocation2),
			LOCATION_ALREADY_EXIST);
	TEST_EQUALS(result, locationAddNearLocation(location2, nearLocation2),
			LOCATION_ALREADY_IN_LOCATION);
	TEST_EQUALS(result, locationAddNearLocation(location3, nearLocation3),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location3, nearLocation4),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location3, nearLocation5),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location5, nearLocation2),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location6, nearLocation2),
			LOCATION_NULL_ARGUMENT);
	TEST_EQUALS(result, locationAddNearLocation(location7, nearLocation2),
			LOCATION_NULL_ARGUMENT);
	/* ------------------------  destruction  ------------------------- */
	nearLocationDestroy(nearLocation1);
	nearLocationDestroy(nearLocation2);
	nearLocationDestroy(nearLocation3);
	nearLocationDestroy(nearLocation4);
	nearLocationDestroy(nearLocation5);
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location5);
	locationDestroy(location6);
	locationDestroy(location7);
	pokedexDestroy(pokedex);
	pokedexPokemonInfoDestroy(pokemon_info1);
	pokedexPokemonInfoDestroy(pokemon_info2);
	pokedexPokemonInfoDestroy(pokemon_info3);
	pokemonDestroy(pokemon1);
	pokemonDestroy(pokemon2);
	pokemonDestroy(pokemon3);
	pokemonDestroy(pokemon4);

	return result;

}

static bool testWorldMapCreateDestroyAndAdd() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Pokedex pokedex = pokedexCreate();
	PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
	PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
	PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
	pokedexAddPokemonInfo(pokedex, pokemon_info1);
	pokedexAddPokemonInfo(pokedex, pokemon_info2);
	pokedexAddPokemonInfo(pokedex, pokemon_info3);
	Pokemon pokemon1 = pokemonCreate("Pikachu", pokedex);
	Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
	Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
	NearLocation nearLocation1 = nearLocationCreate("Israel");
	NearLocation nearLocation2 = nearLocationCreate("USA");
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	locationAddNearLocation(location1, nearLocation2);
	locationAddNearLocation(location2, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	locationAddNearLocation(location3, nearLocation2);
	WorldMap world_map = worldMapCreate();
	/* ----------------------------- tests ---------------------------- */
	TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
			WORLD_MAP_SUCCESS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location2),
			WORLD_MAP_SUCCESS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location3),
			WORLD_MAP_SUCCESS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location4),
			WORLD_MAP_SUCCESS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
			WORLD_MAP_LOCATION_ALREADY_EXISTS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location2),
			WORLD_MAP_LOCATION_ALREADY_EXISTS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location4),
			WORLD_MAP_LOCATION_ALREADY_EXISTS);
	/* ------------------------  destruction  ------------------------- */
	worldMapDestroy(world_map);
	nearLocationDestroy(nearLocation1);
	nearLocationDestroy(nearLocation2);
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	pokedexDestroy(pokedex);
	pokedexPokemonInfoDestroy(pokemon_info1);
	pokedexPokemonInfoDestroy(pokemon_info2);
	pokedexPokemonInfoDestroy(pokemon_info3);
	pokemonDestroy(pokemon1);
	pokemonDestroy(pokemon2);
	pokemonDestroy(pokemon3);

	return result;
}

static bool testWorldMapDoesLocationExist() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Pokedex pokedex = pokedexCreate();
	PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
	PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
	PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
	pokedexAddPokemonInfo(pokedex, pokemon_info1);
	pokedexAddPokemonInfo(pokedex, pokemon_info2);
	pokedexAddPokemonInfo(pokedex, pokemon_info3);
	Pokemon pokemon1 = pokemonCreate("Pikachu", pokedex);
	Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
	Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
	NearLocation nearLocation1 = nearLocationCreate("Israel");
	NearLocation nearLocation2 = nearLocationCreate("USA");
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	locationAddNearLocation(location1, nearLocation2);
	locationAddNearLocation(location2, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	locationAddNearLocation(location3, nearLocation2);
	locationAddPokemon(location1, pokemon1);
	locationAddPokemon(location1, pokemon2);
	locationAddPokemon(location1, pokemon2);
	locationAddPokemon(location1, pokemon3);
	locationAddPokemon(location2, pokemon3);
	locationAddPokemon(location3, pokemon3);
	locationAddPokemon(location4, pokemon3);
	locationAddPokemon(location4, pokemon2);
	WorldMap world_map = worldMapCreate();
	/* ----------------------------- tests ---------------------------- */
	TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
			WORLD_MAP_SUCCESS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location2),
			WORLD_MAP_SUCCESS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location3),
			WORLD_MAP_SUCCESS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
			WORLD_MAP_LOCATION_ALREADY_EXISTS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, location2),
			WORLD_MAP_LOCATION_ALREADY_EXISTS);
	TEST_EQUALS(result, worldMapAddLocation(world_map, NULL),
			WORLD_MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, worldMapAddLocation(NULL, location2),
			WORLD_MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, worldMapDoesLocationExist(world_map, "France"),
	false);
	TEST_EQUALS(result, worldMapDoesLocationExist(world_map, "Israel"),
	true);
	/* ------------------------  destruction  ------------------------- */
	worldMapDestroy(world_map);
	nearLocationDestroy(nearLocation1);
	nearLocationDestroy(nearLocation2);
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	pokedexDestroy(pokedex);
	pokedexPokemonInfoDestroy(pokemon_info1);
	pokedexPokemonInfoDestroy(pokemon_info2);
	pokedexPokemonInfoDestroy(pokemon_info3);
	pokemonDestroy(pokemon1);
	pokemonDestroy(pokemon2);
	pokemonDestroy(pokemon3);

	return result;
}

static bool testWorldMapGetPokemonInLocation() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Pokedex pokedex = pokedexCreate();
	PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
	PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
	PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
	pokedexAddPokemonInfo(pokedex, pokemon_info1);
	pokedexAddPokemonInfo(pokedex, pokemon_info2);
	pokedexAddPokemonInfo(pokedex, pokemon_info3);
	Pokemon pokemon1 = pokemonCreate("Pikachu", pokedex);
	Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
	Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
	NearLocation nearLocation1 = nearLocationCreate("Israel");
	NearLocation nearLocation2 = nearLocationCreate("USA");
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	locationAddNearLocation(location1, nearLocation2);
	locationAddNearLocation(location2, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	locationAddNearLocation(location3, nearLocation2);
	locationAddPokemon(location1, pokemon1);
	locationAddPokemon(location1, pokemon2);
	locationAddPokemon(location1, pokemon2);
	locationAddPokemon(location1, pokemon3);
	locationAddPokemon(location2, pokemon3);
	locationAddPokemon(location3, pokemon3);
	locationAddPokemon(location4, pokemon3);
	locationAddPokemon(location4, pokemon2);
	WorldMap world_map = worldMapCreate();
	worldMapAddLocation(world_map, location1);
	worldMapAddLocation(world_map, location2);
	worldMapAddLocation(world_map, location3);
	worldMapAddLocation(world_map, location4);
	/* ----------------------------- tests ---------------------------- */
	Pokemon pokemon_test1 = worldMapGetPokemonInLocation(world_map, "Israel");
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test1, pokemon1),
			POKEMON_EQUAL);
	Pokemon pokemon_test2 = worldMapGetPokemonInLocation(world_map, "Israel");
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test2, pokemon2),
			POKEMON_EQUAL);
	Pokemon pokemon_test3 = worldMapGetPokemonInLocation(world_map, "Israel");
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test3, pokemon2),
			POKEMON_EQUAL);
	Pokemon pokemon_test4 = worldMapGetPokemonInLocation(world_map, "France");
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test4, pokemon3),
			POKEMON_EQUAL);
	Pokemon pokemon_test5 = worldMapGetPokemonInLocation(world_map, NULL);
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test5, pokemon3),
			POKEMON_NULL_ARG);
	Pokemon pokemon_test6 = worldMapGetPokemonInLocation(NULL, "Israel");
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test6, pokemon3),
			POKEMON_NULL_ARG);
	Pokemon pokemon_test7 = worldMapGetPokemonInLocation(world_map, "Japan");
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test7, pokemon2),
			POKEMON_DIFFERENT);
	Pokemon pokemon_test8 = worldMapGetPokemonInLocation(world_map, "Japan");
	TEST_EQUALS(result, pokemonCompareByName(pokemon_test8, pokemon3),
			POKEMON_NULL_ARG);
	/* ------------------------  destruction  ------------------------- */
	worldMapDestroy(world_map);
	nearLocationDestroy(nearLocation1);
	nearLocationDestroy(nearLocation2);
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	pokedexDestroy(pokedex);
	pokedexPokemonInfoDestroy(pokemon_info1);
	pokedexPokemonInfoDestroy(pokemon_info2);
	pokedexPokemonInfoDestroy(pokemon_info3);
	pokemonDestroy(pokemon1);
	pokemonDestroy(pokemon2);
	pokemonDestroy(pokemon3);
	pokemonDestroy(pokemon_test1);
	pokemonDestroy(pokemon_test2);
	pokemonDestroy(pokemon_test3);
	pokemonDestroy(pokemon_test4);
	pokemonDestroy(pokemon_test5);
	pokemonDestroy(pokemon_test6);
	pokemonDestroy(pokemon_test7);
	pokemonDestroy(pokemon_test8);

	return result;
}

static bool testWorldMapIsLocationReachable() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	Pokedex pokedex = pokedexCreate();
	PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
	PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
	PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
	pokedexAddPokemonInfo(pokedex, pokemon_info1);
	pokedexAddPokemonInfo(pokedex, pokemon_info2);
	pokedexAddPokemonInfo(pokedex, pokemon_info3);
	Pokemon pokemon1 = pokemonCreate("Pikachu", pokedex);
	Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
	Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
	NearLocation nearLocation1 = nearLocationCreate("Israel");
	NearLocation nearLocation2 = nearLocationCreate("USA");
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	Location location5 = NULL;
	locationAddNearLocation(location1, nearLocation2);
	locationAddNearLocation(location2, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	locationAddNearLocation(location3, nearLocation2);
	locationAddPokemon(location1, pokemon1);
	locationAddPokemon(location1, pokemon2);
	locationAddPokemon(location1, pokemon2);
	locationAddPokemon(location1, pokemon3);
	locationAddPokemon(location2, pokemon3);
	locationAddPokemon(location3, pokemon3);
	locationAddPokemon(location4, pokemon3);
	locationAddPokemon(location4, pokemon2);
	WorldMap world_map = worldMapCreate();
	worldMapAddLocation(world_map, location1);
	worldMapAddLocation(world_map, location2);
	worldMapAddLocation(world_map, location3);
	worldMapAddLocation(world_map, location4);
	/* ----------------------------- tests ---------------------------- */
	TEST_EQUALS(result,worldMapIsLocationReachable(world_map,"Israel","Israel"),
			false);
	TEST_EQUALS(result,worldMapIsLocationReachable(world_map,"Israel","USA"),
			true);
	TEST_EQUALS(result,worldMapIsLocationReachable(world_map,"France","Japan"),
			false);
	TEST_EQUALS(result,worldMapIsLocationReachable(world_map,"USA","Israel"),
			true);
	TEST_EQUALS(result,worldMapIsLocationReachable(world_map,"Japan","Israel"),
			true);
	/* ------------------------  destruction  ------------------------- */
	worldMapDestroy(world_map);
	nearLocationDestroy(nearLocation1);
	nearLocationDestroy(nearLocation2);
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	locationDestroy(location5);
	pokedexDestroy(pokedex);
	pokedexPokemonInfoDestroy(pokemon_info1);
	pokedexPokemonInfoDestroy(pokemon_info2);
	pokedexPokemonInfoDestroy(pokemon_info3);
	pokemonDestroy(pokemon1);
	pokemonDestroy(pokemon2);
	pokemonDestroy(pokemon3);

	return result;
}

static bool testWorldMapCombo() {
	bool result = true;

	/* -----------------------  initialization  ----------------------- */
	NearLocation nearLocation1 = nearLocationCreate("Israel");
	NearLocation nearLocation2 = nearLocationCreate("USA");
	NearLocation nearLocation3 = nearLocationCreate("Japan");
	NearLocation nearLocation4 = nearLocationCreate("France");
	NearLocation nearLocation5 = NULL;
	Pokedex pokedex = pokedexCreate();
	PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
	PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
	PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
	pokedexAddPokemonInfo(pokedex, pokemon_info1);
	pokedexAddPokemonInfo(pokedex, pokemon_info2);
	pokedexAddPokemonInfo(pokedex, pokemon_info3);
	Pokemon pokemon1 = pokemonCreate("Pikacho", pokedex);
	Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
	Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
	Pokemon pokemon4 = NULL;
	Location location1 = locationCreate("Israel");
	Location location2 = locationCreate("USA");
	Location location3 = locationCreate("Japan");
	Location location4 = locationCreate("France");
	Location location5 = NULL;
	locationAddPokemon(location1, pokemon1);
	locationAddPokemon(location1, pokemon2);
	locationAddPokemon(location1, pokemon1);
	locationAddPokemon(location2, pokemon3);
	locationAddPokemon(location2, pokemon2);
	locationAddPokemon(location3, pokemon1);
	locationAddNearLocation(location1, nearLocation2);
	locationAddNearLocation(location1, nearLocation3);
	locationAddNearLocation(location2, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	locationAddNearLocation(location3, nearLocation1);
	WorldMap world_map = worldMapCreate();
	worldMapAddLocation(world_map, location1);
	worldMapAddLocation(world_map, location2);
	worldMapAddLocation(world_map, location3);
	worldMapAddLocation(world_map, location4);
	/* ----------------------------- tests ---------------------------- */
	TEST_EQUALS(result,worldMapAddLocation(world_map,location1),WORLD_MAP_LOCATION_ALREADY_EXISTS);
	Pokemon pokemon = worldMapGetPokemonInLocation(world_map,"Japan");
	TEST_EQUALS(result,worldMapAddLocation(world_map,location1),WORLD_MAP_LOCATION_ALREADY_EXISTS);
	TEST_EQUALS(result,worldMapDoesLocationExist(world_map,""),false);
	TEST_EQUALS(result,worldMapDoesLocationExist(world_map,"Japan"),true);
	TEST_EQUALS(result,worldMapIsLocationReachable(world_map,"Japan","Japan"),false);
	TEST_EQUALS(result,worldMapIsLocationReachable(world_map,"France","Japan"),false);
	/* ------------------------  destruction  ------------------------- */
	nearLocationDestroy(nearLocation1);
	nearLocationDestroy(nearLocation2);
	nearLocationDestroy(nearLocation3);
	nearLocationDestroy(nearLocation4);
	nearLocationDestroy(nearLocation5);
	locationDestroy(location1);
	locationDestroy(location2);
	locationDestroy(location3);
	locationDestroy(location4);
	locationDestroy(location5);
	pokedexDestroy(pokedex);
	pokedexPokemonInfoDestroy(pokemon_info1);
	pokedexPokemonInfoDestroy(pokemon_info2);
	pokedexPokemonInfoDestroy(pokemon_info3);
	pokemonDestroy(pokemon1);
	pokemonDestroy(pokemon2);
	pokemonDestroy(pokemon3);
	pokemonDestroy(pokemon4);
	pokemonDestroy(pokemon);
	worldMapDestroy(world_map);

	return result;
}

int main() {

    RUN_TEST(testNearLocationCombo);

	RUN_TEST(testLocationCreateAndDestroy);
	RUN_TEST(testLocationAddPokemon);
	RUN_TEST(testLocationAddNearLocation);
	RUN_TEST(testLocationCombo);

	RUN_TEST(testWorldMapCreateDestroyAndAdd);
	RUN_TEST(testWorldMapDoesLocationExist);
	RUN_TEST(testWorldMapGetPokemonInLocation);
	RUN_TEST(testWorldMapIsLocationReachable);
	// worldMapSort test will be tested in pokemon_go
	// worldMapPrintReport test will be tested in pokemon_go
	RUN_TEST(testWorldMapCombo);

    return 0;
}
