/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "store.h"
#include "list.h"

/**************************************
 *              Defines               *
 **************************************/
#define MAX_TYPE_NUMBER 2
#define ITEM_1_BIGGER 1
#define ITEMS_EQUAL 0
#define ITEM_2_BIGGER -1

typedef void* ItemElement;
typedef ItemElement (*CopyFunction)(ItemElement);
typedef void (*FreeFunction)(ItemElement);
typedef LIST_FOREACH  STORE_FOREACH

/**************************************
 *              Structs               *
 **************************************/

struct item_t {
	ItemType type;
	int value;
};

/**************************************
 *         Static Functions           *
 **************************************/

/* return true if value > 0 */
int static positiveCheck( int value ) {
	return (value > 0);
}

/* check if type exists - return true if so */
bool static isValidType( ItemType type ) {
	for ( int i = 0 ; i < MAX_TYPE_NUMBER ; i++ ) {
		if ( type == i ) return true;
	}
	return false;
}

/**************************************
 *        Interface Functions         *
 **************************************/

/**************************************
 *           ITEM Functions           *
 **************************************/

Item itemCreate( int value,ItemType type ) {
	if( ( !isValidType(type) ) || ( !positiveCheck(value) ) ) return NULL;
	Item new_item = malloc( sizeof(*new_item) );
	if( !new_item )  return NULL;
	new_item->type = type;
	new_item->value = value;
	return new_item;
}

void itemDestroy( Item item ) {
	free (item);
}

Item itemCopy( Item item ) {
	if ( !item ) return NULL;
	return itemCreate(item->value,item->type);
}

int itemGetValue( Item item ) {
	assert(item);
	return item->value;
}

ItemType itemGetType( Item item ) {
	assert(item);
	return item->type;
}

int itemGetPrice( Item item ) {
	assert( item );
	return ( itemGetValue(item) * ( itemGetType(item) + 1 ) );
}

int itemCompare( Item item1 , Item item2 ) {
	assert( item1 && item2 );
	if( itemGetType( item1 ) >  itemGetType( item2 ) ) return ITEM_1_BIGGER;
	if( itemGetType( item1 ) <  itemGetType( item2 ) ) return ITEM_2_BIGGER;
	if( itemGetValue( item1 ) >  itemGetValue( item2 ) ) return ITEM_1_BIGGER;
	if( itemGetValue( item1 ) <  itemGetValue( item2 ) ) return ITEM_2_BIGGER;
	return ITEMS_EQUAL;
}

/**************************************
 *       Wrapper Item Functions       *
 **************************************/

ItemElement itemCopyElement( ItemElement item ) {
	return itemCopy( (Item)item );
}

void itemFreeElement( ItemElement item ) {
	itemDestroy( (Item)item );
}

/**************************************
 *           STORE Functions          *
 **************************************/

Store storeCreate() {
	return listCreate( itemCopyElement , itemFreeElement );
}

void storeDestroy( Store store ) {
	listDestroy( store );
}

Store storeCopy( Store store ) {
	return listCopy( store );
}

StoreResult storeAddItem ( Store store , Item item ) {
	listInsertLast( store , item );

}
















