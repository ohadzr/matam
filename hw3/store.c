/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "store.h"

/**************************************
 *              Defines               *
 **************************************/

#define MAX_TYPE_NUMBER 3
#define NOT_FOR_SALE -1
#define ADD 1
#define SUB -1

/**************************************
 *              Structs               *
 **************************************/

struct item_t { //TODO: should be in h. file
	ItemType type;
	int quantity;
	int value;
	Item next_item;
};

struct store_t {
	Item items;
};

/**************************************
 *         Static Functions           *
 **************************************/

/* return true if value > 0 */
int static positiveCheck(int value) {
	return (value > 0);
}

/* check if type exists - return true if so */
bool static isValidType(ItemType type) {
	for ( int i = 0 ; i < MAX_TYPE_NUMBER ; i++ ) {
		if ( type == i ) return true;
	}
	return false;
}

/* return pointer to last item in store */
Item static getLastItem(Store store) {
	assert( store );
	Item start_point = store->items;
	while ( start_point->next_item != NULL ) {
		start_point = start_point->next_item;
	}
	return start_point;
}

/* add new item to store- link copy of item to the end of store items */
StoreResult static updateNewItemInStore(Store store,Item item) {
	if ( !store ) return STORE_NULL_ARG;
	if ( !item ) return STORE_ITEM_NULL_ARG;
	Item last_item_in_store = getLastItem(store);
	last_item_in_store->next_item = itemCopy(item);
	return STORE_SUCCESS;
}

/* return item's quantity */
int itemGetQuantity(Item item) {
	assert( item );
	return item->quantity;
}

/* update item's quantity, if item was not for sale update to 0 */
void static updateQuantity(Item item,int arithmeticFlag) {
	assert( item && ((arithmeticFlag == ADD) || (arithmeticFlag == SUB)) );
	item->quantity += arithmeticFlag;
}

/**************************************
 *        Interface Functions         *
 **************************************/

Item itemCreate(ItemType type,int value) {
	if( !isValidType(type) ) return NULL;
	if ( !positiveCheck(value) ) return NULL;
	Item new_item = malloc(sizeof(*new_item));
	if( !new_item ) return NULL;
	new_item->type = type;
	new_item->quantity = NOT_FOR_SALE;
	new_item->value = value;
	new_item->next_item = NULL;
	return new_item;
}

Item itemCopy(Item item) {
	if ( !item ) return NULL;
	Item copy_item = itemCreate(item->type,item->value);
	if ( !copy_item ) return NULL;
	copy_item->quantity = 1;
	return copy_item;
}

void itemDestroy(Item item) {
	free (item);
}

Item getItemFromStore(Store store,Item item) {
	assert( store && item );
	Item requested_item = store->items;
	while ( itemCompare(requested_item,item) != ITEM_EQUAL ) {
		requested_item = requested_item->next_item;
		if ( !requested_item ) return NULL;
	}
	return requested_item;
}

ItemResult itemCompare(Item item1, Item item2) {
	if ( !item1 || !item2) return ITEM_NULL_ARG;
	if ( (item1->type == item2->type) &&
		 (item1->value == item2->value) ) return ITEM_EQUAL;
	return ITEM_DIFFERENT;
}

int itemPriceGet(Item item) {
	assert( item );
	return (itemGetValue(item) * (itemGetType(item) + 1 ) );
}

Store storeCreate(Item first_item) {
	Store new_store = malloc(sizeof(*new_store));
	if(!new_store) return NULL;
	new_store->items = itemCopy(first_item);
	return new_store;
}

int getNumOfItems(Store store) {
	assert(store);
	int counter = 0;
	Item start_point = store->items;
	while ( start_point ) {
		counter++;
		start_point = start_point->next_item;
	}
	return counter;
}

void storeDestroy(Store store) {
	if ( store ) {
		Item start_point = store->items;
		while ( start_point ) {
			Item temp = start_point->next_item;
			itemDestroy(start_point);
			start_point = temp;
		}
	}
	free(store);
}

bool doesItemExistInStore(Store store,Item item) {
	assert( store );
	Item start_point = store->items;
	while ( start_point ) {
		if( itemCompare(item,start_point) == ITEM_EQUAL ) return true;
		start_point = start_point->next_item;
	}
	return false;
}

StoreResult addItemToStore(Store store,Item item) {
	if ( !store ) return STORE_NULL_ARG;
	if ( !item ) return STORE_ITEM_NULL_ARG;
	if ( !doesItemExistInStore(store,item) )
		return updateNewItemInStore(store,item);
	Item item_to_update = getItemFromStore(store,item);
	updateQuantity(item_to_update,ADD);
	return STORE_SUCCESS;
}

StoreResult destroyStoreItem(Store store,Item item) {
	assert (store && item);
	if (  getNumOfItems( store ) == 1 ) return STORE_DESTROY_LAST;
	if( doesItemExistInStore(store,item) ) {
		Item previous_item = store->items;
		Item item_to_destroy = getItemFromStore(store,item);
		Item next_item = item_to_destroy->next_item;
		while(itemCompare(previous_item->next_item,item_to_destroy)!=ITEM_EQUAL)
			previous_item = previous_item->next_item;
		itemDestroy(item_to_destroy);
		previous_item->next_item = next_item;
	}
	return STORE_SUCCESS;
}

StoreResult sellItem(Store store,Item requsted_item,Item* sold_item) {
	*sold_item = NULL;
	if ( !store ) return STORE_NULL_ARG;
	if ( !requsted_item ) return STORE_ITEM_NULL_ARG;
	if (!doesItemExistInStore(store,requsted_item)) return STORE_ITEM_NOT_EXIST;
	Item item_to_update = getItemFromStore(store,requsted_item);
	int item_to_sell_quantity = itemGetQuantity(item_to_update);
	if ( item_to_sell_quantity == 0 ) return STORE_OUT_OF_STOCK;
	updateQuantity(item_to_update,SUB);
	*sold_item = itemCopy(item_to_update);
	if (*sold_item == NULL) return STORE_OUT_OF_MEM;
	return STORE_SUCCESS;
}

int itemGetValue(Item item) {
	assert(item);
	return item->value;
}

ItemType itemGetType(Item item) {
	assert(item);
	return item->type;
}
