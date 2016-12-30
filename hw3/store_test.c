/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include "store.h"
#include "aux_macros.h"
#include <assert.h>
//
///**************************************
// *         Static Functions           *
// **************************************/
//
//static bool testItemCombo() {
//    bool result = true;
///* -----------------------  initialization  ----------------------- */
//    Item item1 = itemCreate(0,"TYPE_CANDY");
//    Item item2 = itemCreate(40,"TYPE_CANDY");
//    Item item3 = itemCreate(100,"TYPE_POTION");
//    Item item4 = itemCopy(item2);
///* ----------------------------- tests ---------------------------- */
//    TEST_EQUALS(result,item1,NULL);
//    TEST_DIFFERENT(result,item2,NULL);
//    TEST_EQUALS(result,itemGetValue(item2),40);
//    TEST_EQUALS(result,itemGetType(item3),TYPE_POTION);
//    TEST_EQUALS(result,itemCompare(item2,item4),0);
//    TEST_EQUALS(result,itemCompare(item2,item3),-1);
//    TEST_EQUALS(result,itemCompare(item3,item2),1);
//    TEST_EQUALS(result,itemGetPrice(item2),40);
//    TEST_EQUALS(result,itemGetPrice(item3),200);
///* ------------------------  destruction  ------------------------- */
//    itemDestroy(item1);
//    itemDestroy(item2);
//    itemDestroy(item3);
//    itemDestroy(item4);
//
//    return result;
//}
//
//static bool testStoreCombo() {
//    bool result = true;
///* -----------------------  initialization  ----------------------- */
//    Item item1 = itemCreate(0,"TYPE_CANDY");
//    Item item2 = itemCreate(40,"TYPE_CANDY");
//    Item item3 = itemCreate(100,"TYPE_POTION");
//    Item item4 = itemCopy(item2);
//    Item item5 = itemCopy(item4);
//    Store store1 = storeCreate();
//    assert(store1);
//    storeAddItem(store1,item2);
//    storeAddItem(store1,item3);
//    storeAddItem(store1,item4);
//    storeAddItem(store1,item5);
//    Store store2 = storeCopy(store1);
//    assert(store2);
///* ----------------------------- tests ---------------------------- */
//    TEST_EQUALS(result,storeAddItem(store1,item1),STORE_NULL_ARGUMENT);
//    TEST_EQUALS(result,storeAddItem(store1,item2),STORE_SUCCESS);
//    TEST_EQUALS(result,storeAddItem(store1,item3),STORE_SUCCESS);
//    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
//    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
//    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
//    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
//    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_ITEM_NOT_EXIST);
//    TEST_EQUALS(result,storeDoesItemExist(store1,item2),false);
//    TEST_EQUALS(result,storeRemoveItem(store2,item2),STORE_SUCCESS);
//    TEST_EQUALS(result,storeDoesItemExist(store2,item2),true);
//    TEST_EQUALS(result,storeRemoveItem(store2,item1),STORE_NULL_ARGUMENT);
//    Item item6 = storeSellItem(store2,item3);
//    Item item7 = storeSellItem(store2,item3);
//    TEST_EQUALS(result,itemCompare(item6,item3),0);
//    TEST_EQUALS(result,storeDoesItemExist(store2,item3),false);
//    TEST_DIFFERENT(result,storeSort(store2),STORE_NULL_ARGUMENT);
//    TEST_EQUALS(result,storeDoesItemExist(store2,item2),true);
//    TEST_EQUALS(result,storeDoesItemExist(store2,item3),false);
//
///* ------------------------  destruction  ------------------------- */
//    itemDestroy(item1);
//    itemDestroy(item2);
//    itemDestroy(item3);
//    itemDestroy(item4);
//    itemDestroy(item5);
//    itemDestroy(item6);
//    itemDestroy(item7);
//    storeDestroy(store1);
//    storeDestroy(store2);
//
//    return result;
//}
//
//int main() {
//    RUN_TEST(testItemCombo);
//    RUN_TEST(testStoreCombo);
//    return 0;
//}
