
#ifndef STORE_H_
#define STORE_H_

/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define STORE_FOREACH(type,iterator,list)                                      \
	for(type iterator = listGetFirst(list) ;                                   \
		iterator ;                                                             \
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
	STORE_OUT_OF_MEMORY} StoreResult;

/**************************************
 *      Functions declarations        *
 **************************************/

/** function create a new Item.
 *
 * @return
 * new item or NULL if type invalid or value isn't positive or not enough memory
 */
Item itemCreate( int value, char* type );

/** function destroy given Item.
 * if item NULL do nothing, else free all memory allocated to item
 */
void itemDestroy( Item item );

/** function copy item.
 *
 * @return
 * if item not NULL and enough memory return copy of item, else return NULL.
 */
Item itemCopy( Item item );

/** function asserts item not NULL.
 *
 * @return
 * item's value
 */
int itemGetValue( Item item );

/** function asserts item not NULL.
 *
 * @return
 * item's type
 */
ItemType itemGetType( Item item );

/** function asserts item not NULL.
 * calculate item's price according to it's type.
 *
 * @return
 * item's price - (item's value)*(type bonus).
 */
int itemGetPrice( Item item );

/** function check if arguments to create Item valid.
 *
 * @return
 * true if arguments valid, false else
 */
bool itemIsValidArgs( int value, char* type );

/** function create new store.
 *
 * @return
 * new store with no items in it, return NULL if not enough memory
 */
Store storeCreate();

/** function destroy given store.
 * if store is NULL do nothing, else free all memory allocated to store
 */
void storeDestroy( Store store );

/** function copy store.
 *
 * @return
 * copy of store, NULL if given store is NULL or not enough memory
 */
Store storeCopy( Store store );

/** function add new item to store.
 *
 * @return
 * STORE_NULL_ARGUMENT - if item/store were NULL
 * STORE_OUT_OF_MEMORY - if an allocation failed
 * STORE_SUCCESS - the item has been inserted successfully
 */
StoreResult storeAddItem ( Store store , Item item );

/** function remove all memory of item from store.
 *
 * @return
 * STORE_NULL_ARGUMENT - if store or item is NULL
 * STORE_ITEM_NOT_EXIST - if item was not in store
 * STORE_SUCCESS - if item was removed successfully */
StoreResult storeRemoveItem( Store store , Item item );

/** function sell item to trainer.
 *
 * @return
 * if item exist in store return item, else return NULL if out of memory or
 * store or item is NULL.
 */
Item storeSellItem( Store store , Item item );

/** function check if item exist in store.
 *
 * @return
 * true if item exist in store, false else*/
bool storeDoesItemExist(  Store store , Item item );

/** function sort store items by type and for each type by value.
 *
 * @return
 * STORE_NULL_ARGUMENT - if store or item is NULL
 * STORE_OUT_OF_MEMORY - if an allocation failed
 * STORE_SUCCESS - the item has been sorted successfully
 */
StoreResult storeSort( Store store );

/* function print to output store stack one of each item and it's quantity */
void storePrintStock( Store store , FILE* output );

#endif /* STORE_H_ */
