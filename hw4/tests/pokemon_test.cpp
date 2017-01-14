//
// Created by ohad on 14-Jan-17.
//

#include "../pokemon.h"
#include "test_utils.h"


bool pokemonTestExample() {


    return true;
};

bool pokemonTestCtor() {


    return true;
};

bool pokemonTestCopyCtor() {


    return true;
};

bool pokemonTestOperators() {


    return true;
};

bool pokemonTestGetLevel() {


    return true;
};

bool pokemonTestPokemonCompare() {


    return true;
};

bool pokemonTestHit() {


    return true;
};

bool pokemonTestHeal() {


    return true;
};

bool pokemonTestTrain() {


    return true;
};

bool pokemonTestPrint() {


    return true;
};



bool pokemonTest() {
    RUN_TEST(pokemonTestExample);
    RUN_TEST(pokemonTestCtor);
    RUN_TEST(pokemonTestCopyCtor);
    RUN_TEST(pokemonTestOperators);
    RUN_TEST(pokemonTestGetLevel);
    RUN_TEST(pokemonTestPokemonCompare);
    RUN_TEST(pokemonTestHit);
    RUN_TEST(pokemonTestHeal);
    RUN_TEST(pokemonTestTrain);
    RUN_TEST(pokemonTestPrint); //TODO: remove later
    return true;
}

int main() {
    pokemonTest();
    return 0;
}