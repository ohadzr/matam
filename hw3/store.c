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
#include "print_utils.h"

/**************************************
 *              Defines               *
 **************************************/

#define ITEM_1_BIGGER 1
#define EQUAL 0
#define ITEM_2_BIGGER -1
#define EMPTY 0
#define DOUBLE_PRICE 2
#define NO_PRICE 0

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

/* convert string to type return -1 if string NULL */
ItemType static stringToType( char* string ) {
	if (strcmp ( string , "candy" ) == EQUAL )
		return  TYPE_CANDY;
	return  TYPE_POTION;
}

/* return true if value > 0 */
int static positiveCheck( int value ) {
	return (value > 0);
}

/* check if type exists - return true if so */
bool static isValidType( char* type ) {
	if (!strcmp(type,"potion")) return true;
	if (!strcmp(type,"candy")) return true;
	return false;
}

/* convert items type name to string return NULL if item NULL */
char static*  convertTypeToString( Item item ) {
	if ( item ) {
		ItemType type = itemGetType(item);
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

Item itemCreate( int value, char* type ) {
	if( !itemIsValidArgs( value, type ) ) return NULL;
	Item new_item = malloc( sizeof(*new_item) );
	if( !new_item )  return NULL;

	new_item->type = stringToType( type );
	new_item->value = value;
	return new_item;
}

void itemDestroy( Item item ) {
	free (item);
}

Item itemCopy( Item item ) {
	if ( !item ) return NULL;
	return itemCreate( item->value,convertTypeToString(item) );
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
	if (itemGetType(item) == TYPE_CANDY)
		return itemGetValue(item) * DOUBLE_PRICE;
	if (itemGetType(item) == TYPE_POTION)
		return itemGetValue(item);
	return NO_PRICE;
}

int itemCompare( Item item1 , Item item2 ) {
	assert( item1 && item2 );
	if( itemGetType( item1 ) >  itemGetType( item2 ) ) return ITEM_1_BIGGER;
	if( itemGetType( item1 ) <  itemGetType( item2 ) ) return ITEM_2_BIGGER;
	if( itemGetValue( item1 ) >  itemGetValue( item2 ) ) return ITEM_1_BIGGER;
	if( itemGetValue( item1 ) <  itemGetValue( item2 ) ) return ITEM_2_BIGGER;
	return EQUAL;
}

bool itemIsValidArgs( int value, char* type ) {
	if ( (!type) || (!positiveCheck(value)) ) return false;
	if ( !isValidType(type) ) return false;
	return true;
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
		if ( itemCompare( current_item , item ) ==  EQUAL ){
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

bool storeDoesItemExist(  Store store , Item item ) {
	assert ( item && store );
	LIST_FOREACH( Item , current_item , store ) {
		if ( itemCompare( current_item , item ) ==  EQUAL ){
			return true;
		}
	}
	return false;
}

StoreResult storeSort( Store store ) {
	ListResult result = listSort( store , itemCompareElement );
	if ( result == LIST_NULL_ARGUMENT ) return STORE_NULL_ARGUMENT;
	if ( result == LIST_OUT_OF_MEMORY ) return STORE_OUT_OF_MEMORY;
	return STORE_SUCCESS;
}

void storePrintStock( Store store , FILE* output_channel ) {
	assert( store && output_channel );
	mtmPrintStockHeader( output_channel );
	if( listGetSize( store ) != EMPTY ) {
		storeSort( store );
		Item item = listGetFirst(store);
		int counter = 0;
		LIST_FOREACH( Item , current_item , store ) {
			if ( itemCompare( item , current_item ) != EQUAL ) {
				mtmPrintItem(output_channel , convertTypeToString(item),
							 itemGetValue(item) , counter);
				counter = 0;
			}
			counter++;
			item = current_item;
		}
		mtmPrintItem(output_channel , convertTypeToString(item),
									 itemGetValue(item) , counter);
	}
}


