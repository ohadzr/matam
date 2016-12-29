/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "location.h"
#include "set.h"
#include "list.h"
#include "print_utils.h"
#include "pokemon.h"
#include "utilities.h"

/**************************************
 *              Defines               *
 **************************************/

#define LOCATION1_BIGGER 1
#define LOCATIONS_EQAUL 0
#define LOCATION2_BIGGER -1
#define RELEALSE_TREATMENT( parameter , name ) {                                      \
			if ( !(parameter) ) {                                              \
				locationDestroy( name );                                       \
				return NULL;                                                   \
			}                                                                  \
		}

/**************************************
 *              Structs               *
 **************************************/

struct location_t {
    char* name;
    List pokemons;
    Set near_locations;
};

/**************************************
 *         Static Functions           *
 **************************************/

/* compare if 2 names equal - if so return 0 , if the first bigger return 1 and
 *  if the second bigger return -1. - to be used only by legal parameters */
int static locationNameCompare( char* location1 , char* location2 ){
    assert( location1 && location2 );
    int result = strcmp( location1 , location2 );
    if ( result > 0 ) return LOCATION1_BIGGER;
    if ( result < 0 ) return LOCATION2_BIGGER;
    return LOCATIONS_EQAUL;
}

/* if location exist in map return true , false otherwise - to be used only by
 *  legal parameters */
bool static worldMapDoesLocationExist( WorldMap world_map , Location location ){
    assert( world_map && location );
    LIST_FOREACH( Location , current_location , world_map ) {
        if ( locationCompare(location , current_location) == LOCATIONS_EQAUL )
            return true;
    }
    return false;
}

/**************************************
 *          Wrapper Functions         *
 **************************************/

/* wrapper function to nearLocationCopy so it will be possible to work
 *  with set GDT */
ItemElement static nearLocationCopyElement( NearLocationElement near_location ){
    return nearLocationCopy( (NearLocation)near_location );
}

/*wrapper function to nearLocationDestroy so it will be possible to work with
 *  set GDT*/
void static nearLocationFreeElement( NearLocationElement near_location ) {
    nearLocationDestroy( (char*)near_location );
}

/*wrapper function to nearLocationCompare so it will be possible to work with
 *  set GDT*/
int static nearLocationCompareElement( NearLocationElement
                                       near_location1 , NearLocationElement near_location2 ) {
    return nearLocationCompare(  (char*)near_location1 ,
                                 (char*)near_location2 );
}

/*wrapper function to locationCopy so it will be possible to work with
 * list GDT */
LocationElement locationCopyElement( LocationElement location ) {
    return locationCopy( (Location)location );
}

/* wrapper function to locationDestroy so it will be possible to work with
 * list GDT */
void locationDestroyElement( LocationElement location ) {
    locationDestroy( (Location)location );
}

/* wrapper function to locationCompare so it will be possible to work with
 * list GDT */
int locationCompareElement(LocationElement location1,LocationElement location2){
    return locationCompare( (Location)location1 , (Location)location2 );
}

/**************************************
 *        Interface Functions         *
 **************************************/

/**************************************
 *      NEAR_LOCATION Functions       *
 **************************************/

NearLocation nearLocationCreate(char* location_name) {
    if ( !location_name ) return NULL;
    return stringCopy ( location_name );
}

void nearLocationDestroy(NearLocation location_name){
    stringDestroy( location_name );
}

NearLocation nearLocationCopy( NearLocation location_to_copy ){
    return nearLocationCreate ( location_to_copy );
}

int nearLocationCompare( NearLocation location1 , NearLocation location2 ) {
    return locationNameCompare( location1 , location2 );
}

/**************************************
 *         LOCATION Functions         *
 **************************************/

Location locationCreate( char* location_name ) {
    if ( !location_name ) return NULL;
    Location new_location = malloc( sizeof(*new_location) );
    if ( !new_location ) return NULL;
    new_location->name = stringCopy( location_name );
    RELEALSE_TREATMENT( new_location->name , new_location );
    new_location->pokemons = listCreate(pokemonCopyElement,pokemonFreeElement);
    RELEALSE_TREATMENT( new_location->pokemons , new_location );
    new_location->near_locations = setCreate(nearLocationCopyElement ,
                                             nearLocationFreeElement , nearLocationCompareElement );
    RELEALSE_TREATMENT( new_location->near_locations , new_location );
    return new_location;
}

void locationDestroy( Location location ) {
    if ( location ) {
        stringDestroy( location->name );
        listDestroy( location->pokemons );
        setDestroy( location->near_locations );
    }
    free ( location );
}

Location locationCopy( Location location ) {
    if ( !location ) return NULL;
    Location copyed_location = locationCreate( locationGetName( location ) );
    if ( !copyed_location ) return NULL;
    if ( !(location->pokemons) ) copyed_location->pokemons = NULL;
    else {
        copyed_location->pokemons = listCopy( location->pokemons );
        RELEALSE_TREATMENT( copyed_location->pokemons , copyed_location );
    }
    if ( !(location->near_locations) ) copyed_location->near_locations = NULL;
    else {
        copyed_location->near_locations = setCopy(location->near_locations);
        RELEALSE_TREATMENT( copyed_location->near_locations , copyed_location );
    }
    return copyed_location;
}

int locationCompare( Location location1 , Location location2 ) {
    assert ( location1 && location2 );
    return locationNameCompare( location1->name , location2->name );
}

char* locationGetName( Location location ) {
    assert( location );
    return location->name;
}

LocationResult locationAddPokemon( Location location , Pokemon pokemon ){
    if ( (!location) || (!pokemon) ) return LOCATION_NULL_ARGUMENT;
    ListResult result = listInsertLast( location->pokemons , pokemon );
    if ( result == LIST_OUT_OF_MEMORY ) return LOCATION_OUT_OF_MEMORY;
    return LOCATION_SUCCESS;
}

LocationResult locationRemovePokemon( Location location , Pokemon pokemon ){
    if ( (!location) || (!pokemon) ) return LOCATION_NULL_ARGUMENT;
    LIST_FOREACH( Pokemon , current_pokemon , location->pokemons ) {
        if ( pokemonCompareByID( current_pokemon , pokemon ) ==  0 ) {
            listRemoveCurrent( location->pokemons );
            return LOCATION_SUCCESS;
        }
    }
    return LOCATION_POKEMON_NOT_EXIST;
}

LocationResult locationAddNearLocation(  Location location ,
                                         NearLocation near_location ){
    if ( (!location) || (!near_location) ) return LOCATION_NULL_ARGUMENT;
    if ( locationNameCompare( location->name , near_location ) == 0 )
        return LOCATION_ALREADY_IN_LOCATION;
    SetResult result = setAdd(location->near_locations , near_location);
    if ( result == SET_OUT_OF_MEMORY ) return LOCATION_OUT_OF_MEMORY;
    return LOCATION_SUCCESS;
}

LocationResult locationRemoveNearLocation( Location location ,
                                           NearLocation near_location ) {
    if ( (!location) || (!near_location) ) return LOCATION_NULL_ARGUMENT;
    SetResult result = setRemove( location->near_locations , near_location );
    if( result == SET_ITEM_DOES_NOT_EXIST )
        return LOCATION_NEAR_LOCATION_NOT_EXIST;
    return LOCATION_SUCCESS;
}

bool locationIsNearDestination( Location location , char* destination ) {
    assert( location && destination );
    SET_FOREACH( char* , current_location , location->near_locations ){
        if ( nearLocationCompare( current_location , destination ) == 0  )
            return true;
    }
    return false;
}

/**************************************
 *        WORLD_MAP Functions         *
 **************************************/

WorldMap worldMapCreate() {
    return listCreate( locationCopyElement , locationDestroyElement );
}

void worldMapDestroy( WorldMap world_map ) {
    listDestroy( world_map );
}

WorldMapResult worldMapAddLocation( WorldMap world_map , Location location ) {
    if ( (!world_map) || (!location) ) return WORLD_MAP_NULL_ARGUMENT;
    if ( worldMapDoesLocationExist( world_map , location ) )
        return WORLD_MAP_LOCATION_ALREADY_EXISTS;
    ListResult result = listInsertLast( world_map , location );
    if ( result == LIST_OUT_OF_MEMORY ) return WORLD_MAP_OUT_OF_MEMORY;
    return WORLD_MAP_SUCCESS;
}

WorldMapResult worldMapRemoveLocation( WorldMap world_map , Location location ){
    if ( (!world_map) || (!location) ) return WORLD_MAP_NULL_ARGUMENT;
    LIST_FOREACH( Location , current_location , world_map ) {
        if ( locationCompare(location , current_location) == LOCATIONS_EQAUL ) {
            listRemoveCurrent( world_map );
            return WORLD_MAP_SUCCESS;
        }
    }
    return WORLD_MAP_LOCATION_NOT_EXIST;
}

int worldMapGetSize( WorldMap world_map ) {
    assert( world_map );
    return listGetSize( world_map );
}

Location worldMapGetLocation( WorldMap world_map , char* location_name ) {
    if ( !world_map ) return NULL;
    if ((!location_name) || (strlen(location_name)==EMPTY_STRING)) return NULL;
    Location location = worldMapGetLocation(world_map,location_name);
    if ( worldMapDoesLocationExist(world_map,location) == false ) return NULL;
    LIST_FOREACH( Location , current_location , world_map ) {
        if (locationNameCompare(locationGetName(current_location),location_name)
            == LOCATIONS_EQAUL ) {
            return current_location;
        }
    }
    return NULL;
}

Pokemon worldMapGetPokemonInLocation( WorldMap world_map,char* location_name ){
    if (!(world_map) || !(location_name) ) return NULL;
    Location location = worldMapGetLocation( world_map ,location_name);
    if (worldMapDoesLocationExist( world_map , location ) == false) return NULL;
    Pokemon huntedPokemon = listGetFirst( location->pokemons );
    if ( !huntedPokemon ) return NULL;
    listRemoveCurrent( location->pokemons );
    return huntedPokemon;
}

bool worldMapIsLocationReachable( WorldMap world_map , char* current_location ,
                                  char* destination_location) {
    assert( destination_location && current_location && world_map);
    assert( strlen(current_location)  &&  strlen(destination_location) );
    Location location = worldMapGetLocation(world_map,current_location);
    Location destination = worldMapGetLocation(world_map,destination_location);
    assert(worldMapDoesLocationExist(world_map,location) &&
           worldMapDoesLocationExist(world_map,destination) );
    return locationIsNearDestination(location,destination_location);
}

WorldMapResult worldMapSort( WorldMap world_map ) {
    ListResult result = listSort( world_map , locationCompareElement );
    if ( result == LIST_NULL_ARGUMENT ) return WORLD_MAP_NULL_ARGUMENT;
    if ( result == LIST_OUT_OF_MEMORY ) return WORLD_MAP_OUT_OF_MEMORY;
    return WORLD_MAP_SUCCESS;
}

void worldMapPrintReport( WorldMap world_map , FILE* output_channel) {
    assert( world_map && output_channel );
    worldMapSort( world_map );
    mtmPrintLocationsHeader( output_channel );
    LIST_FOREACH( Location , current_location , world_map ) {
        LIST_FOREACH( Pokemon , current_pokemon , current_location->pokemons ) {
            mtmPrintLocation( output_channel, locationGetName(current_location),
                              pokemonGetName(current_pokemon) );
        }
    }
}
