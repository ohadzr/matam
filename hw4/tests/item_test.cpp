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

    ASSERT_NO_THROW(Item("POTION", 1));
    ASSERT_NO_THROW(Item("CANDY", 1));
    ASSERT_THROW(mtm::pokemongo::ItemInvalidArgsException, Item("Tomer", 1));
    ASSERT_THROW(mtm::pokemongo::ItemInvalidArgsException, Item("CANDY", -1));
    ASSERT_THROW(mtm::pokemongo::ItemInvalidArgsException, Item("POTION", 0));


    Item item1 = Item("POTION", 1);
    Item item2 = Item("CANDY", 2);
    Item item3 = Item("POTION", 4);

    Item item4(item2);
    Item item5(item1);

    ASSERT_EQUAL(item2.getLevel(), item4.getLevel());
    ASSERT_EQUAL(item1.getType(), item5.getType());

    return true;
}


//int main() {
//    RUN_TEST(TestComboItem);
//    return 0;
//}
