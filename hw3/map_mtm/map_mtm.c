
/**************************************
 *       Header files include         *
 **************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "map_mtm.h"

/**************************************
 *              Structs               *
 **************************************/


typedef struct node_t {
    MapKeyElement key;
    MapDataElement data;
    struct node_t* next;
}*Node;

struct Map_t {
    Node head;
    Node next;
    Node iterator;
    copyMapKeyElements copyMapKey;
    copyMapDataElements copyData;
    freeMapKeyElements freeKeyElement;
    freeMapDataElements freeDataElement;
    compareMapKeyElements compareKeyElements;
};

/**************************************
 *              Defines               *
 **************************************/

#define ILLEGAL_MAP -1
#define EMPTY_MAP 0
#define ELEMENTS_EQUAL 0
#define MAP_INTERNAL_FOREACH( type , current_key , map )                       \
                                    for ( type current_key = mapGetFirst(map); \
                                    current_key;                               \
                                    current_key = mapGetNext(map) )
#define RELEASE_NODE( node , map ) {                                           \
    nodeDestroy( node , map );                                                 \
    return NULL;                                                               \
}
/**************************************
 *         Static Functions           *
 **************************************/

static Node nodeCreate( MapKeyElement keyElement , MapDataElement dataElement ,
                        Map map ){
    if ( (!keyElement) || (!dataElement) ) return NULL;
    Node new_node = malloc( sizeof(*new_node) );
    if ( !new_node ) return NULL;

    new_node->data = map->copyData( dataElement );
    if ( !new_node->data ) RELEASE_NODE( new_node , map );
    new_node->key = map->copyMapKey( keyElement );
    if ( !new_node->key ) RELEASE_NODE( new_node , map );
    new_node->next = NULL;

    return new_node;
}

static void nodeDestroy( Node node , Map map ) {
    if ( node ) {
        map->freeDataElement( node->data);
        map->freeKeyElement( node->key);
        free ( node );
    }
}

static void removeNodeFromMap( Map map , Node node ) {
    assert( map && node );
    Node previous = mapGetFirst( map );
    Node after = node->next;
    if ( map->compareKeyElements(previous->key , node->key) == ELEMENTS_EQUAL ) {
        nodeDestroy(previous, map); //TODO: check if destroy the real one
        map->head = NULL;
    }
    while( map->compareKeyElements(node->key,previous->next->key) !=
                                                            ELEMENTS_EQUAL) {
        previous = mapGetNext( map );
    }
    nodeDestroy( node , map );
    previous->next = after;
}

static Node nodeGetLast( Map map ) {
    if ( !map )  return NULL;
    Node node = map->head;
    if ( !node ) return NULL;
    mapGetFirst( map ); // TODO: check if not a leak
    while ( node->next ) {
        node = mapGetNext( map );
    }
    return node;
}
/**************************************
 *        Interface Functions         *
 **************************************/

Map mapCreate( copyMapKeyElements copyKeyElement ,
              copyMapDataElements copyDataElement ,
              freeMapKeyElements freeKeyElement ,
              freeMapDataElements freeDataElement ,
              compareMapKeyElements compareKeyElements ) {
    if ( (!copyKeyElement) || (!copyDataElement) || (!freeKeyElement)
        || (!freeDataElement) || (!compareKeyElements) )
        return NULL;

    Map new_map = malloc( sizeof(*new_map) );

    if ( new_map == NULL )
        return NULL;

    new_map->head = NULL;
    new_map->next = NULL;
    new_map->iterator = NULL;
    new_map->copyMapKey = copyKeyElement;
    new_map->copyData = copyDataElement;
    new_map->freeKeyElement = freeKeyElement;
    new_map->freeDataElement = freeDataElement;
    new_map->compareKeyElements = compareKeyElements;

    return new_map;
}

void mapDestroy( Map map ) {
    if (map != NULL) {
        mapClear(map);
        free(map);
    }
}


Map mapCopy( Map map ) {

}


int mapGetSize( Map map ) {
    if ( map == NULL ) return ILLEGAL_MAP;
    if ( map->head == NULL ) return EMPTY_MAP;
    unsigned int  counter = 0;
    MAP_INTERNAL_FOREACH( Node , current_key , map ) {
        counter++;
    }
    return counter;
}


bool mapContains(Map map, MapKeyElement element);


MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if ( (!map) || (!keyElement) || (!dataElement) ) return MAP_NULL_ARGUMENT;

    MAP_INTERNAL_FOREACH( Node , current_key ,  map ) {
        int result = map->compareKeyElements( keyElement , current_key );
        if ( result == ELEMENTS_EQUAL ) {
            map->freeDataElement( current_key->data );
            current_key->data = map->copyData( dataElement );
            if ( current_key->data == NULL ) return MAP_OUT_OF_MEMORY;
            return MAP_SUCCESS;
        }
    }

    Node new_node = nodeCreate( keyElement , dataElement , map );
    if ( new_node == NULL ) return MAP_OUT_OF_MEMORY;
    Node last_node = nodeGetLast( map ); //TODO: write func
    if ( last_node == NULL ) map->head = new_node;
    last_node->next = new_node;
    return MAP_SUCCESS;
}


MapDataElement mapGet(Map map, MapKeyElement keyElement);


MapResult mapRemove(Map map, MapKeyElement keyElement) {
    if ( (!map) || (!keyElement) ) return MAP_NULL_ARGUMENT;
    MAP_INTERNAL_FOREACH( Node , current_key ,  map ) {
        int result = map->compareKeyElements(keyElement, current_key);
        if (result == ELEMENTS_EQUAL) {
            removeNodeFromMap( map , current_key );
            return MAP_SUCCESS;
        }
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}


MapKeyElement mapGetFirst( Map map ) {
    if ( !map ) return NULL;
    if ( !map->head ) {
        map->iterator = NULL;
        return NULL;
    }
    map->iterator = map->head;
    return map->head->key;
}


MapKeyElement mapGetNext( Map map ) { //TODO: "mapGetNext: Advances the map iterator to the next key element and returns it."
    if ( !map ) return NULL;
    if ( !map->iterator ) return NULL;
    if ( !map->iterator->next ) return NULL;
    map->iterator = map->iterator->next->key;
}


MapResult mapClear( Map map ) {
    if ( map == NULL ) return MAP_NULL_ARGUMENT;

    MAP_INTERNAL_FOREACH( Node , current_node , map ) {
        removeNodeFromMap( map , current_node );
    }
        return MAP_SUCCESS;
}

