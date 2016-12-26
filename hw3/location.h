
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
#include "print_utils.h"
#include "pokemon.h"
#include "utilities.h"


/**************************************
 *              Defines               *
 **************************************/

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

NearLocation nearLocationCreate(char* location_name);

void nearLocationDestroy(char* location_name);

NearLocation nearLocationCopy( char* location_name_to_copy );

int nearLocationCompare( NearLocation location1 , NearLocation location2 );

/**************************************
*         LOCATION Functions         *
**************************************/

Location locationCreate( char* location_name );

void locationDestroy( Location location );

Location locationCopy( Location location );

int locationCompare( Location location1 , Location location2 );

LocationResult locationAddPokemon( Location location , Pokemon pokemon );

LocationResult locationRemovePokemon( Location location , Pokemon pokemon );

LocationResult locationAddNearLocation( Location location ,
                                        NearLocation near_location );

bool locationIsNearDestination( Location location , char* destination );

Pokemon locationGetPokemonInLocation( Location location );

/**************************************
*        WORLD_MAP Functions         *
**************************************/

WorldMap worldMapCreate();

void worldMapDestroy( WorldMap world_map );

WorldMapResult worldMapAddLocation( WorldMap world_map , Location location );

WorldMapResult worldMapRemoveLocation( WorldMap world_map , Location location );

int worldMapGetSize( WorldMap world_map );

WorldMapResult worldMapSort( WorldMap world_map );

void worldMapPrintReport( WorldMap world_map , FILE* output_channel);

#endif /* LOCATION_H_ */
