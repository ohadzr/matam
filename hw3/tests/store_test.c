/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include "../store.h"
#include "test_utilities.h"

/**************************************
 *         Static Functions           *
 **************************************/

static bool testItemCreateAndDestroy() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(0,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCreate(100,"sahar");
    Item item5 = itemCreate(100,"ohad");
    Item item6 = itemCreate(-1,"potion");
/* ----------------------------- tests ---------------------------- */
    TEST_EQUALS(result,item1,NULL);
    TEST_EQUALS(result,item6,NULL);
    TEST_DIFFERENT(result,item2,NULL);
    TEST_DIFFERENT(result,item3,NULL);
    TEST_EQUALS(result,item4,NULL);
    TEST_EQUALS(result,item5,NULL);
    TEST_EQUALS(result,itemGetPrice(item2),80);
    TEST_EQUALS(result,itemGetPrice(item3),100);
    TEST_EQUALS(result,itemGetType(item3),TYPE_POTION);
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);
    itemDestroy(item6);

    return result;
}

static bool testItemCopy() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(0,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item1);
    Item item5 = itemCopy(item2);
    Item item6 = itemCopy(item3);
    Item item7 = itemCopy(item4);
    Item item8 = NULL;
    Item item9 = itemCopy(item8);
/* ----------------------------- tests ---------------------------- */
    TEST_EQUALS(result,item1,NULL);
    TEST_EQUALS(result,item4,NULL);
    TEST_DIFFERENT(result,item5,NULL);
    TEST_DIFFERENT(result,item6,NULL);
    TEST_EQUALS(result,item7,NULL);
    TEST_EQUALS(result,item9,NULL);
    TEST_EQUALS(result,itemGetValue(item2),itemGetValue(item5));
    TEST_EQUALS(result,itemGetType(item2),itemGetType(item5));
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);
    itemDestroy(item6);
    itemDestroy(item7);
    itemDestroy(item8);
    itemDestroy(item9);
    return result;
}

static bool testItemGetValue() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(10,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item1);
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,itemGetValue(item4),itemGetValue(item2));
    TEST_EQUALS(result,itemGetValue(item1),itemGetValue(item4));
    TEST_DIFFERENT(result,itemGetValue(item3),itemGetValue(item4));
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);

    return result;
}

static bool testItemGetType() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(10,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item1);
/* ----------------------------- tests ---------------------------- */
    TEST_EQUALS(result,itemGetType(item4),itemGetType(item2));
    TEST_EQUALS(result,itemGetType(item1),itemGetType(item4));
    TEST_DIFFERENT(result,itemGetType(item3),itemGetType(item4));
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);

    return result;
}

static bool testItemGetPrice() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(10,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item1);
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,itemGetPrice(item4),itemGetPrice(item2));
    TEST_EQUALS(result,itemGetPrice(item1),itemGetPrice(item4));
    TEST_DIFFERENT(result,itemGetPrice(item3),itemGetPrice(item4));
    TEST_EQUALS(result,itemGetPrice(item1),20);
    TEST_EQUALS(result,itemGetPrice(item2),80);
    TEST_EQUALS(result,itemGetPrice(item3),100);
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);

    return result;
}

static bool testItemCombo() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(30,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item2);
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,item1,NULL);
    TEST_EQUALS(result,itemGetType(item2),itemGetType(item1));
    TEST_EQUALS(result,itemGetPrice(item4),80);
    TEST_EQUALS(result,itemGetType(item1),TYPE_CANDY);
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);

    return result;
}

static bool testStoreCreateAndDestroy() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(30,"candy");
    Item item2 = NULL;
    Store store1 = storeCreate();
    Store store2 = storeCreate();
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,store1,NULL);
    TEST_DIFFERENT(result,store2,NULL);
    TEST_EQUALS(result,storeAddItem(store1,item1),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store1,item2),STORE_NULL_ARGUMENT);
/* ------------------------  destruction  ------------------------- */
    storeDestroy(store1);
    storeDestroy(store2);
    itemDestroy(item1);

    return result;
}

static bool testStoreCopy() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(30,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item2);
    Item item5 = NULL;
    Store store1 = storeCreate();
    storeAddItem(store1,item1);
    storeAddItem(store1,item2);
    storeAddItem(store1,item3);
    storeAddItem(store1,item4);
    storeAddItem(store1,item5);
    Store store2 = storeCopy(store1);
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,store1,NULL);
    TEST_DIFFERENT(result,store2,NULL);
    TEST_EQUALS(result,storeDoesItemExist(store2,item4),true);
    TEST_EQUALS(result,storeDoesItemExist(store2,item3),true);
    TEST_EQUALS(result,storeDoesItemExist(store2,item2),true);
    TEST_EQUALS(result,storeDoesItemExist(store2,item1),true);
    TEST_EQUALS(result,storeDoesItemExist(store2,item5),false);
/* ------------------------  destruction  ------------------------- */
    storeDestroy(store1);
    storeDestroy(store2);
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);

    return result;
}

static bool testStoreAddItem() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(10,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCreate(-100,"potion");
    Item item5 = itemCreate(100,"dog");
    Item item6 = itemCreate(100,"");
    Item item7 = itemCreate(100,NULL);
    Item item8 = itemCreate(0,NULL);
    Item item9 = itemCopy(item1);
    Store store = storeCreate();
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,store,NULL);
    TEST_EQUALS(result,storeAddItem(store,item1),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store,item3),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store,item4),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item5),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item6),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item7),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item8),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item9),STORE_SUCCESS);
    TEST_EQUALS(result,storeDoesItemExist(store,item1),true);
    TEST_EQUALS(result,storeDoesItemExist(store,item2),true);
    TEST_EQUALS(result,storeDoesItemExist(store,item3),true);
    TEST_EQUALS(result,storeDoesItemExist(store,item4),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item5),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item6),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item7),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item8),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item9),true);
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);
    itemDestroy(item6);
    itemDestroy(item7);
    itemDestroy(item8);
    itemDestroy(item9);
    storeDestroy(store);

    return result;
}

static bool testStoreRemoveItem() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(10,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCreate(-100,"potion");
    Item item5 = itemCreate(100,"dog");
    Item item6 = itemCreate(100,"");
    Item item7 = itemCreate(100,NULL);
    Item item8 = itemCreate(0,NULL);
    Item item9 = itemCopy(item1);
    Store store = storeCreate();
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,store,NULL);
    TEST_EQUALS(result,storeAddItem(store,item1),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store,item3),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store,item4),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item5),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item6),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item7),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item8),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store,item9),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store,item1),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store,item3),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store,item4),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeRemoveItem(store,item5),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeRemoveItem(store,item6),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeRemoveItem(store,item7),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeRemoveItem(store,item8),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeRemoveItem(store,item9),STORE_SUCCESS);
    TEST_EQUALS(result,storeDoesItemExist(store,item1),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item2),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item3),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item4),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item5),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item6),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item7),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item8),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item9),false);
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);
    itemDestroy(item6);
    itemDestroy(item7);
    itemDestroy(item8);
    itemDestroy(item9);
    storeDestroy(store);

    return result;
}

static bool testStoreSellItem() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(30,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item2);
    Store store = storeCreate();
    storeAddItem(store,item1);
    storeAddItem(store,item2);
    storeAddItem(store,item3);
    storeAddItem(store,item4);
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,item1,NULL);
    Item item5 = storeSellItem(store,item2);
    TEST_EQUALS(result,storeDoesItemExist(store,item2),true);
    Item item6 = storeSellItem(store,item2);
    TEST_EQUALS(result,storeDoesItemExist(store,item2),false);
    TEST_EQUALS(result,storeDoesItemExist(store,item1),true);
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);
    itemDestroy(item6);
    storeDestroy(store);

    return result;
}

static bool testStoreDoesItemExist() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(30,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item2);
    Item item5 = itemCreate(180,"potion");
    Store store = storeCreate();
    storeAddItem(store,item1);
    storeAddItem(store,item2);
    storeAddItem(store,item3);
    storeAddItem(store,item4);
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,item1,NULL);
    TEST_EQUALS(result,storeDoesItemExist(store,item1),true);
    TEST_EQUALS(result,storeDoesItemExist(store,item2),true);
    TEST_EQUALS(result,storeDoesItemExist(store,item3),true);
    TEST_EQUALS(result,storeDoesItemExist(store,item4),true);
    TEST_EQUALS(result,storeDoesItemExist(store,item5),false);

/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);
    storeDestroy(store);

    return result;
}

static bool testStoreCombo() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */
    Item item1 = itemCreate(0,"candy");
    Item item2 = itemCreate(40,"candy");
    Item item3 = itemCreate(100,"potion");
    Item item4 = itemCopy(item2);
    Item item5 = itemCopy(item4);
    Store store1 = storeCreate();
    storeAddItem(store1,item2);
    storeAddItem(store1,item3);
    storeAddItem(store1,item4);
    storeAddItem(store1,item5);
    Store store2 = storeCopy(store1);
    storeAddItem(store2,item2);
    storeAddItem(store2,item3);
    storeAddItem(store2,item4);
    storeAddItem(store2,item5);
/* ----------------------------- tests ---------------------------- */
    TEST_DIFFERENT(result,store1,NULL);
    TEST_DIFFERENT(result,store2,NULL);
    TEST_EQUALS(result,storeAddItem(store1,item1),STORE_NULL_ARGUMENT);
    TEST_EQUALS(result,storeAddItem(store1,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeAddItem(store1,item3),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeRemoveItem(store1,item2),STORE_ITEM_NOT_EXIST);
    TEST_EQUALS(result,storeDoesItemExist(store1,item2),false);
    TEST_EQUALS(result,storeRemoveItem(store2,item2),STORE_SUCCESS);
    TEST_EQUALS(result,storeDoesItemExist(store2,item2),true);
    TEST_EQUALS(result,storeRemoveItem(store2,item1),STORE_NULL_ARGUMENT);
    Item item6 = storeSellItem(store2,item3);
    Item item7 = storeSellItem(store2,item3);
    TEST_EQUALS(result,storeDoesItemExist(store2,item7),false);
    TEST_EQUALS(result,storeDoesItemExist(store2,item3),false);
/* ------------------------  destruction  ------------------------- */
    itemDestroy(item1);
    itemDestroy(item2);
    itemDestroy(item3);
    itemDestroy(item4);
    itemDestroy(item5);
    itemDestroy(item6);
    itemDestroy(item7);
    storeDestroy(store1);
    storeDestroy(store2);

    return result;
}

int main() {
    RUN_TEST(testItemCreateAndDestroy);
    RUN_TEST(testItemCopy);
    RUN_TEST(testItemGetValue);
    RUN_TEST(testItemGetType);
    RUN_TEST(testItemGetPrice);
    // itemIsValidArgs will be tested in pokemon_go;
    RUN_TEST(testItemCombo);

    RUN_TEST(testStoreCreateAndDestroy);
    RUN_TEST(testStoreCopy);
    RUN_TEST(testStoreAddItem);
    RUN_TEST(testStoreRemoveItem);
    RUN_TEST(testStoreSellItem);
    RUN_TEST(testStoreDoesItemExist);
    // storeSort test will be tested in pokemon_go
    // storePrintStock test will be tested in pokemon_go
    RUN_TEST(testStoreCombo);
    return 0;
}
