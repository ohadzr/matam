/**************************************
 *       Header files include         *
 **************************************/

#include "../world.h"
#include "test_utils.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::World;

/**************************************
 *               Tests                *
 **************************************/

bool TestCombo() {
    /********************************************************************
    *                              tests                               *
    ********************************************************************/
    World technion();

    ASSERT_NO_THROW("GYM berlin" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTOP israel POTION -10 CANDY 30 CANDY 30" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "GM berlin" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTO israel POTION 10 candy 30 CANDY 30" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTOP israel POTION 10 candy 30 CANDY 30" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldLocationNameAlreadyUsed,
                 "POKESTOP berlin POTION 10 CANDY 30 CANDY 30" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTOP kanada POTION 10 CANDY 30 CANDY 0" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTOP kanada potion 10 CANDY 30 CANDY 0" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTOP china potion1 0CANDY 30 CANDY 0" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTOP LA POTION  CANDY 30 CANDY 0" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "STARBUCKS eygpt pikachu pikachu 1 2 charmander 3.45 4" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "STARBUCKS " >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "STARBUCKS eygpt pikachu pikachu 1 2 charmander 0 4" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldLocationNameAlreadyUsed,
                 "STARBUCKS eygpt pikachu 3 6 pikachu 1 2 charmander 2 4" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "sahar eygpt pikachu 3 6 pikachu 1 2 charmander 2 4" >> technion);
    ASSERT_NO_THROW("STARBUCKS france " >> technion);
    ASSERT_NO_THROW("    STARBUCKS tokyo pikachu  5.4   7 " >> technion);
    ASSERT_NO_THROW("POKESTOP china potion 60 CANDY 100 CANDY 900" >> technion);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 "POKESTOP akraba ALADIN 60 CANDY 100 CANDY 900" >> technion);
}

int main() {
    RUN_TEST(TestCombo);
    return 0;
}
