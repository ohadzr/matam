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

static bool testNearLocationCombo() {
    bool result = true;

    /* -----------------------  initialization  ----------------------- */
    NearLocation nearLocation1 = nearLocationCreate("Israel");
    NearLocation nearLocation2 = nearLocationCreate("USA");
    NearLocation nearLocation3 = nearLocationCreate("Japan");
    NearLocation nearLocation4 = nearLocationCopy(nearLocation3);
    /* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result, nearLocation1, NULL);
    TEST_DIFFERENT(result, nearLocation3, NULL);
    TEST_EQUALS(result, nearLocationCompare(nearLocation4, nearLocation3), 0);
    TEST_DIFFERENT(result, nearLocationCompare(nearLocation1, nearLocation2), 0);
    /* ------------------------  destruction  ------------------------- */
    nearLocationDestroy(nearLocation1);
    nearLocationDestroy(nearLocation2);
    nearLocationDestroy(nearLocation3);
    nearLocationDestroy(nearLocation4);

    return result;
}

static bool testLocationCombo() {
    bool result = true;

    /* -----------------------  initialization  ----------------------- */
    NearLocation nearLocation1 = nearLocationCreate("Israel");
    NearLocation nearLocation2 = nearLocationCreate("USA");
    NearLocation nearLocation3 = nearLocationCreate("Japan");
    NearLocation nearLocation4 = nearLocationCreate("France");
    NearLocation nearLocation5 = nearLocationCopy(nearLocation4);
    NearLocation nearLocation6 = NULL;
    Pokedex pokedex = pokedexCreate();
    PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
    PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
    PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
    Pokemon pokemon1 = pokemonCreate("Pikacho", pokedex);
    Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
    Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
    Pokemon pokemon4 = NULL;
    Location location1 = locationCreate("Israel");
    Location location2 = locationCreate("USA");
    Location location3 = locationCreate("Japan");
    Location location4 = NULL;
    Location location5 = locationCopy(location1);
    locationAddPokemon(location1, pokemon1);
    locationAddPokemon(location1, pokemon2);
    locationAddPokemon(location1, pokemon1);
    locationAddPokemon(location2, pokemon3);
    locationAddPokemon(location2, pokemon2);
    locationAddPokemon(location3, pokemon1);
    locationAddPokemon(location5, pokemon3);
    locationAddPokemon(location5, pokemon3);
    locationAddNearLocation(location1, nearLocation2);
    locationAddNearLocation(location1, nearLocation3);
    locationAddNearLocation(location2, nearLocation1);
    locationAddNearLocation(location3, nearLocation1);
    /* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result, location1, NULL);
    TEST_EQUALS(result, locationCompare(location1, location5), 0);
    Pokemon pokemon5 = locationGetPokemonInLocation(location1);
    TEST_EQUALS(result, pokemonCompare(pokemon5, pokemon1), 0);
    Pokemon pokemon6 = locationGetPokemonInLocation(location2);
    Pokemon pokemon7 = locationGetPokemonInLocation(location2);
    Pokemon pokemon8 = locationGetPokemonInLocation(location2);
    TEST_EQUALS(result, pokemonCompare(pokemon6, pokemon3), 0);
    TEST_EQUALS(result, pokemonCompare(pokemon7, pokemon2), 0);
    TEST_EQUALS(result, pokemonCompare(pokemon8,NULL), 0);
    TEST_DIFFERENT(result, locationCompare(location1, location2), 0);
    TEST_EQUALS(result, locationIsNearDestination(location1, nearLocation1),
                false);
    TEST_EQUALS(result, locationIsNearDestination(location1, nearLocation2),
                true);
    TEST_EQUALS(result, locationRemovePokemon(location1, pokemon1),
                LOCATION_SUCCESS);
    TEST_EQUALS(result, locationRemovePokemon(location1, pokemon1),
                LOCATION_SUCCESS);
    TEST_EQUALS(result, locationRemovePokemon(location1, pokemon1),
                LOCATION_POKEMON_NOT_EXIST);
    TEST_EQUALS(result, locationRemovePokemon(location3, pokemon1),
                LOCATION_SUCCESS);
    TEST_EQUALS(result, locationRemovePokemon(location3, pokemon1),
                LOCATION_SUCCESS);
    TEST_EQUALS(result, locationAddNearLocation(location3, nearLocation1),
                LOCATION_SUCCESS);
    TEST_EQUALS(result, locationRemoveNearLocation(location3, nearLocation1),
                LOCATION_SUCCESS);
    TEST_EQUALS(result, locationIsNearDestination(location3, nearLocation1),
                false);
    TEST_EQUALS(result, locationIsNearDestination(location3, nearLocation5),
                false);
    locationAddNearLocation(location3, nearLocation5);
    TEST_EQUALS(result, locationIsNearDestination(location3, nearLocation1),
                true);
    TEST_EQUALS(result, locationRemoveNearLocation(location3, nearLocation5),
                LOCATION_SUCCESS);
    TEST_EQUALS(result, locationIsNearDestination(location3, nearLocation5),
                false);
    TEST_EQUALS(result, locationRemoveNearLocation(location3, nearLocation5),
                LOCATION_NEAR_LOCATION_NOT_EXIST);
    TEST_EQUALS(result, locationAddNearLocation(location4, nearLocation5),
                LOCATION_NULL_ARGUMENT);
    TEST_EQUALS(result, locationAddNearLocation(location1, nearLocation6),
                LOCATION_NULL_ARGUMENT);
    TEST_EQUALS(result, locationAddPokemon(location5, pokemon3),
                LOCATION_NULL_ARGUMENT);
    TEST_EQUALS(result, locationAddPokemon(location4, pokemon3),
                LOCATION_NULL_ARGUMENT);
    /* ------------------------  destruction  ------------------------- */
    nearLocationDestroy(nearLocation1);
    nearLocationDestroy(nearLocation2);
    nearLocationDestroy(nearLocation3);
    nearLocationDestroy(nearLocation4);
    nearLocationDestroy(nearLocation5);
    nearLocationDestroy(nearLocation6);
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
    pokemonDestroy(pokemon5);
    pokemonDestroy(pokemon6);
    pokemonDestroy(pokemon7);
    pokemonDestroy(pokemon8);
    return result;

}

static bool testWorldMapCombo() {
    bool result = true;

    /* -----------------------  initialization  ----------------------- */
    NearLocation nearLocation1 = nearLocationCreate("Israel");
    NearLocation nearLocation2 = nearLocationCreate("USA");
    NearLocation nearLocation3 = nearLocationCreate("Japan");
    NearLocation nearLocation4 = nearLocationCreate("France");
    NearLocation nearLocation5 = nearLocationCopy(nearLocation4);
    NearLocation nearLocation6 = NULL;
    Pokedex pokedex = pokedexCreate();
    PokemonInfo pokemon_info1 = pokedexPokemonInfoCreate("Pikachu", 30);
    PokemonInfo pokemon_info2 = pokedexPokemonInfoCreate("Balbazur", 20);
    PokemonInfo pokemon_info3 = pokedexPokemonInfoCreate("Togopi", 20);
    Pokemon pokemon1 = pokemonCreate("Pikacho", pokedex);
    Pokemon pokemon2 = pokemonCreate("Balbazur", pokedex);
    Pokemon pokemon3 = pokemonCreate("Togopi", pokedex);
    Pokemon pokemon4 = NULL;
    Location location1 = locationCreate("Israel");
    Location location2 = locationCreate("USA");
    Location location3 = locationCreate("Japan");
    Location location4 = NULL;
    Location location5 = locationCopy(location1);
    locationAddPokemon(location1, pokemon1);
    locationAddPokemon(location1, pokemon2);
    locationAddPokemon(location1, pokemon1);
    locationAddPokemon(location2, pokemon3);
    locationAddPokemon(location2, pokemon2);
    locationAddPokemon(location3, pokemon1);
    locationAddPokemon(location5, pokemon3);
    locationAddPokemon(location5, pokemon3);
    locationAddNearLocation(location1, nearLocation2);
    locationAddNearLocation(location1, nearLocation3);
    locationAddNearLocation(location2, nearLocation1);
    locationAddNearLocation(location3, nearLocation1);
    WorldMap world_map = worldMapCreate();
    /* ----------------------------- tests ---------------------------- */
    TEST_EQUALS(result, worldMapGetSize(world_map), 0);
    TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
                WORLD_MAP_SUCCESS);
    TEST_EQUALS(result, worldMapAddLocation(world_map, location1),
                WORLD_MAP_LOCATION_ALREADY_EXISTS);
    TEST_EQUALS(result, worldMapAddLocation(world_map, location3),
                WORLD_MAP_SUCCESS);
    TEST_EQUALS(result, worldMapAddLocation(world_map, location4),
                WORLD_MAP_NULL_ARGUMENT);
    TEST_EQUALS(result, worldMapAddLocation(world_map, location5),
                WORLD_MAP_SUCCESS);
    TEST_EQUALS(result, worldMapRemoveLocation(world_map, location2),
                WORLD_MAP_LOCATION_NOT_EXIST);
    TEST_EQUALS(result, worldMapRemoveLocation(world_map, location3),
                WORLD_MAP_SUCCESS);
    TEST_EQUALS(result, worldMapGetSize(world_map), 2);
    TEST_EQUALS(result, worldMapRemoveLocation(world_map, location4),
                WORLD_MAP_NULL_ARGUMENT);
    TEST_EQUALS(result, worldMapAddLocation(world_map, location2),
                WORLD_MAP_SUCCESS);
    TEST_EQUALS(result, worldMapGetSize(world_map), 3);
    TEST_EQUALS(result,locationCompare(worldMapGetLocation(world_map,locationGetName(location1)),location1),0);
    TEST_EQUALS(result,worldMapGetLocation(world_map,locationGetName(location3)),NULL);
    TEST_EQUALS(result,worldMapGetLocation(world_map,""),NULL);
    TEST_EQUALS(result,worldMapGetLocation(world_map,NULL),NULL);
    worldMapSort(world_map);
    TEST_EQUALS(result, worldMapGetSize(world_map), 3);

    /* ------------------------  destruction  ------------------------- */
    nearLocationDestroy( nearLocation1);
    nearLocationDestroy(nearLocation2);
    nearLocationDestroy(nearLocation3);
    nearLocationDestroy(nearLocation4);
    nearLocationDestroy(nearLocation5);
    nearLocationDestroy(nearLocation6);
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
    worldMapDestroy(world_map);

    return result;
}

int main() {
    RUN_TEST(testNearLocationCombo);
    RUN_TEST(testLocationCombo);
    RUN_TEST(testWorldMapCombo);
    return 0;
}
