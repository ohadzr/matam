
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
    Node iterator;
    copyMapKeyElements copyMapKey;
    copyMapDataElements copyData;
    freeMapKeyElements freeKeyElement;
    freeMapDataElements freeDataElement;
    compareMapKeyElements compareKeyElements;
};

/**************************************
 *        Static declarations         *
 **************************************/

/**
 * function create a new Node.
 * @param keyElement - points to the key that will be stored in the new node.
 * @param dataElement - points to the suitable data fitting to the the key.
 * @param map - contains the copy and free functions suitable to key and data.
 * @return
 * NULL- if one or more of the arguments is NULL, or if memory allocation failed
 * else return a new Node.
 */
static Node nodeCreate( MapKeyElement keyElement , MapDataElement dataElement ,
                 Map map );

/**
 * function free all memory allocated to Node.
 * @param node - the Node to be destroyed.
 * @param map - contains the free functions to destroy data and key stored in.
 */
static void nodeDestroy( Node node , Map map );

/**
 * function copies a Node.
 * @param node - the Node to by copyed.
 * @param map - contains the free functions to destroy data and key stored in.
 * @return
 * NULL - if one or more of the arguments is NULL or if memory allocation failed
 * else returns a copy of the exepted node.
 */
static Node nodeCopy( Node node , Map map );

/**
 * function removes node from map if node exists, do noting else.
 * @param map - the  map that contains the node to be removed.
 * @param node - the node to be removed.
 */
static void removeNodeFromMap( Map map , Node node );

/**
 * function locates the previous node to the the nodewe want to add to the map.
 * @param new_node - the new node to add to map.
 * @param map - the map to add node to.
 * @return
 * NULL - if one of the parameters is NULL or if map has no Nodes.
 * else return the Node previous to be linked to map.
 */
static Node findPreviousToNewNode( Node new_node, Map map);


/**************************************
 *              Defines               *
 **************************************/

#define ILLEGAL_MAP -1
#define EMPTY_MAP 0
#define ELEMENTS_EQUAL 0
#define RIGHT_ELEMENT_FIRST 1
#define LEFT_ELEMEMT_FIRST -1
#define MAP_INTERNAL_FOREACH( type , current_node , map )                      \
                                    for ( type current_node = map->head;       \
                                    current_node;                              \
                                    current_node = current_node->next )
#define RELEASE_NODE( node , map ) {                                           \
    nodeDestroy( node , map );                                                 \
    return NULL;                                                               \
}
#define RELEASE_MAP( map ) {                                                   \
    mapDestroy( map );                                                         \
    return NULL;                                                               \
}

/**************************************
 *         Static Functions           *
 **************************************/

Node nodeCreate( MapKeyElement keyElement , MapDataElement dataElement ,
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

void nodeDestroy( Node node , Map map ) {
    if ( node ) {
        map->freeDataElement( node->data);
        map->freeKeyElement( node->key);
        free ( node );
    }
}

Node nodeCopy( Node node , Map map ) {
    if ( !node ) return NULL;
    return nodeCreate( node->key , node->data , map );
}

void removeNodeFromMap( Map map , Node node ) {
    assert( map && node );
    Node previous = map->head;
    Node after = node->next;
    if ( map->compareKeyElements(previous->key , node->key) == ELEMENTS_EQUAL ){
        nodeDestroy(previous, map);
        map->head = after;
        return;
    }
    while( map->compareKeyElements(node->key,previous->next->key) !=
                                                            ELEMENTS_EQUAL) {
        if ( !previous->next ) break;
        previous = previous->next;
    }
    nodeDestroy( node , map );
    previous->next = after;
}

Node findPreviousToNewNode ( Node node, Map map ) {
    if (!map || !node) return NULL;
    if ( !map->head ) return NULL;

    MAP_INTERNAL_FOREACH( Node , current_node ,  map )  {
        int result = map->compareKeyElements( node->key , current_node->key );
        if ( result != RIGHT_ELEMENT_FIRST ) return NULL;
        if ( !current_node->next ) return current_node;
        else {
            result = map->compareKeyElements(node->key,current_node->next->key);
            if (result == LEFT_ELEMEMT_FIRST) {
                return current_node;
            }
        }
    }

    return NULL;
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
    new_map->iterator = NULL;
    new_map->copyMapKey = copyKeyElement;
    new_map->copyData = copyDataElement;
    new_map->freeKeyElement = freeKeyElement;
    new_map->freeDataElement = freeDataElement;
    new_map->compareKeyElements = compareKeyElements;

    return new_map;
}

void mapDestroy( Map map ) {
    if ( map != NULL ) {
        mapClear( map );
        free( map );
    }
}


Map mapCopy( Map map ) {
    if ( !map ) return NULL;
    Map copy_map = mapCreate( map->copyMapKey , map->copyData ,
                              map->freeKeyElement , map->freeDataElement ,
                              map->compareKeyElements );

    if ( !copy_map ) return NULL;

    if ( !map->head ) return copy_map;
    copy_map->head = nodeCopy( map->head , map );
    if ( !copy_map->head ) RELEASE_MAP( copy_map );

    Node temp = copy_map->head;

    MAP_INTERNAL_FOREACH( Node , current_node , map ) {
        // Skip first node (already copied)
        if (map->compareKeyElements(current_node->key, temp->key) ==
            ELEMENTS_EQUAL)
            continue;

        temp->next = nodeCopy( current_node , map );
        if ( !temp->next ) RELEASE_MAP( copy_map );
        temp = temp->next;
    }

    return copy_map;
}


int mapGetSize( Map map ) {
    if ( map == NULL ) return ILLEGAL_MAP;
    if ( map->head == NULL ) return EMPTY_MAP;
    int  counter = 0;
    MAP_INTERNAL_FOREACH( Node , current_node , map ) {
        counter++;
    }
    return counter;
}


bool mapContains( Map map , MapKeyElement element ) {
    if ( (!map) || (!element) ) return false;
    MAP_INTERNAL_FOREACH( Node , current_node ,  map ) {
        int result = map->compareKeyElements(element, current_node->key);
        if (result == ELEMENTS_EQUAL) return true;
    }
    return false;
}


MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if ( (!map) || (!keyElement) || (!dataElement) ) {
        return MAP_NULL_ARGUMENT;
    }

    Node new_node = nodeCreate(keyElement, dataElement, map);
    if (!new_node) return MAP_OUT_OF_MEMORY;
    if (!map->head) {
        map->head = new_node;
        return MAP_SUCCESS;
    }
    //Update if key exists
    MAP_INTERNAL_FOREACH( Node , current_node ,  map ) {
        int result = map->compareKeyElements( keyElement , current_node->key );
        if ( result == ELEMENTS_EQUAL ) {
            map->freeDataElement( current_node->data );
            current_node->data = map->copyData( dataElement );
            if ( current_node->data == NULL ) return MAP_OUT_OF_MEMORY;
            nodeDestroy(new_node, map);
            return MAP_SUCCESS;
        }
    }

    Node previous = findPreviousToNewNode(new_node, map);
    if ( !previous ) {
        new_node->next = map->head;
        map->head = new_node;
        return MAP_SUCCESS;
    }
    new_node->next = previous->next;
    previous->next = new_node;
    return MAP_SUCCESS;
}


MapDataElement mapGet( Map map , MapKeyElement keyElement ) {
    if ( (!map) || (!keyElement) ) return NULL;
    Node temp = map->iterator;
    MAP_INTERNAL_FOREACH( Node , current_node ,  map ) {
        int result = map->compareKeyElements( keyElement , current_node->key);
        if (result == ELEMENTS_EQUAL) return current_node->data;
    }
    map->iterator = temp;
    return NULL;
}


MapResult mapRemove(Map map, MapKeyElement keyElement) {
    if ( (!map) || (!keyElement) ) return MAP_NULL_ARGUMENT;
    MAP_INTERNAL_FOREACH( Node , current_node ,  map ) {
        int result = map->compareKeyElements( keyElement , current_node->key );
        if (result == ELEMENTS_EQUAL) {
            removeNodeFromMap( map , current_node );
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


MapKeyElement mapGetNext( Map map ) {
    if ( !map ) return NULL;
    if ( !map->iterator ) return NULL;
    if ( !map->iterator->next ) return NULL;
    map->iterator = map->iterator->next;
    return map->iterator->key;
}


MapResult mapClear( Map map ) {
    if ( !map ) return MAP_NULL_ARGUMENT;

    MAP_INTERNAL_FOREACH( Node , current_node , map ) {
        removeNodeFromMap( map , current_node );
    }


    return MAP_SUCCESS;
}

