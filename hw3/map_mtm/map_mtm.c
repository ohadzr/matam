
/**************************************
 *       Header files include         *
 **************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "map_mtm.h"

/**************************************
 *              Defines               *
 **************************************/

#define MAP_INTERNAL_FOREACH(node, map)    \
                                    for ( Node node=mapGetFirst(map); \
                                    node; \
                                    node = mapGetNext(map) )

/**************************************
 *              Structs               *
 **************************************/
typedef struct Node_t Node;

struct Node_t {
    MapKeyElement key;
    MapDataElement data;
    Node next;
};

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
 *         Static Functions           *
 **************************************/


/**************************************
 *        Interface Functions         *
 **************************************/

Map mapCreate(copyMapKeyElements copyKeyElement,
              copyMapDataElements copyDataElement,
              freeMapKeyElements freeKeyElement,
              freeMapDataElements freeDataElement,
              compareMapKeyElements compareKeyElements) {
    if (!copyKeyElement || !copyDataElement || !freeKeyElement
        || !freeDataElement || !compareKeyElements)
        return NULL;

    Map new_map = malloc(sizeof(*new_map));

    if (new_map == NULL)
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

void mapDestroy(Map map) {
    if (map != NULL) {
        mapClear(map);
        free(map);
    }
}


Map mapCopy(Map map) {

}


int mapGetSize(Map map);


bool mapContains(Map map, MapKeyElement element);


MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement);


MapDataElement mapGet(Map map, MapKeyElement keyElement);


MapResult mapRemove(Map map, MapKeyElement keyElement);


MapKeyElement mapGetFirst(Map map);


MapKeyElement mapGetNext(Map map);


MapResult mapClear(Map map) {
    if (map == NULL) return MAP_NULL_ARGUMENT;

}

