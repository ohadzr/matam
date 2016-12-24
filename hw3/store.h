
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
/
#endif /* STORE_H_ */
