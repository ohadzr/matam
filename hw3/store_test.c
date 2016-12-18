#include <stdio.h>
#include <stdbool.h>
#include "aux_macros.h"
#include "store.h"

static bool testCombo() {
	bool result = true;
/* -----------------------  initialization  ----------------------- */

	Item  item1 = itemCreate(TYPE_POTION,10);
	Item  item2 = itemCreate(TYPE_POTION,20);
	Item  item3 = itemCreate(TYPE_CANDY,20);
	Item  item4_BadValue = itemCreate(TYPE_POTION,0);
	Item  item5_badType = itemCreate(3,0);
	Item  item6 = itemCreate(TYPE_CANDY,90);
	Item  item1_copy = itemCopy(item1);
	Store our_store = storeCreate(item6);
	Item item_bag1 = NULL;
	Item item_bag2 = NULL;
	Item item_bag3 = NULL;
	addItemToStore(our_store,item1);
	addItemToStore(our_store,item2);
	addItemToStore(our_store,item3);
	Store my_store = storeCreate(item1);

/* ---------------------- Integration tests ----------------------- */

	TEST_EQUALS(result, itemCompare(item1,item1_copy),ITEM_EQUAL);
	TEST_DIFFERENT(result, itemCompare(item1,item2),ITEM_EQUAL);
	TEST_EQUALS(result, itemPriceGet(item1),10);
	TEST_EQUALS(result, item4_BadValue,NULL);
	TEST_EQUALS(result, item5_badType,NULL);
	TEST_EQUALS(result,getNumOfItems(our_store),4);
	TEST_EQUALS(result,doesItemExistInStore(our_store,item6),true);
	TEST_EQUALS(result,doesItemExistInStore(our_store,item2),true);
	destroyStoreItem(our_store,item2);
	TEST_EQUALS(result,getNumOfItems(our_store),3);
	TEST_DIFFERENT(result,doesItemExistInStore(our_store,item2),true);
	addItemToStore(our_store,item1);
	TEST_EQUALS(result,getNumOfItems(our_store),3);
	sellItem(our_store,item1,&item_bag1);
	TEST_EQUALS(result,itemCompare(item_bag1,item1),ITEM_EQUAL);
	TEST_EQUALS(result,sellItem(our_store,item6,&item_bag2),STORE_SUCCESS);
	TEST_EQUALS(result,itemCompare(item_bag2,item6),ITEM_EQUAL);
	TEST_EQUALS(result,sellItem(our_store,item6,&item_bag3),STORE_OUT_OF_STOCK);
	TEST_EQUALS(result,item_bag3,NULL);
	TEST_EQUALS(result,sellItem(our_store,item2,&item_bag3),STORE_ITEM_NOT_EXIST);
	TEST_EQUALS(result,item_bag3,NULL);
	TEST_EQUALS(result,getNumOfItems(my_store),1);
	TEST_EQUALS(result,destroyStoreItem(my_store,item1),STORE_DESTROY_LAST);
	addItemToStore(my_store,item1);
	TEST_EQUALS(result,getNumOfItems(my_store),1);


/* ------------------------  destruction  ------------------------- */

	itemDestroy(item1);
	itemDestroy(item2);
	itemDestroy(item3);
	itemDestroy(item4_BadValue);
	itemDestroy(item5_badType);
	itemDestroy(item6);
	itemDestroy(item1_copy);
	itemDestroy(item_bag1);
	itemDestroy(item_bag2);
	itemDestroy(item_bag3);
	storeDestroy(our_store);
	storeDestroy(my_store);

	return result;
}
int main() {
	RUN_TEST(testCombo); //TODO: should we have more test? for each function independently and not only combo?
	return 0;
}
