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
#define STORE_FOREACH(type, iterator, list) LIST_FOREACH(type, iterator, list)


typedef ItemElement (*CopyFunction)(ItemElement);
typedef void (*FreeFunction)(ItemElement);
typedef int(*CompareFunction)(ItemElement, ItemElement);

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

int itemCompareElement( ItemElement item1 , ItemElement item2 ) {
	retrun itemCompare(  (Item)item1 , (Item)item2 );
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
    if ( !item ) return STORE_NULL_ARGUMENT;
    ListResult add_result = listInsertLast( store , item );
    if ( add_result == LIST_NULL_ARGUMENT ) return STORE_NULL_ARGUMENT;
    if ( add_result == LIST_OUT_OF_MEMORY ) return STORE_OUT_OF_MEMORY;
    return STORE_SUCCESS;
}

StoreResult storeRemoveItem( Store store , Item item ) {
    if ( !item || !store ) return STORE_NULL_ARGUMENT;
    LIST_FOREACH( Item , current_item , store ) {
        if ( itemCompare( current_item , item ) ==  ITEMS_EQUAL ){
            listRemoveCurrent( store );
            return STORE_SUCCESS;
        }
    }
    return STORE_ITEM_NOT_EXIST;
}

Item storeSellItem( Store store , Item item ) {
    assert( item && store );
    StoreResult result = storeRemoveItem( store , item );
    if ( result == STORE_SUCCESS ) return itemCopy( item );
    return NULL;
}

StoreResult storeSort( Store store ) {
	ListResult result = listSort( store , itemCompareElement );
	if ( result == LIST_NULL_ARGUMENT ) return STORE_NULL_ARGUMENT;
	if ( result == LIST_OUT_OF_MEMORY ) return STORE_OUT_OF_MEMORY;
	retrun STORE_SUCCESS;
}

void storePrintStock( Store store , FILE* output) {

}




