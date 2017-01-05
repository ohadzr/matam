
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

typedef void* Object;

/**************************************
 *              Structs               *
 **************************************/
struct Map_t {
    Object object;
    Object next_object;
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
              compareMapKeyElements compareKeyElements);

void mapDestroy(Map map);


Map mapCopy(Map map);


int mapGetSize(Map map);


bool mapContains(Map map, MapKeyElement element);


MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement);


MapDataElement mapGet(Map map, MapKeyElement keyElement);


MapResult mapRemove(Map map, MapKeyElement keyElement);


MapKeyElement mapGetFirst(Map map);


MapKeyElement mapGetNext(Map map);


MapResult mapClear(Map map);








