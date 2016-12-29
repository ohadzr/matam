#include <stdbool.h>
#include "aux_macros.h"
#include "pokedex.h"

static bool testCombo() {
	bool result = true;

    Pokedex pokedex = pokedexCreate();
    TEST_DIFFERENT(result, pokedex, NULL);

    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 50);
    PokemonInfo squirtel_info = pokedexPokemonInfoCreate("Squirtel", 30);



    TEST_EQUALS(result, pokedexAddPokemonInfo(pokedex, pikachu_info),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexAddPokemonInfo(pokedex, raichu_info),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexAddPokemonInfo(pokedex, squirtel_info),
                POKEDEX_SUCCESS);


    TEST_EQUALS(result, pokedexAddType(pokedex, "Pikachu", "NORMAL"),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexAddType(pokedex, "Pikachu", "ELECTRIC"),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexGetStarBonus(pokedex, "Pikachu"), 20);



    TEST_EQUALS(result, pokedexAddType(pokedex, "Squirtel", "WATER"),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexAddType(pokedex, "Squirtel", "POISON"),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexGetStarBonus(pokedex, "Squirtel"), 30);

    TEST_DIFFERENT(result, pokedexPokemonInfoCompare(pikachu_info,
                                                     squirtel_info), 0);

    TEST_EQUALS(result, pokedexUpdateNextEvolution(pokedex,"Pikachu", "Raichu",
                                                   6), POKEDEX_SUCCESS);

    TEST_EQUALS(result, strcmp("Raichu", pokedexGetNextEvolution(pokedex,
                                                   "Pikachu", 6)), 0);

    TEST_EQUALS(result, pokedexGetInitialCP(pokedex, "Pikachu"), 10);

    pokedexPokemonInfoDestroy(raichu_info);
    pokedexPokemonInfoDestroy(squirtel_info);
    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexDestroy(pokedex);


    return result;
}


static bool testPokedexPokemonInfoCreateDestroy() {
    bool result = true;
    PokemonInfo pokemon_info = pokedexPokemonInfoCreate("Pikachu", 10);
    TEST_DIFFERENT(result, pokemon_info, NULL);
    TEST_EQUALS(result, pokedexPokemonInfoCreate(NULL, 10), NULL);
    TEST_EQUALS(result, pokedexPokemonInfoCreate("Pikachu", -10), NULL);

    pokedexPokemonInfoDestroy(pokemon_info);

    return result;
}

static bool testPokedexPokemonInfoCopy() {
    bool result = true;
    PokemonInfo pokemon_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo pokemon_info_copy = pokedexPokemonInfoCopy(pokemon_info);

    TEST_DIFFERENT(result, pokemon_info_copy, NULL);
    TEST_EQUALS(result, pokedexPokemonInfoCopy(NULL), NULL);

    pokedexPokemonInfoDestroy(pokemon_info_copy);
    pokedexPokemonInfoDestroy(pokemon_info);

    return result;
}

static bool testPokedexPokemonInfoCompare() {
    bool result = true;
    PokemonInfo pokemon_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo pokemon_info_copy = pokedexPokemonInfoCopy(pokemon_info);
    PokemonInfo pokemon_info_diff = pokedexPokemonInfoCreate("Squirtel", 10);
    TEST_EQUALS(result, pokedexPokemonInfoCompare(pokemon_info,
                                                  pokemon_info_copy), 0);
    TEST_DIFFERENT(result, pokedexPokemonInfoCompare(pokemon_info,
                                                  pokemon_info_diff), 0);

    pokedexPokemonInfoDestroy(pokemon_info_diff);
    pokedexPokemonInfoDestroy(pokemon_info_copy);
    pokedexPokemonInfoDestroy(pokemon_info);

    return result;
}


static bool testPokedexCreateDestroy() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    TEST_DIFFERENT(result, pokedex, NULL);

    pokedexDestroy(pokedex);

    return result;
}

static bool testPokedexAddPokemonInfo() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    TEST_DIFFERENT(result, pokedex, NULL);

    PokemonInfo pokemon_info = pokedexPokemonInfoCreate("Pikachu", 10);
    TEST_EQUALS(result, pokedexAddPokemonInfo(pokedex, pokemon_info),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexAddPokemonInfo(pokedex, NULL),
                POKEDEX_NULL_ARG);
    TEST_EQUALS(result, pokedexAddPokemonInfo(NULL, pokemon_info),
                POKEDEX_NULL_ARG);

    pokedexPokemonInfoDestroy(pokemon_info);
    pokedexDestroy(pokedex);

    return result;
}

static bool testPokedexGetInitialCP() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    TEST_DIFFERENT(result, pokedex, NULL);

    PokemonInfo pokemon_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pokemon_info);

    TEST_EQUALS(result, pokedexGetInitialCP(pokedex, "Pikachu"), 10);


    pokedexPokemonInfoDestroy(pokemon_info);
    pokedexDestroy(pokedex);

    return result;
}


static bool testPokedexAddType() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    TEST_DIFFERENT(result, pokedex, NULL);

    PokemonInfo pokemon_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pokemon_info);

    TEST_EQUALS(result, pokedexAddType(pokedex, "Pikachu", "ELECTRIC"),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexAddType(pokedex, "Pikachu", "NORMAL"),
                POKEDEX_SUCCESS);


    pokedexPokemonInfoDestroy(pokemon_info);
    pokedexDestroy(pokedex);

    return result;
}

static bool testPokedexGetStarBonus() {
    bool result = true;

    Pokedex pokedex = pokedexCreate();
    TEST_DIFFERENT(result, pokedex, NULL);

    PokemonInfo pokemon_info = pokedexPokemonInfoCreate("Pikachu", 10);
    pokedexAddPokemonInfo(pokedex, pokemon_info);

    pokedexAddType(pokedex, "Pikachu", "NORMAL");
    TEST_EQUALS(result, pokedexGetStarBonus(pokedex, "Pikachu"), 10);

    pokedexAddType(pokedex, "Pikachu", "ELECTRIC");
    TEST_EQUALS(result, pokedexGetStarBonus(pokedex, "Pikachu"), 20);

    pokedexAddType(pokedex, "Pikachu", "FIRE");
    TEST_EQUALS(result, pokedexGetStarBonus(pokedex, "Pikachu"), 30);

    pokedexPokemonInfoDestroy(pokemon_info);
    pokedexDestroy(pokedex);

    return result;
}

static bool testPokedexUpdateNextEvolution() {
    bool result = true;

    PokemonInfo pikachu_info = pokedexPokemonInfoCreate("Pikachu", 10);
    PokemonInfo raichu_info = pokedexPokemonInfoCreate("Raichu", 40);

    Pokedex pokedex = pokedexCreate();
    pokedexAddPokemonInfo(pokedex, pikachu_info);
    pokedexAddPokemonInfo(pokedex, raichu_info);

    TEST_EQUALS(result, pokedexUpdateNextEvolution(pokedex, "Pikachu",
                                                   "Raichu", 6),
                POKEDEX_SUCCESS);
    TEST_EQUALS(result, pokedexUpdateNextEvolution(pokedex, "Raichu",
                                                   "BigRaichu", 10),
                POKEDEX_SUCCESS);


    TEST_EQUALS(result, strcmp("Raichu", pokedexGetNextEvolution(pokedex,
                                                          "Pikachu", 6)), 0);
    TEST_EQUALS(result, strcmp("BigRaichu", pokedexGetNextEvolution(pokedex,
                                                          "Pikachu", 12)), 0);
    TEST_EQUALS(result, strcmp("BigRaichu", pokedexGetNextEvolution(pokedex,
                                                           "Raichu", 12)), 0);
    TEST_EQUALS(result, strcmp("BigRaichu", pokedexGetNextEvolution(pokedex,
                                                        "BigRaichu", 12)), 0);
    TEST_DIFFERENT(result, strcmp("Raichu", pokedexGetNextEvolution(pokedex,
                                                   "Pikachu", 5)), 0);

    pokedexPokemonInfoDestroy(pikachu_info);
    pokedexPokemonInfoDestroy(raichu_info);
    pokedexDestroy(pokedex);

    return result;
}

int main() {

    RUN_TEST(testCombo);
    RUN_TEST(testPokedexPokemonInfoCreateDestroy);
    RUN_TEST(testPokedexPokemonInfoCopy);
    RUN_TEST(testPokedexPokemonInfoCompare);
    RUN_TEST(testPokedexCreateDestroy);
    RUN_TEST(testPokedexAddPokemonInfo);
    RUN_TEST(testPokedexGetInitialCP);
    RUN_TEST(testPokedexAddType);
    RUN_TEST(testPokedexGetStarBonus);
    RUN_TEST(testPokedexUpdateNextEvolution);
	return 0;
}
