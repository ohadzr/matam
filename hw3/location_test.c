/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include "location.h"
#include "aux_macros.h"
#include <assert.h>
#include "pokedex.h"
#include "pokemon.h"

/**************************************
 *         Static Functions           *
 **************************************/

//static bool testNearLocationCombo() {
//    bool result = true;
//
//    /* -----------------------  initialization  ----------------------- */
//    NearLocation nearLocation1 = nearLocationCreate("Israel");
//    NearLocation nearLocation2 = nearLocationCreate("USA");
//    NearLocation nearLocation3 = nearLocationCreate("Japan");
//    NearLocation nearLocation4 = nearLocationCopy(nearLocation3);
//    /* ----------------------------- tests ---------------------------- */
//    TEST_DIFFERENT(result, nearLocation1, NULL);
//    TEST_DIFFERENT(result, nearLocation4, NULL);
//    TEST_EQUALS(result, nearLocationCompare(nearLocation4, nearLocation3), 0);
//    TEST_DIFFERENT(result, nearLocationCompare(nearLocation1, nearLocation2), 0);
//    /* ------------------------  destruction  ------------------------- */
//    nearLocationDestroy(nearLocation1);
//    nearLocationDestroy(nearLocation2);
//    nearLocationDestroy(nearLocation3);
//    nearLocationDestroy(nearLocation4);
//
//    return result;
//}
//
//static bool testLocationCombo() {
//    bool result = true;
//
//    /* -----------------------  initialization  ----------------------- */
//    NearLocation nearLocation1 = nearLocationCreate("Israel");
//    NearLocation nearLocation2 = nearLocationCreate("USA");
//    NearLocation nearLocation3 = nearLocationCreate("Japan");
//    NearLocation nearLocation4 = nearLocationCreate("France");
//    NearLocation nearLocation5 = NULL;
//    NearLocation nearLocation6 = nearLocationCopy(nearLocation1);
//    Pokedex pokedex = pokedexCreate();
//    PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
//    PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
//    PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
//    pokedexAddPokemonInfo(pokedex, pokemon_info1);
//    pokedexAddPokemonInfo(pokedex, pokemon_info2);
//    pokedexAddPokemonInfo(pokedex, pokemon_info3);
//    Pokemon pokemon1 = pokemonCreate("Pikachu", pokedex);
//    Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
//    Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
//    Pokemon pokemon4 = NULL;
//    Location location1 = locationCreate("Israel");
//    Location location2 = locationCreate("USA");
//    Location location3 = locationCreate("Japan");
//    Location location4 = locationCreate("France");
//    Location location5 = NULL;
//    Location location6 = locationCopy(location1);
//    locationAddPokemon(location1, pokemon1);
//    locationAddPokemon(location1, pokemon2);
//    locationAddPokemon(location1, pokemon1);
//    locationAddPokemon(location2, pokemon3);
//    locationAddPokemon(location2, pokemon2);
//    locationAddPokemon(location3, pokemon1);
//    //locationAddPokemon(location6, pokemon3);
//    locationAddNearLocation(location1, nearLocation2);
//    locationAddNearLocation(location1, nearLocation3);
//    locationAddNearLocation(location2, nearLocation1);
//    locationAddNearLocation(location3, nearLocation1);
//    locationAddNearLocation(location3, nearLocation1);
//    /* ----------------------------- tests ---------------------------- */
//    TEST_DIFFERENT(result, location1, NULL);
//    //TEST_DIFFERENT(result, location6, NULL);
//    //TEST_EQUALS(result, locationCompare(location1, location6), 0);
//    TEST_DIFFERENT(result, locationCompare(location1, location2), 0);
//    TEST_EQUALS(result, locationIsNearDestination(location1, nearLocation1),
//                false);
//    TEST_EQUALS(result, locationIsNearDestination(location1, nearLocation2),
//                true);
//    TEST_EQUALS(result, locationRemovePokemon(location1, pokemon1),
//                LOCATION_SUCCESS);
//    TEST_EQUALS(result, locationRemovePokemon(location1, pokemon1),
//                LOCATION_SUCCESS);
//    TEST_EQUALS(result, locationRemovePokemon(location1, pokemon1),
//                LOCATION_POKEMON_NOT_EXIST);
//    TEST_EQUALS(result, locationRemovePokemon(location3, pokemon1),
//                LOCATION_SUCCESS);
//    TEST_EQUALS(result, locationIsNearDestination(location3, nearLocation1),
//                true);
//    TEST_EQUALS(result, locationAddNearLocation(location3, nearLocation1),
//                LOCATION_SUCCESS);
//    TEST_EQUALS(result, locationRemoveNearLocation(location3, nearLocation1),
//                LOCATION_SUCCESS);
//    TEST_EQUALS(result, locationIsNearDestination(location3, nearLocation1),
//                false);
//    TEST_EQUALS(result, locationAddNearLocation(location3, nearLocation5),
//                LOCATION_NULL_ARGUMENT);
//    TEST_EQUALS(result, locationRemoveNearLocation(location3, nearLocation5),
//                LOCATION_NULL_ARGUMENT);
//    //TEST_EQUALS(result, locationIsNearDestination(location6, nearLocation1),
//    //		false);
//    TEST_EQUALS(result, locationAddNearLocation(location4, nearLocation5),
//                LOCATION_NULL_ARGUMENT);
//    TEST_EQUALS(result, locationAddPokemon(location4, pokemon3),
//                LOCATION_SUCCESS);
//    //TEST_EQUALS(result,
//    //		locationIsNearDestination(location6, locationGetName(location1)),
//    //		false);
//    /* ------------------------  destruction  ------------------------- */
//    nearLocationDestroy(nearLocation1);
//    nearLocationDestroy(nearLocation2);
//    nearLocationDestroy(nearLocation3);
//    nearLocationDestroy(nearLocation4);
//    nearLocationDestroy(nearLocation5);
//    nearLocationDestroy(nearLocation6);
//    locationDestroy(location1);
//    locationDestroy(location2);
//    locationDestroy(location3);
//    locationDestroy(location4);
//    locationDestroy(location5);
//    locationDestroy(location6);
//    pokedexDestroy(pokedex);
//    pokedexPokemonInfoDestroy(pokemon_info1);
//    pokedexPokemonInfoDestroy(pokemon_info2);
//    pokedexPokemonInfoDestroy(pokemon_info3);
//    pokemonDestroy(pokemon1);
//    pokemonDestroy(pokemon2);
//    pokemonDestroy(pokemon3);
//    pokemonDestroy(pokemon4);
//
//    return result;
//
//}
//
//static bool testWorldMapCombo() { //TODO: add worldMapDoesLocationExist tests
//    bool result = true;
//
//    /* -----------------------  initialization  ----------------------- */
//    NearLocation nearLocation1 = nearLocationCreate("Israel");
//    NearLocation nearLocation2 = nearLocationCreate("USA");
//    NearLocation nearLocation3 = nearLocationCreate("Japan");
//    NearLocation nearLocation4 = nearLocationCreate("France");
//    NearLocation nearLocation5 = NULL;
//    NearLocation nearLocation6 = nearLocationCopy(nearLocation1);
//    Pokedex pokedex = pokedexCreate();
//    PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
//    PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
//    PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
//    pokedexAddPokemonInfo(pokedex, pokemon_info1);
//    pokedexAddPokemonInfo(pokedex, pokemon_info2);
//    pokedexAddPokemonInfo(pokedex, pokemon_info3);
//    Pokemon pokemon1 = pokemonCreate("Pikacho", pokedex);
//    Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
//    Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
//    Pokemon pokemon4 = NULL;
//    Location location1 = locationCreate("Israel");
//    Location location2 = locationCreate("USA");
//    Location location3 = locationCreate("Japan");
//    Location location4 = locationCreate("France");
//    Location location5 = NULL;
//    Location location6 = locationCopy(location1);
//    locationAddPokemon(location1, pokemon1);
//    locationAddPokemon(location1, pokemon2);
//    locationAddPokemon(location1, pokemon1);
//    locationAddPokemon(location2, pokemon3);
//    locationAddPokemon(location2, pokemon2);
//    locationAddPokemon(location3, pokemon1);
//    locationAddPokemon(location6, pokemon3);
//    locationAddNearLocation(location1, nearLocation2);
//    locationAddNearLocation(location1, nearLocation3);
//    locationAddNearLocation(location2, nearLocation1);
//    locationAddNearLocation(location3, nearLocation1);
//    locationAddNearLocation(location3, nearLocation1);
//    WorldMap world_map = worldMapCreate();
//    /* ----------------------------- tests ---------------------------- */
//    TEST_EQUALS(result, worldMapGetSize(world_map), 0);
//    TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
//                WORLD_MAP_SUCCESS);
//    TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
//                WORLD_MAP_LOCATION_ALREADY_EXISTS);
//    TEST_EQUALS(result, worldMapAddLocation(world_map, location3),
//                WORLD_MAP_SUCCESS);
//    TEST_EQUALS(result, worldMapAddLocation(world_map, location5),
//                WORLD_MAP_NULL_ARGUMENT);
//    TEST_EQUALS(result, worldMapAddLocation(world_map, location6),
//                WORLD_MAP_LOCATION_ALREADY_EXISTS);
//    TEST_EQUALS(result, worldMapGetSize(world_map), 2);
//    TEST_EQUALS(result, worldMapRemoveLocation(world_map, location2),
//                WORLD_MAP_LOCATION_NOT_EXIST);
//    TEST_EQUALS(result, worldMapRemoveLocation(world_map, location3),
//                WORLD_MAP_SUCCESS);
//    TEST_EQUALS(result, worldMapGetSize(world_map), 1);
//    TEST_EQUALS(result, worldMapRemoveLocation(world_map, location5),
//                WORLD_MAP_NULL_ARGUMENT);
//    TEST_EQUALS(result, worldMapAddLocation(world_map, location2),
//                WORLD_MAP_SUCCESS);
//    TEST_EQUALS(result, worldMapGetSize(world_map), 2);
//    TEST_EQUALS(result, worldMapGetLocation(world_map, ""), NULL);
//    TEST_EQUALS(result, worldMapGetLocation(world_map,NULL), NULL);
//    Location location_test = worldMapGetLocation(world_map, "Israel");
//    TEST_EQUALS(result, locationCompare(location_test, location1), 0);
//    location_test = worldMapGetLocation(world_map, "Japan");
//    TEST_EQUALS(result, location_test, NULL);
//    Pokemon pokemon_test = worldMapGetPokemonInLocation(world_map, "Israel");
//    TEST_EQUALS(result, pokemonCompareByName(pokemon_test, pokemon2),
//                POKEMON_EQUAL);
//    pokemon_test = worldMapGetPokemonInLocation(world_map, "USA");
//    TEST_EQUALS(result, pokemonCompareByName(pokemon_test, pokemon3),
//                POKEMON_EQUAL);
//    pokemon_test = worldMapGetPokemonInLocation(world_map, "France");
//    TEST_EQUALS(result, pokemonCompareByName(pokemon_test,NULL),
//                POKEMON_NULL_ARG);
//    TEST_EQUALS(result,
//                worldMapIsLocationReachable(world_map, "Israel", "Japan"), false);
//    TEST_EQUALS(result, worldMapIsLocationReachable(world_map, "Israel", "USA"),
//                true);
//    TEST_EQUALS(result, worldMapIsLocationReachable(world_map, "USA", "Israel"),
//                true);
//    TEST_EQUALS(result,
//                worldMapIsLocationReachable(world_map, "France", "Israel"), false);
//    TEST_EQUALS(result, worldMapIsLocationReachable(world_map, "USA", "France"),
//                false);
//
//    worldMapSort(world_map);
//    TEST_EQUALS(result, worldMapGetSize(world_map), 2);
//
//    /* ------------------------  destruction  ------------------------- */
//    nearLocationDestroy(nearLocation1);
//    nearLocationDestroy(nearLocation2);
//    nearLocationDestroy(nearLocation3);
//    nearLocationDestroy(nearLocation4);
//    nearLocationDestroy(nearLocation5);
//    nearLocationDestroy(nearLocation6);
//    locationDestroy(location1);
//    locationDestroy(location2);
//    locationDestroy(location3);
//    locationDestroy(location4);
//    locationDestroy(location5);
//    locationDestroy(location6);
//    pokedexDestroy(pokedex);
//    pokedexPokemonInfoDestroy(pokemon_info1);
//    pokedexPokemonInfoDestroy(pokemon_info2);
//    pokedexPokemonInfoDestroy(pokemon_info3);
//    pokemonDestroy(pokemon1);
//    pokemonDestroy(pokemon2);
//    pokemonDestroy(pokemon3);
//    pokemonDestroy(pokemon4);
//    worldMapDestroy(world_map);
//
//    return result;
//}
//
//int main() {
//    RUN_TEST(testNearLocationCombo);
//    RUN_TEST(testLocationCombo);
//    RUN_TEST(testWorldMapCombo);
//    return 0;
//}
