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
#define MAX_TYPE_NUMBER 2
#define ITEM_1_BIGGER 1
#define ITEMS_EQUAL 0
#define ITEM_2_BIGGER -1
#define EMPTY 0

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

/* convert items type name to string return NULL if item NULL */
char static*  convertTypeToString( Item item ) {
    if ( item ) {
        ItemType type = itemGetType(item);
        assert(isValidType(type));
        switch (type) {
            case TYPE_POTION: return "potion";
            case TYPE_CANDY: return "candy";
        }
    }
    return NULL;
}

/**************************************
 *       Wrapper Item Functions       *
 **************************************/

/* wrapper function to itemCopy so it will be possible to work with List GDT */
ItemElement static itemCopyElement( ItemElement item ) {
    return itemCopy( (Item)item );
}

/*wrapper function to itemDestroy so it will be possible to work with List GDT*/
void static itemFreeElement( ItemElement item ) {
    itemDestroy( (Item)item );
}

/*wrapper function to itemCompare so it will be possible to work with List GDT*/
int static itemCompareElement( ItemElement item1 , ItemElement item2 ) {
    return itemCompare(  (Item)item1 , (Item)item2 );
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
	return STORE_SUCCESS;
}

void storePrintStock( Store store , FILE* output ) {
	assert( store && output );
	if( listGetSize( store ) != EMPTY ) {
		Item item_index = (Item) listGetFirst(store);
		int counter = 0;
		LIST_FOREACH(Item, current_item, store) {
			if (itemCompare(item_index, current_item) != ITEMS_EQUAL) {
				item_index = (Item) listGetCurrent(store);
				mtmPrintItem( output , convertTypeToString( current_item ),
							 itemGetValue(current_item) , counter );
				counter = 0;
			}
			counter++;
		}
	}
}

bool storeDoesItemExist(  Store store , Item item ) {
    assert ( item && store );
    LIST_FOREACH( Item , current_item , store ) {
        if ( itemCompare( current_item , item ) ==  ITEMS_EQUAL ){
            return true;
        }
    }
    return false;
}