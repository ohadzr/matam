
#ifndef STORE_H_
#define STORE_H_

/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "print_utils.h"
#include "list.h"

#define STORE_FOREACH(type,iterator,list) \
	for(type iterator = listGetFirst(list) ; \
		iterator ;\
		iterator = listGetNext(list))


/**************************************
 *        Structs declarations        *
 **************************************/

typedef struct item_t* Item;
typedef List Store;
typedef void* ItemElement;

/**************************************
 *         Enum declarations          *
 **************************************/

typedef enum {TYPE_CANDY,TYPE_POTION} ItemType;

typedef enum {STORE_SUCCESS,
              STORE_NULL_ARGUMENT,
	          STORE_ITEM_NOT_EXIST,
	          STORE_OUT_OF_STOCK,
	          STORE_OUT_OF_MEMORY,
	          STORE_DESTROY_LAST} StoreResult;

/**************************************
 *      Functions declarations        *
 **************************************/

/* return new item or NULL if type invalid || value<= 0 || not enough memory */
Item itemCreate( int value,ItemType type );

/* if item == NULL do nothing, else free all memory allocated to item */
void itemDestroy( Item item );

/* if item valid and enough memory return copy of item */
Item itemCopy( Item item );

/* return item's value */
int itemGetValue( Item item );

/* return item's type */
ItemType itemGetType( Item item );

/* return item price according to it's type */
int itemGetPrice( Item item );

/* define: if items has the same value and same type then they equal. function
 * return 0 if items equal, 1 if item1 > item2 and -1 if item2 > item1 */
int itemCompare( Item item1 , Item item2 );

/* return new store with no items in it. return NULL if not enough memory */
Store storeCreate();

/* if store == NULL do nothing, else free all memory allocated to store */
void storeDestroy( Store store );

/* return copy of store or NULL if given store == NULL or not enough memory*/
Store storeCopy( Store store );

/* add new item to store
 * return values:
 * STORE_NULL_ARGUMENT - if item/store were NULL
 * STORE_OUT_OF_MEMORY - if an allocation failed
 * STORE_SUCCESS - the item has been inserted successfully */
StoreResult storeAddItem ( Store store , Item item );

/* remove all memory of item from store.
 * return values:
 * STORE_NULL_ARGUMENT - if store or item is NULL
 * STORE_ITEM_NOT_EXIST - if item was not in store
 * STORE_SUCCESS - if item was removed successfully */
StoreResult storeRemoveItem( Store store , Item item );

/* if item exist in store return item to buyer, return NULL if out of memory */
Item storeSellItem( Store store , Item item );

/* sort store items by type and for each type by value */
StoreResult storeSort( Store store );

/* print to output store stack one of each item and it's quantity */
void storePrintStock( Store store , FILE* output );

/* return true if item exist in store, false else*/
bool storeDoesItemExist(  Store store , Item item );

#endif /* STORE_H_ */
