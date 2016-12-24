
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

Item itemCreate( int value,ItemType type );

void itemDestroy( Item item );

Item itemCopy( Item item );

int itemGetValue( Item item );

ItemType itemGetType( Item item );

int itemGetPrice( Item item );

int itemCompare( Item item1 , Item item2 );

Store storeCreate();

void storeDestroy( Store store );

Store storeCopy( Store store );

StoreResult storeAddItem ( Store store , Item item );

StoreResult storeRemoveItem( Store store , Item item );

Item storeSellItem( Store store , Item item );

StoreResult storeSort( Store store );

void storePrintStock( Store store , FILE* output )

#endif /* STORE_H_ */
