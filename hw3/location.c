/**************************************
 *       Header files include         *
 **************************************/


#include "location.h"


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

/* function compare if 2 names equal. this function asserts parameters not NULL.
 *
 * @return
 * if equal return 0 , if the first is bigger return 1 and
 * if the second bigger return -1.
 */
int static locationNameCompare( char* location1 , char* location2 ){
    assert( location1 && location2 );
    int result = strcmp( location1 , location2 );
    if ( result > 0 ) return LOCATION1_BIGGER;
    if ( result < 0 ) return LOCATION2_BIGGER;
    return LOCATIONS_EQAUL;
}

/* function copy near location.
 *
 * @return
 * if location_name valid (=> not NULL and not an empty string) and provided
 * that memory allocation succeeded - return copy of nearLocation.
 * return NULL otherwise
 */
NearLocation static nearLocationCopy( NearLocation location_to_copy ){
    return nearLocationCreate ( location_to_copy );
}

/* function compare tow nearLocations. function assert locations not NULL.
 *
 * @return
 * if equal return 0 , if the first bigger return 1
 * and if the second bigger return -1.
 */
int static nearLocationCompare( NearLocation location1 , NearLocation location2 ) {
    return locationNameCompare( location1 , location2 );
}

/* function copy location.
 *
 * @return
 * if location valid (=> not NULL) and provided that memory allocation succeeded
 * return copy of location. return NULL otherwise.
 */
Location static locationCopy( Location location ) {
    if ( !location ) return NULL;
    Location copyed_location = locationCreate( locationGetName( location ) );
    if ( !copyed_location ) return NULL;
    listDestroy(copyed_location->pokemons);
    copyed_location->pokemons = listCopy( location->pokemons );
    RELEALSE_TREATMENT( copyed_location->pokemons , copyed_location );
    setDestroy(copyed_location->near_locations);
    copyed_location->near_locations = setCopy(location->near_locations);
    RELEALSE_TREATMENT( copyed_location->near_locations , copyed_location );
    return copyed_location;
}

/* define two locations equal if their names equal.
 * function compare two Locations. function asserts parameters not NULL.
 *
 * @return
 * if equal - return 0 , if the first bigger return 1 and if the second bigger
 * return -1.
 */
int locationCompare( Location location1 , Location location2 ) {
    assert ( location1 && location2 );
    return locationNameCompare( location1->name , location2->name );
}

/* function extricate location's name. function assert location not NULL.
 *
 * @return
 * location name.
 */
char static* locationGetName( Location location ) {
    assert( location );
    return location->name;
}

/* function check if destination is a NearLocation of location.
 *
 * @return
 * return true if destination is a NearLocation of location.
 * return false if one of the parameters NULL or destination is not a
 * NearLocation of location.
 */
bool static locationIsNearDestination( Location location , char* destination ) {
    if ( (!location) || (!destination) ) return false;
    SET_FOREACH( char* , current_location , location->near_locations ){
        if ( nearLocationCompare( current_location , destination ) == 0  )
            return true;
    }
    return false;
}

/* function extricate location from world map.
 *
 * @return
 * location with the same name as loation_name from world map if exist.
 * return NULL if world_map or loation_name are NULL or if location by that name
 * does not exist or if location_name is an empty string.
 */
Location static worldMapGetLocation( WorldMap world_map , char* location_name ) {
    if ( !world_map ) return NULL;
    if ((!location_name) || (strlen(location_name)==EMPTY_STRING)) return NULL;
    LIST_FOREACH( Location , current_location , world_map ) {
        if (locationNameCompare(locationGetName(current_location),location_name)
            == LOCATIONS_EQAUL ) {
            return current_location;
        }
    }
    return NULL;
}

/**************************************
 *          Wrapper Functions         *
 **************************************/

/* wrapper function to nearLocationCopy so it will be possible to work
 *  with set GDT.
 *
 * @return
 * valid copyed location or NULL if location NULL.
 */
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
 * list GDT.
 *
 * @return
 * 1 if location1 is bigger then location2, 0 if equal and -1 else
 */
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

/**************************************
 *         LOCATION Functions         *
 **************************************/


Location locationCreate( char* location_name ) {
    if ( (!location_name) || (!strlen(location_name)) ) return NULL;
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


LocationResult locationAddPokemon( Location location , Pokemon pokemon ){
    if ( (!location) || (!pokemon) ) return LOCATION_NULL_ARGUMENT;
    ListResult result = listInsertLast( location->pokemons , pokemon );
    if ( result == LIST_OUT_OF_MEMORY ) return LOCATION_OUT_OF_MEMORY;
    return LOCATION_SUCCESS;
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
    if ( worldMapDoesLocationExist( world_map , locationGetName(location) ) )
        return WORLD_MAP_LOCATION_ALREADY_EXISTS;
    ListResult result = listInsertLast( world_map , location );
    if ( result == LIST_OUT_OF_MEMORY ) return WORLD_MAP_OUT_OF_MEMORY;
    return WORLD_MAP_SUCCESS;
}

bool worldMapDoesLocationExist( WorldMap world_map , char* location ){
    if( (!world_map) || (!location) ) return false;
    LIST_FOREACH( Location , current_location , world_map ) {
        if(locationNameCompare(location,current_location->name)==LOCATIONS_EQAUL)
            return true;
    }
    return false;
}

Pokemon worldMapGetPokemonInLocation( WorldMap world_map,char* location_name ){
    if ( (!world_map) || (!location_name) ) return NULL;
    Location location = worldMapGetLocation( world_map ,location_name);
    if ( !location ) return NULL;
    if (worldMapDoesLocationExist( world_map , locationGetName(location) ) == false) return NULL;
    Pokemon huntedPokemon = pokemonCopy(listGetFirst( location->pokemons ));
    listRemoveCurrent( location->pokemons );
    return huntedPokemon;
}

bool worldMapIsLocationReachable( WorldMap world_map , char* current_location ,
                                  char* destination_location) {
    assert ( destination_location != NULL);
    assert ( world_map != NULL);
    if (!worldMapDoesLocationExist(world_map,destination_location) )
        return false;
    if( !current_location ) return true;
    if (!worldMapDoesLocationExist(world_map,current_location) )
        return false;
    Location location = worldMapGetLocation(world_map,current_location);
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
        Pokemon pokemon = listGetFirst(current_location->pokemons);
        mtmPrintLocation( output_channel, locationGetName(current_location),
                          pokemonGetName(pokemon) );
    }
}
