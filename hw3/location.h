
#ifndef LOCATION_H_
#define LOCATION_H_

/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "pokemon.h"

/**************************************
 *              Defines               *
 **************************************/

typedef List WorldMap;
typedef void* LocationElement;
typedef void* NearLocationElement;
typedef char* NearLocation;
#define EMPTY_STRING 0
typedef struct location_t* Location;

/**************************************
 *         Enum declarations          *
 **************************************/

typedef enum {LOCATION_SUCCESS,
    LOCATION_NULL_ARGUMENT,
    LOCATION_POKEMON_NOT_EXIST,
    LOCATION_NEAR_LOCATION_NOT_EXIST,
    LOCATION_OUT_OF_MEMORY,
    LOCATION_ALREADY_IN_LOCATION} LocationResult;

typedef enum {WORLD_MAP_SUCCESS,
    WORLD_MAP_NULL_ARGUMENT,
    WORLD_MAP_LOCATION_NOT_EXIST,
    WORLD_MAP_LOCATION_ALREADY_EXISTS,
    WORLD_MAP_OUT_OF_MEMORY} WorldMapResult;

/**************************************
 *      Functions declarations        *
 **************************************/

/**************************************
*      NEAR_LOCATION Functions       *
**************************************/

/* if location_name valid (=> not NULL and not an empty string) and provided
* that memory allocation succeeded - return new nearLocation to be added to
* Location as a reachable location, return NULL otherwise */
NearLocation nearLocationCreate(char* location_name);

/* destroy nearLocation and free memory allocations, if near_location == NULL
 *  do nothing */
void nearLocationDestroy(NearLocation near_location);

/* if location_name valid (=> not NULL and not an empty string) and provided
* that memory allocation succeeded - return copy of nearLocation -
* location_to_copy return NULL otherwise */
NearLocation nearLocationCopy( NearLocation location_to_copy );

/* compare 2 nearLocations - if equal - return 0 , if the first bigger return 1
 *  and if the second bigger return -1. to be used only by legal parameters */
int nearLocationCompare( NearLocation location1 , NearLocation location2 );

/**************************************
*         LOCATION Functions         *
**************************************/

/* if location_name valid (=> not NULL and not an empty string) and provided
* that memory allocation succeeded - return new nearLocation to be added to
* Location as a reachable location, return NULL otherwise */
Location locationCreate( char* location_name );

/*destroy location and free memory allocations, if location == NULL do nothing*/
void locationDestroy( Location location );

/* if location valid (=> not NULL) and provided that memory allocation succeeded
 * return copy of location. return NULL otherwise */
Location locationCopy( Location location );

/* define two locations equal if their names equal. compare two Locations - if
 *  equal - return 0 , if the first bigger return 1 and if the second bigger
 *  return -1. to be used only by legal parameters */
int locationCompare( Location location1 , Location location2 );

/* return location name - to be used only by legal parameters */
char* locationGetName( Location location );

/* add new Pokemon to location.
 * return:
 * LOCATION_NULL_ARGUMENT: if location or pokemon equal NULL ;
 * LOCATION_OUT_OF_MEMORY: if memory allocation failed ;
 * LOCATION_SUCCESS: if pokemon was added successfully; */
LocationResult locationAddPokemon( Location location , Pokemon pokemon );

/* remove Pokemon from location.
 * return:
 * LOCATION_NULL_ARGUMENT: if location or pokemon equal NULL ;
 * LOCATION_POKEMON_NOT_EXIST: if pokemon wasn't in location ;
 * LOCATION_SUCCESS: if pokemon was removed successfully; */
LocationResult locationRemovePokemon( Location location , Pokemon pokemon );

/* add new NearLocation to location.
 * return:
 * LOCATION_ALREADY_IN_LOCATION: if tries to add the location to itself ;
 * LOCATION_NULL_ARGUMENT: if location or near_location equal NULL ;
 * LOCATION_OUT_OF_MEMORY: if memory allocation failed ;
 * LOCATION_SUCCESS: if near_location was added successfully; */
LocationResult locationAddNearLocation( Location location ,
                                        NearLocation near_location );

/* remove NearLocation from location.
 * return:
 * LOCATION_NULL_ARGUMENT: if location or near_location equal NULL ;
 * LOCATION_POKEMON_NOT_EXIST: if near_location wasn't in location ;
 * LOCATION_SUCCESS: if near_location was removed successfully; */
LocationResult locationRemoveNearLocation( Location location ,
                                           NearLocation near_location );

/* if destination is a NearLocation to location then return true, false else.
 * to be used only by legal parameters */
bool locationIsNearDestination( Location location , char* destination );

/**************************************
*        WORLD_MAP Functions         *
**************************************/

/* return new worldMap return NULL if memory allocation failed */
WorldMap worldMapCreate();

/* free all memory allocated to world_map, if world_map is NULL do noting */
void worldMapDestroy( WorldMap world_map );

/* added new Location to map.
 * return:
 * WORLD_MAP_NULL_ARGUMENT:	if world_map or location NULL;
 * WORLD_MAP_LOCATION_ALREADY_EXISTS: if location already exists;
 * WORLD_MAP_OUT_OF_MEMORY: if memory allocation failed ;
 * WORLD_MAP_SUCCESS: if location was added to world map successfully; */
WorldMapResult worldMapAddLocation( WorldMap world_map , Location location );

/* remove location from world_map.
 * return:
 * WORLD_MAP_NULL_ARGUMENT: if location or world_map equal NULL ;
 * WORLD_MAP_LOCATION_NOT_EXIST: if location wasn't in world_map ;
 * WORLD_MAP_SUCCESS: if location was removed successfully; */
WorldMapResult worldMapRemoveLocation( WorldMap world_map , Location location );

/* if location exist in map return true , false otherwise - to be used only by
 *  legal parameters */
bool worldMapDoesLocationExist( WorldMap world_map , char* location );

/* return number of locations in map - to be used only by legal parameters */
int worldMapGetSize( WorldMap world_map );

/* return location with the same name as loation_name from world map.
 * return NULL if world_map or loation_name are NULL or if location by that name
 * does not exist */
Location worldMapGetLocation( WorldMap world_map , char* location_name );

/* retrieve the available pokemon that can be hunted in location. return NULL if
 * location out of pokemons - to be used only by legal parameters */
Pokemon worldMapGetPokemonInLocation( WorldMap world_map,char* location_name );

/* return true if destination_location can be reached by trainer by one step
 * from current_location - if not legal parameters : real location names in map
 *  && parameters not NULL or empty strings or if location isn't in map -
 *  return false)*/
bool worldMapIsLocationReachable( WorldMap world_map , char* current_location ,
                                  char* destination_location);

/* sort world map by lexicographical order.
 * return:
 * WORLD_MAP_NULL_ARGUMENT: if world_map is NULL;
 * WORLD_MAP_OUT_OF_MEMORY: if memory allocation failed;
 * WORLD_MAP_SUCCESS: if world map was sorted successfully;
}*/
WorldMapResult worldMapSort( WorldMap world_map );

/* print world map by lexicographical order and pokemons in each location - to
 *  be used only by legal parameters*/
void worldMapPrintReport( WorldMap world_map , FILE* output_channel);

#endif /* LOCATION_H_ */
