//
// Created by ohad on 14-Jan-17.
//

#include "../pokemon.h"
#include "test_utils.h"
#include "../../hw2/pokemon.h"

using PN=mtm::pokemongo::Pokemon;
using std::set;
using std::string;

bool pokemonTestCombo() {


    return true;
}

bool pokemonTestCtor() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <mtm::pokemongo::PokemonType>types1 =
            set<mtm::pokemongo::PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
    string pikachu_name = "Pikachu";
    double pikacho_cp = 30.3;
    int pikacho_level = 3;


    /* -------------------  initialize one pokemon  ------------------- */

    set <mtm::pokemongo::PokemonType>types2 =
            set<mtm::pokemongo::PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::FIRE);
    string Cyndaquil_name = "Cyndaquil";
    double Cyndaquil_cp = 100.0;
    int Cyndaquil_level = 4;


    /* -------------------  initialize one pokemon  ------------------- */

    //check if throw empty string
    set <mtm::pokemongo::PokemonType>types3 =
            set<mtm::pokemongo::PokemonType>();
    types3.insert(mtm::pokemongo::PokemonType::NORMAL);
    string Bad_pokemon1_name = "";
    double Bad_pokemon1_cp = 90.9;
    int Bad_pokemon1_level = 4;



    /* -------------------  initialize one pokemon  ------------------- */

//    // TODO: add this test and check it on eclipse
//    string poor_pokemon_name = "poor_pokemon";
//    double poor_pokemon_cp = 80.0;
//    int poor_pokemon_level = 7;


    /* -------------------  initialize one pokemon  ------------------- */

    //check if throw invalid cp
    set <mtm::pokemongo::PokemonType>types5 =
            set<mtm::pokemongo::PokemonType>();
    types3.insert(mtm::pokemongo::PokemonType::NORMAL);
    string Bad_pokemon3_name = "Bad_pokemon3";
    double Bad_pokemon3_cp = -90.8;
    int Bad_pokemon3_level = 4;


    /* -------------------  initialize one pokemon  ------------------- */

    //check if throw invalid level
    set <mtm::pokemongo::PokemonType>types6 = set<mtm::pokemongo::PokemonType>();
    types6.insert(mtm::pokemongo::PokemonType::GROUND);
    types6.insert(mtm::pokemongo::PokemonType::NORMAL);
    types6.insert(mtm::pokemongo::PokemonType::WATER);
    string Bad_pokemon4_name = "Bad_pokemon4";
    double Bad_pokemon4_cp = 40.8;
    int Bad_pokemon4_level = 0;



    /********************************************************************
     *                              tests                               *
     ********************************************************************/

    ASSERT_NO_THROW(PN( pikachu_name , types1 , pikacho_cp , pikacho_level ));
    ASSERT_NO_THROW( PN( Cyndaquil_name , types2 ,
                         Cyndaquil_cp, Cyndaquil_level ));
    ASSERT_THROW( mtm::pokemongo::PokemonInvalidArgsException,
                  PN( Bad_pokemon1_name , types3 ,
                      Bad_pokemon1_cp, Bad_pokemon1_level ));
//    ASSERT_NO_THROW( PN( poor_pokemon_name , poor_pokemon_cp, TODO: remove comments
//                         poor_pokemon_level ));
    ASSERT_THROW( mtm::pokemongo::PokemonInvalidArgsException,
                  PN( Bad_pokemon3_name , types5 ,
                      Bad_pokemon3_cp, Bad_pokemon3_level ));
    ASSERT_THROW( mtm::pokemongo::PokemonInvalidArgsException,
                  PN( Bad_pokemon4_name , types6 ,
                      Bad_pokemon4_cp, Bad_pokemon4_level ));


    return true;
}

bool pokemonTestCopyCtor() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <mtm::pokemongo::PokemonType>types1 =
            set<mtm::pokemongo::PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
    string pikachu_name = "Pikachu";
    double pikacho_cp = 30.3;
    int pikacho_level = 3;


    /********************************************************************
     *                              tests                               *
     ********************************************************************/
    PN pikachu = PN( pikachu_name , types1 , pikacho_cp , pikacho_level );
    PN pikachu_copy = PN(pikachu);
    ASSERT_TRUE(pikachu == pikachu_copy);


    return true;
}

bool pokemonTestOperators() {


    return true;
}

bool pokemonTestGetLevel() {


    return true;
}

bool pokemonTestPokemonCompare() {


    return true;
}

bool pokemonTestHit() {


    return true;
}

bool pokemonTestHeal() {


    return true;
}

bool pokemonTestTrain() {


    return true;
}



bool pokemonTest() {
    RUN_TEST(pokemonTestCombo);
    RUN_TEST(pokemonTestCtor);
    RUN_TEST(pokemonTestCopyCtor);
    RUN_TEST(pokemonTestOperators);
    RUN_TEST(pokemonTestGetLevel);
    RUN_TEST(pokemonTestPokemonCompare);
    RUN_TEST(pokemonTestHit);
    RUN_TEST(pokemonTestHeal);
    RUN_TEST(pokemonTestTrain);
    return true;
}

int main() {
    pokemonTest();
    return 0;
}