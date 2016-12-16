
#ifndef STORE_H_
#define STORE_H_

/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**************************************
 *        Structs declarations        *
 **************************************/

typedef struct item_t* Item;
typedef struct store_t* Store;

/**************************************
 *         Enum declarations          *
 **************************************/
typedef enum {ITEM_NULL_ARG,
			  ITEM_EOUAL,
			  ITEM_DIFFERENT} ItemResult;

typedef enum {Potion,Candy} ItemType;

typedef enum {STORE_SUCCESS,
			  STORE_NULL_ARG,
			  STORE_ITEM_NULL_ARG,
			  STORE_ITEM_NOT_EXIST,
			  STORE_OUT_OF_STOCK,
			  STORE_OUT_OF_MEM,
			  STORE_DESTROY_LAST} StoreResult;

/**************************************
 *      Functions declarations        *
 **************************************/
/* return new item if type invalid or value <= 0 or or allocation failed
 * return NULL */
Item itemCreate(ItemType type,int value);

/* return copy of item, return NULL if item_to_copy were NULL */
Item itemCopy(Item item);

/* destroy single item */
void itemDestroy(Item item);

/* compare items - if value && type equal return true, false else */
ItemResult itemCompare(Item item1, Item item2);

/* return item price based on items type */
int itemPriceGet(Item item);

/* create new store,condition for create is first item, return NULL if item
 * is NULL or allocation failed */
Store storeCreate(Item first_item);

/* return kind of items in store - not quantity */
int getNumOfItems(Store store);

/* destroy store and all of it's items, it's not possible to destroy store's
 * last item */
void storeDestroy(Store store);

/* return true if item exist in store, false else */
bool doesItemExistInStore(Store store,Item item);

/* add item to store if store & item != NULL, if item already exist then raise
 * its quantity in store */
StoreResult addItemToStore(Store store,Item item);

/* delete kind of item from store */
StoreResult destroyStoreItem(Store store,Item item);

/* return item from store if it exist to buyer and update quantity in store */
StoreResult sellItem(Store store,Item requsted_item,Item* sold_item);

/* return items quantity */
int itemGetQuantity(Item item);

#endif /* STORE_H_ */
