
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
#define EMPTY_STRING 0
typedef struct location_t* Location;
typedef List WorldMap;
typedef void* LocationElement;
typedef void* NearLocationElement;
typedef char* NearLocation;

/**************************************
 *         Enum declarations          *
 **************************************/

typedef enum {LOCATION_SUCCESS,
    LOCATION_NULL_ARGUMENT,
    LOCATION_NOT_EXIST,
    LOCATION_POKEMON_NOT_EXIST,
    LOCATION_OUT_OF_MEMORY} LocationResult;

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
 * LOCATION_NULL_ARGUMENT: if location or near_location equal NULL ;
 * LOCATION_OUT_OF_MEMORY: if memory allocation failed ;
 * LOCATION_SUCCESS: if near_location was added successfully; */
LocationResult locationAddNearLocation( Location location ,
                                        NearLocation near_location );

/* if destination is a NearLocation to location then return true, false else.
 * to be used only by legal parameters */
bool locationIsNearDestination( Location location , char* destination );

/* retrieve the available pokemon that can be hunted in location. return NULL if
 * location out of pokemons - to be used only by legal parameters */
Pokemon locationGetPokemonInLocation( Location location );

/**************************************
*        WORLD_MAP Functions         *
**************************************/

/* */
WorldMap worldMapCreate();

void worldMapDestroy( WorldMap world_map );

WorldMapResult worldMapAddLocation( WorldMap world_map , Location location );

WorldMapResult worldMapRemoveLocation( WorldMap world_map , Location location );

int worldMapGetSize( WorldMap world_map );

Location worldMapGetLocation( WorldMap world_map , char* loation_name );

WorldMapResult worldMapSort( WorldMap world_map );

void worldMapPrintReport( WorldMap world_map , FILE* output_channel);

#endif /* LOCATION_H_ */
