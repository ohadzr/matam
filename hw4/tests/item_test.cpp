/**************************************
 *       Header files include         *
 **************************************/

#include "../item.h"
#include "test_utils.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::Item;

/**************************************
 *               Tests                *
 **************************************/

bool TestComboItem() {
    /********************************************************************
    *                              tests                               *
    ********************************************************************/
    /* -------------------     test constractor    ------------------- */

    ASSERT_NO_THROW( Item("POTION",1) );
    ASSERT_NO_THROW( Item("CANDY",1) );
    ASSERT_THROW( mtm::pokemongo::ItemInvalidArgsException , Item("Tomer",1) );
    ASSERT_THROW( mtm::pokemongo::ItemInvalidArgsException , Item("CANDY",-1) );
    ASSERT_THROW( mtm::pokemongo::ItemInvalidArgsException , Item("POTION",0) );

    /* -------------------     test constractor    ------------------- */




    int main() {
    RUN_TEST(TestComboItem);
    return 0;
}