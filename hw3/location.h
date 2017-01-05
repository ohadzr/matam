
#ifndef LOCATION_H_
#define LOCATION_H_

/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"
#include "list.h"
#include "print_utils.h"
#include "pokemon.h"
#include "utilities.h"

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
    LOCATION_OUT_OF_MEMORY,
    LOCATION_ALREADY_EXIST,
    LOCATION_ALREADY_IN_LOCATION} LocationResult;

typedef enum {WORLD_MAP_SUCCESS,
    WORLD_MAP_NULL_ARGUMENT,
    WORLD_MAP_LOCATION_ALREADY_EXISTS,
    WORLD_MAP_OUT_OF_MEMORY} WorldMapResult;

/**************************************
 *      Functions declarations        *
 **************************************/

/**************************************
*      NEAR_LOCATION Functions       *
**************************************/

/* function create new nearLocation.
 *
 * @return
 * if location_name valid (=> not NULL and not an empty string) and provided
 * that memory allocation succeeded - return new nearLocation to be added to
 * Location as a reachable location, return NULL otherwise.
 */
NearLocation nearLocationCreate(char* location_name);

/* function destroy nearLocation and free memory allocations.
 * if near_location == NULL do nothing.
 */
void nearLocationDestroy(NearLocation near_location);

/**************************************
*         LOCATION Functions         *
**************************************/

/** function create new location.
 *
 * @return
 * if location_name valid (=> not NULL and not an empty string) and provided
 * that memory allocation succeeded - return new nearLocation to be added to
 * world map, return NULL otherwise.
 */
Location locationCreate( char* location_name );

/** function destroy location and free memory allocations.
 * if location == NULL do nothing*/
void locationDestroy( Location location );

/** function add new Pokemon to location.
 *
 * @return
 * LOCATION_NULL_ARGUMENT if location or pokemon equal NULL.
 * LOCATION_OUT_OF_MEMORY if memory allocation failed.
 * LOCATION_SUCCESS if pokemon was added successfully.
 */
LocationResult locationAddPokemon( Location location , Pokemon pokemon );

/** function add new NearLocation to location.
 *
 * @return
 * LOCATION_ALREADY_IN_LOCATION if tries to add the location to itself.
 * LOCATION_NULL_ARGUMENT if location or near_location equal NULL.
 * LOCATION_OUT_OF_MEMORY if memory allocation failed.
 * LOCATION_SUCCESS if near_location was added successfully.
 */
LocationResult locationAddNearLocation( Location location ,
                                        NearLocation near_location );

/**************************************
*        WORLD_MAP Functions         *
**************************************/

/** function create new worldMap.
 *
 * @return
 * new worldMap or NULL if memory allocation failed.
 */
WorldMap worldMapCreate();

/** function free all memory allocated to world_map.
 * if world_map is NULL do noting.
 */
void worldMapDestroy( WorldMap world_map );

/** function added new Location to map.
 *
 * @return
 * WORLD_MAP_NULL_ARGUMENT if world_map or location NULL.
 * WORLD_MAP_LOCATION_ALREADY_EXISTS if location already exists.
 * WORLD_MAP_OUT_OF_MEMORY if memory allocation failed.
 * WORLD_MAP_SUCCESS if location was added to world map successfully.
 */
WorldMapResult worldMapAddLocation( WorldMap world_map , Location location );

/** function check if location exist in world map. function
 * return true if location exist in world map.
 * false otherwise.
 */
bool worldMapDoesLocationExist( WorldMap world_map , char* location );

/** function retrieve the available pokemon that can be hunted in location.
 *
 * @return
 * NULL if location out of pokemons or if one of the parameters NULL.
 */
Pokemon worldMapGetPokemonInLocation( WorldMap world_map,char* location_name );

/** function check if destination_location can be reached by trainer by one step
 * from current_location. funation asserts parameters not NULL.
 *
 * @return
 * true if destination_location can be reached by trainer by one step from
 * current_location.
 * false if not legal parameters (not real location names in map or parameters
 * NULL or empty strings or destination_location is not reachable from location.
*/
bool worldMapIsLocationReachable( WorldMap world_map , char* current_location ,
                                  char* destination_location);

/** function sort world map by lexicographical order.
 *
 * @return:
 * WORLD_MAP_NULL_ARGUMENT if world_map is NULL.
 * WORLD_MAP_OUT_OF_MEMORY if memory allocation failed.
 * WORLD_MAP_SUCCESS if world map was sorted successfully.
}*/
WorldMapResult worldMapSort( WorldMap world_map );

/** function print world map by lexicographical order and pokemons in each
 * location. function asserts parameters not NULL.
 */
void worldMapPrintReport( WorldMap world_map , FILE* output_channel);

#endif /* LOCATION_H_ */
