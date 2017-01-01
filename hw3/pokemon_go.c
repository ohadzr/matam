//
// Created by ohad on 28-Dec-16.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pokedex.h"
#include "pokemon_trainer.h"



#define MAX_LINE_SIZE 250
#define SPACE_DELIMITER " "
#define SEMICOLON_DELIMITER ";"
#define COMMAND_HANDLE(cmd_name, name, cmd_action, action, arg_counter, num) \
                                        (!strcmp(cmd_name, name)) \
                                        && (!strcmp(cmd_action, action)) &&   \
                                        (arg_counter==num)
#define GET_NEXT_ARGUMENT strtok(NULL, SPACE_DELIMITER)
#define GET_NEXT_LINE(line, input_file)   fgets(line,MAX_LINE_SIZE,input_file)
#define POSITIVE_QUANTITY 0


/********************************
 * Helper Function Declarations *
 ********************************/

/**
 * edit a string for fixing end of line (windows and unix)
 * replace \r or \n with \0
 *
 * @return
 * char* - the editted string
 */
static char* pokemonGoStringEdit(char *string);

/**
 *  check if the args to the main program are valid (see comments above main
 *  for more details)
 * @return
 * true - if valid.
 * false - if not.
 */
static bool isValidMainArgs(int argc, char** argv);

/**
 *  This function counts how many args each command line has
 * @return
 * int - number of args
 */
static int countArgsInCommand( char* command );

/**
 *  This function check what trainer result was and replace it with the right
 *  MtmErrorCode
 * @return
 * POKEMON_TRAINER_NULL_ARG : MTM_INVALID_ARGUMENT
 * POKEMON_TRAINER_POKEMON_DOESNT_EXIST : MTM_POKEMON_DOES_NOT_EXIST
 * POKEMON_TRAINER_OUT_OF_MEMORY: MTM_OUT_OF_MEMORY
 * POKEMON_TRAINER_ITEM_OUT_OF_STOCK : MTM_ITEM_OUT_OF_STOCK
 * POKEMON_TRAINER_INSUFFICIENT_BUDGET : MTM_BUDGET_IS_NOT_SUFFICIENT
 * POKEMON_TRAINER_ALREADY_IN_LOCATION : MTM_TRAINER_ALREADY_IN_LOCATION
 * POKEMON_TRAINER_LOCATION_IS_NOT_REACHABLE : MTM_LOCATION_IS_NOT_REACHABLE
 * POKEMON_TRAINER_INVALID_AGR : MTM_INVALID_ARGUMENT
 * POKEMON_TRAINER_POKEMON_HP_AT_MAX : MTM_HP_IS_AT_MAX
 * POKEMON_TRAINER_ALREADY_EXIST : MTM_TRAINER_NAME_ALREADY_EXISTS
 * POKEMON_TRAINER_NO_AVAILABLE_ITEM_FOUND : MTM_NO_AVAILABLE_ITEM_FOUND
 * POKEMON_TRAINER_SUCCESS : MTM_SUCCESS
 */
static MtmErrorCode handlePokemonTrainerResult(PokemonTrainerResult result);

/**
 *  This function check what store result was and replace it with the right
 *  MtmErrorCode
 * @return
 * STORE_SUCCESS: MTM_SUCCESS
 * STORE_NULL_ARGUMENT : MTM_INVALID_COMMAND_LINE_PARAMETERS
 * STORE_ITEM_NOT_EXIST : MTM_ITEM_OUT_OF_STOCK
 * STORE_OUT_OF_MEMORY : MTM_OUT_OF_MEMORY
 */
static MtmErrorCode handleStoreResult(StoreResult result);

/**
 *  This function casts a char* to int (using @sscanf)
 * @return
 * int - the given string cast to int
 */
static int stringToInt(char *int_as_char);

/**
 *  This function loads the given pokedex file into the empty pokedex
 * @return
 * MTM_OUT_OF_MEMORY - if allocation error.
 * MTM_SUCCESS - otherwise.
 */
static MtmErrorCode loadPokedexFile(Pokedex pokedex, FILE* pokedex_file);

/**
 *  This function loads the given evolutions file into the pokedex (after
 *  loading pokedex file)
 * @return
 * MTM_OUT_OF_MEMORY - if allocation error.
 * MTM_SUCCESS - otherwise.
 */
static MtmErrorCode loadEvolutionsFile(Pokedex pokedex, FILE* evolution_file);

/**
 *  This function loads the given locations file into the a new location
 * @return
 * New allocated location.
 * NULL if allocation error
 */
static Location loadLocationsFileAddPokemon(char* location_name,
                                            WorldMap world_map,
                                            Pokedex pokedex);

/**
 *  This function loads the location that a trainer can go to from a source
 *  location into the world map (after loading location into world map)
 * @return
 * MTM_OUT_OF_MEMORY - if allocation error.
 * MTM_SUCCESS - otherwise.
 */
static MtmErrorCode loadLocationsFileAddNearLocations(char* near_location,
                                                      Location location,
                                                      WorldMap world_map);




/****************************************
 *    Assistent PokemonGO Funcs         *
 ****************************************/

char* pokemonGoStringEdit(char *string) {
	if( string && strlen(string) ) {
		char* current_letter = string;
		while( *current_letter ) {
			if ( (*current_letter) == '\r' || (*current_letter) == '\n')
				*current_letter = '\0';
            if ((*current_letter) == '\t')
                *current_letter = ' ';
			current_letter++;
		}
	}
    return string;
}

bool isValidMainArgs(int argc, char** argv) {
    if (argc < 7 || argc > 11 || (argc%2 != 1) || strcmp(argv[1], "-p") ||
        strcmp(argv[3], "-e") || strcmp(argv[5], "-l")) {
        mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
        return false;
    }

    else if (argc == 9 && (strcmp(argv[7], "-i") &&
                           strcmp(argv[7], "-o"))) {
        mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
        return false;
    }

    else if (argc == 11 && strcmp(argv[7], "-i") && strcmp(argv[9], "-o")) {
        mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
        return false;
    }

    return true;
}


int countArgsInCommand( char* command ) {
    int counter = 0;
    char *current_word = strtok(command, SPACE_DELIMITER);
    while (current_word) {
        current_word = GET_NEXT_ARGUMENT;
        counter++;
    }
    return counter;
}


MtmErrorCode handlePokemonTrainerResult(PokemonTrainerResult result) {
    switch (result) {
        case POKEMON_TRAINER_NULL_ARG:
            return MTM_INVALID_ARGUMENT;
        case POKEMON_TRAINER_POKEMON_DOESNT_EXIST:
            return MTM_POKEMON_DOES_NOT_EXIST;
        case POKEMON_TRAINER_OUT_OF_MEMORY:
            return MTM_OUT_OF_MEMORY;
        case POKEMON_TRAINER_ITEM_OUT_OF_STOCK:
            return MTM_ITEM_OUT_OF_STOCK;
        case POKEMON_TRAINER_INSUFFICIENT_BUDGET:
            return MTM_BUDGET_IS_NOT_SUFFICIENT;
        case POKEMON_TRAINER_ALREADY_IN_LOCATION:
            return MTM_TRAINER_ALREADY_IN_LOCATION;
        case POKEMON_TRAINER_LOCATION_IS_NOT_REACHABLE:
        	return MTM_LOCATION_IS_NOT_REACHABLE;
        case POKEMON_TRAINER_INVALID_AGR:
        	return MTM_INVALID_ARGUMENT;
        case POKEMON_TRAINER_POKEMON_HP_AT_MAX:
        	return MTM_HP_IS_AT_MAX;
        case POKEMON_TRAINER_ALREADY_EXIST:
        	return MTM_TRAINER_NAME_ALREADY_EXISTS;
        case POKEMON_TRAINER_SUCCESS:
        	return MTM_SUCCESS;
        case POKEMON_TRAINER_NO_AVAILABLE_ITEM_FOUND:
        	return MTM_NO_AVAILABLE_ITEM_FOUND;
    }
    return MTM_SUCCESS;
}


MtmErrorCode handleStoreResult(StoreResult result) {
    switch (result) {
        case STORE_SUCCESS:
            return MTM_SUCCESS;
        case STORE_NULL_ARGUMENT:
            return MTM_INVALID_COMMAND_LINE_PARAMETERS;
        case STORE_ITEM_NOT_EXIST:
        	return MTM_ITEM_OUT_OF_STOCK;
        case STORE_OUT_OF_MEMORY:
        	return MTM_OUT_OF_MEMORY;
    }
    return MTM_SUCCESS;
}

int stringToInt(char *int_as_char) {
    assert(int_as_char != NULL);

    int num;
    sscanf(int_as_char, "%d", &num);

    return num;
}

MtmErrorCode loadPokedexFile(Pokedex pokedex, FILE* pokedex_file) {
    char line[MAX_LINE_SIZE], *pokemon_name, *initial_cp;

    while (GET_NEXT_LINE(line,pokedex_file)) {
        pokemonGoStringEdit(line);
        pokemon_name = strtok(line, SPACE_DELIMITER);
        if (pokemon_name == NULL) continue;

        initial_cp = GET_NEXT_ARGUMENT;
        int cp = stringToInt(initial_cp);
        PokemonInfo pokemon_info = pokedexPokemonInfoCreate(pokemon_name, cp);
        if (pokemon_info == NULL) {
            pokedexDestroy(pokedex);
            return MTM_OUT_OF_MEMORY;
        }
        if (pokedexAddPokemonInfo(pokedex, pokemon_info) ==
                POKEDEX_OUT_OF_MEMORY) {
            pokedexPokemonInfoDestroy(pokemon_info);
            return MTM_OUT_OF_MEMORY;
        }

        char* type = GET_NEXT_ARGUMENT;
        while (type != NULL) {
            pokedexAddType(pokedex, pokemon_name, type);
            type = GET_NEXT_ARGUMENT;
        }
        pokedexPokemonInfoDestroy(pokemon_info);
    }

    return MTM_SUCCESS;
}

MtmErrorCode loadEvolutionsFile(Pokedex pokedex, FILE* evolution_file) {
    char line[MAX_LINE_SIZE], *pokemon_name;
    char *evolution_name, *evolution_level_char;
    int evolution_level;
    while (GET_NEXT_LINE(line,evolution_file)) {
        pokemonGoStringEdit(line);
        pokemon_name = strtok(line, SPACE_DELIMITER);
        evolution_name = GET_NEXT_ARGUMENT;
        evolution_level_char = GET_NEXT_ARGUMENT;
        evolution_level = stringToInt(evolution_level_char);
        PokedexResult result = pokedexUpdateNextEvolution(pokedex, pokemon_name,
                                                          evolution_name,
                                                          evolution_level);
        if (result == POKEDEX_OUT_OF_MEMORY) {
            pokedexDestroy(pokedex);
            return MTM_OUT_OF_MEMORY;
        }
    }

    return MTM_SUCCESS;
}


Location loadLocationsFileAddPokemon(char* location_name,
                                         WorldMap world_map, Pokedex pokedex) {
    Location location = locationCreate(location_name);

    char* pokemon_name = GET_NEXT_ARGUMENT;
    while (pokemon_name != NULL) {
        Pokemon pokemon = pokemonCreate(pokemon_name, pokedex);
        if (pokemon == NULL || location == NULL) {
            worldMapDestroy(world_map);
            locationDestroy(location);
            pokemonDestroy(pokemon);
            return NULL;
        }
        LocationResult result = locationAddPokemon(location, pokemon);
        if (result == LOCATION_OUT_OF_MEMORY) {
            worldMapDestroy(world_map);
            locationDestroy(location);
            pokemonDestroy(pokemon);
            return NULL;
        }
        pokemonDestroy(pokemon);
        pokemon_name = GET_NEXT_ARGUMENT;
    }

    return location;
}

MtmErrorCode loadLocationsFileAddNearLocations(char* near_location,
                                               Location location,
                                               WorldMap world_map) {
    while (near_location != NULL) {
        NearLocation new_near_location = nearLocationCreate(near_location);
        LocationResult result = locationAddNearLocation(location,
                                                        new_near_location);
        if (result != LOCATION_SUCCESS) {
            worldMapDestroy(world_map);
            locationDestroy(location);
            nearLocationDestroy(near_location);
            return MTM_OUT_OF_MEMORY;
        }

        nearLocationDestroy(new_near_location);
        near_location = GET_NEXT_ARGUMENT;
    }

    WorldMapResult result = worldMapAddLocation(world_map, location);
    if (result == WORLD_MAP_OUT_OF_MEMORY) {
        worldMapDestroy(world_map);
        locationDestroy(location);
        return MTM_OUT_OF_MEMORY;
    }
    return MTM_SUCCESS;

}

/********************************
 *          Commands Funcs      *
 ********************************/

MtmErrorCode pokemonGoAddTrainer( Pokedex pokedex, WorldMap world_map, Trainers trainers, FILE* output ) {
    if (trainers == NULL || pokedex == NULL || world_map == NULL)
        return MTM_OUT_OF_MEMORY;
    char* name =  GET_NEXT_ARGUMENT;
    char* budget_char = GET_NEXT_ARGUMENT;
    char* start_point = GET_NEXT_ARGUMENT;
    int budget = stringToInt(budget_char);
    if ( !output ) return MTM_CANNOT_OPEN_FILE;
    if ( !(pokemonTrainerIsValidArgs( name, budget)) )
        return MTM_INVALID_ARGUMENT;
    if ( trainersDoesTrainerExist(trainers,name) )
        return MTM_TRAINER_NAME_ALREADY_EXISTS;
    if ( !worldMapDoesLocationExist(world_map,start_point) )
        return MTM_LOCATION_DOES_NOT_EXIST;

    PokemonTrainer trainer = pokemonTrainerCreate(name, budget);
    if (trainer == NULL) return MTM_OUT_OF_MEMORY;

    if ( pokemonTrainerGoHunt( trainer, start_point, world_map, pokedex, output)
         == POKEMON_TRAINER_OUT_OF_MEMORY ) {
        pokemonTrainerDestroy(trainer);
        return MTM_OUT_OF_MEMORY;
    }
    if ( trainersAddTrainer( trainers, trainer )
         == POKEMON_TRAINER_OUT_OF_MEMORY ) {
        pokemonTrainerDestroy(trainer);
        return MTM_OUT_OF_MEMORY;
    }
    pokemonTrainerDestroy(trainer);
    return MTM_SUCCESS;
}

MtmErrorCode pokemonGoTrainerGoHunt( Pokedex pokedex ,WorldMap world_map,
                                     Trainers trainers, FILE* output) {
    if (trainers == NULL || pokedex == NULL || world_map == NULL)
        return MTM_OUT_OF_MEMORY;

    char* trainer_name = GET_NEXT_ARGUMENT;
    char* destination_location = GET_NEXT_ARGUMENT;

    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    if ( !trainersDoesTrainerExist(trainers,trainer_name) )
        return MTM_TRAINER_DOES_NOT_EXIST;
    if ( !worldMapDoesLocationExist(world_map,destination_location) )
        return MTM_LOCATION_DOES_NOT_EXIST;

    PokemonTrainer trainer = trainersGetTrainer( trainers, trainer_name );
    PokemonTrainerResult result = pokemonTrainerGoHunt( trainer,
                                                        destination_location,
                                                        world_map, pokedex,
                                                        output);
    return handlePokemonTrainerResult(result);
}


MtmErrorCode pokemonGoTrainerPurchase(Trainers trainers, Store store) {
    if (trainers == NULL || store == NULL) return MTM_OUT_OF_MEMORY;

    char* trainer_name = GET_NEXT_ARGUMENT;
    char* item_name = GET_NEXT_ARGUMENT;
    char* item_value = GET_NEXT_ARGUMENT;
    int value = stringToInt(item_value);

    if (trainersDoesTrainerExist(trainers, trainer_name) == false)
        return MTM_TRAINER_DOES_NOT_EXIST;

    if (itemIsValidArgs(value, item_name) == false) return MTM_INVALID_ARGUMENT;

    PokemonTrainer trainer = trainersGetTrainer(trainers, trainer_name);
    Item item = itemCreate(value, item_name);
    if (item == NULL) return MTM_OUT_OF_MEMORY;

    PokemonTrainerResult result = pokemonTrainerBuyItem(trainer,item,store );

    itemDestroy(item);
    return handlePokemonTrainerResult(result);
}

MtmErrorCode pokemonGoStoreAddItem(Store store) {
    if (store == NULL) return MTM_OUT_OF_MEMORY;

    char* item_name = GET_NEXT_ARGUMENT;
    char* item_value = GET_NEXT_ARGUMENT;
    char* quantity_char = GET_NEXT_ARGUMENT;
    int value = stringToInt(item_value), quantity = stringToInt(quantity_char);

    if (!itemIsValidArgs(value, item_name) || quantity < POSITIVE_QUANTITY)
        return MTM_INVALID_ARGUMENT;
    Item item = itemCreate(value, item_name);
    if (item == NULL) return MTM_OUT_OF_MEMORY;

    for (int i=0; i<quantity; i++) {
        StoreResult result = storeAddItem(store, item);
        if (handleStoreResult(result) != MTM_SUCCESS) {
            itemDestroy(item);
            return handleStoreResult(result);
        }
    }

    itemDestroy(item);
    return MTM_SUCCESS;
}

MtmErrorCode pokemonGoTrainerBattle(Pokedex pokedex, Trainers trainers,
                                    FILE* output) {
    if (pokedex == NULL || trainers == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    char* trainer1_name = GET_NEXT_ARGUMENT;
    char* trainer2_name = GET_NEXT_ARGUMENT;
    char* pokemon_id_char_1 = GET_NEXT_ARGUMENT;
    char* pokemon_id_char_2 = GET_NEXT_ARGUMENT;
    int pokemon_id1 = stringToInt(pokemon_id_char_1);
    int pokemon_id2 = stringToInt(pokemon_id_char_2);

    if (!strcmp(trainer1_name, trainer2_name))
        return MTM_INVALID_ARGUMENT;
    if (!trainersDoesTrainerExist(trainers, trainer1_name) ||
            !trainersDoesTrainerExist(trainers, trainer2_name))
        return MTM_TRAINER_DOES_NOT_EXIST;
    PokemonTrainer trainer1 =  trainersGetTrainer(trainers,trainer1_name);
    PokemonTrainer trainer2 =  trainersGetTrainer(trainers,trainer2_name);

    PokemonTrainerResult result = pokemonTrainerFight(trainer1, trainer2,
                                                      pokemon_id1, pokemon_id2,
                                                      pokedex, output);
    return handlePokemonTrainerResult(result);
}

MtmErrorCode pokemonGoPokemonHealOrTrain(Trainers trainers, bool is_heal) {
    if (trainers == NULL) return MTM_OUT_OF_MEMORY;

    char* trainer_name = GET_NEXT_ARGUMENT;
    char* pokemon_id_char = GET_NEXT_ARGUMENT;
    int pokemon_id = stringToInt(pokemon_id_char);

    if (!trainersDoesTrainerExist(trainers, trainer_name))
        return MTM_TRAINER_DOES_NOT_EXIST;

    PokemonTrainer trainer = trainersGetTrainer(trainers,trainer_name);
    PokemonTrainerResult result;

    if (is_heal)
        result = pokemonTrainerHealPokemon(trainer, pokemon_id);
    else
        result = pokemonTrainerTrainPokemon(trainer, pokemon_id);

    return handlePokemonTrainerResult(result);

}


MtmErrorCode pokemonGoTrainerReport(Trainers trainers, FILE* output) {
    if (trainers == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    char* trainer_name = GET_NEXT_ARGUMENT;

    if (!trainersDoesTrainerExist(trainers, trainer_name))
        return MTM_TRAINER_DOES_NOT_EXIST;

    PokemonTrainer trainer = trainersGetTrainer(trainers,trainer_name);

    PokemonTrainerResult result = pokemonTrainerReport(trainer, output);

    return handlePokemonTrainerResult(result);
}


MtmErrorCode pokemonGoWorldMapReport(WorldMap world_map, FILE* output) {
    if (world_map == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    worldMapPrintReport(world_map, output);
    return MTM_SUCCESS;
}


MtmErrorCode pokemonGoStoreReport(Store store, FILE* output) {
    if (store == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    mtmPrintStockHeader( output );
    storePrintStock(store, output);
    return MTM_SUCCESS;
}



MtmErrorCode pokemonGoProcessCommand(char* command, Trainers trainers,
                             Store store, WorldMap world_map, Pokedex pokedex,
                             FILE* output) {
	char command_for_count[MAX_LINE_SIZE];
	strcpy(command_for_count, pokemonGoStringEdit(command));
    int arg_counter = countArgsInCommand(command_for_count);
    if (arg_counter == 0) return MTM_SUCCESS;
    if (arg_counter < 2) return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    char* section = strtok(command, SPACE_DELIMITER);
    char* action = GET_NEXT_ARGUMENT;
    if (COMMAND_HANDLE(section, "trainer",action, "add", arg_counter, 5))
        return pokemonGoAddTrainer( pokedex, world_map, trainers, output );
    if (COMMAND_HANDLE(section, "trainer",action, "go", arg_counter, 4))
        return pokemonGoTrainerGoHunt( pokedex , world_map, trainers, output);
    if (COMMAND_HANDLE(section,"trainer",action,"purchase",arg_counter,5))
        return pokemonGoTrainerPurchase(trainers, store);
    if (COMMAND_HANDLE(section, "store",action, "add", arg_counter, 5))
        return pokemonGoStoreAddItem(store);
    if (COMMAND_HANDLE(section, "battle",action,"fight", arg_counter, 6))
        return pokemonGoTrainerBattle(pokedex, trainers, output);
    if (COMMAND_HANDLE(section, "pokemon",action, "heal", arg_counter,4))
        return pokemonGoPokemonHealOrTrain(trainers, true);
    if (COMMAND_HANDLE(section,"pokemon",action,"train",arg_counter, 4))
        return pokemonGoPokemonHealOrTrain(trainers, false);
    if (COMMAND_HANDLE(section,"report",action,"trainer",arg_counter, 3))
        return pokemonGoTrainerReport(trainers, output);
    if (COMMAND_HANDLE(section,"report",action,"locations",arg_counter,2))
        return pokemonGoWorldMapReport(world_map, output);
    if (COMMAND_HANDLE(section, "report",action, "stock", arg_counter, 2))
        return pokemonGoStoreReport(store, output);
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

/********************************
 *        PokemonGo Funcs       *
 ********************************/


Trainers pokemonGoTrainersCreate() {
    return trainersCreate();
}

Store pokemonGoStoreCreate() {
    return storeCreate();
}

WorldMap pokemonGoWorldMapCreate(FILE* location_file, Pokedex pokedex) {
    if (location_file == NULL) return NULL;
    WorldMap world_map = worldMapCreate();
    if (world_map == NULL) return NULL;
    char location_info[MAX_LINE_SIZE];
    char *first_part, *second_part, *location_name ,*near_location;

    while (GET_NEXT_LINE(location_info,location_file)) {
        pokemonGoStringEdit(location_info);
        first_part = strtok(location_info, SEMICOLON_DELIMITER);
        if (first_part == NULL) continue;
        second_part = strtok(NULL, SEMICOLON_DELIMITER);
        location_name = strtok(first_part, SPACE_DELIMITER);
        if (location_name == NULL) continue;
        Location location = loadLocationsFileAddPokemon(location_name,
                                                        world_map, pokedex);
        if (location == NULL)
            return NULL;
        if (second_part != NULL) {
            near_location = strtok(second_part, SPACE_DELIMITER);
            if (near_location == NULL)
                return NULL;
        }
        else near_location = NULL;
        if (loadLocationsFileAddNearLocations(near_location, location,
                                   world_map)  == MTM_OUT_OF_MEMORY)
            return NULL;
        locationDestroy(location);
    }
    return world_map;
}


Pokedex pokemonGoPokedexCreate(FILE* pokedex_file, FILE* evolution_file) {
    if (!pokedex_file && !evolution_file) return NULL;

    Pokedex pokedex = pokedexCreate();
    if (pokedex == NULL) return NULL;

    MtmErrorCode result = loadPokedexFile(pokedex, pokedex_file);
    if (result != MTM_SUCCESS) {
        pokedexDestroy(pokedex);
        return NULL;
    }

    result = loadEvolutionsFile(pokedex, evolution_file);
    if (result != MTM_SUCCESS){
        pokedexDestroy(pokedex);
        return NULL;
    }

    return pokedex;
}


void destroyPokemonGo(Trainers trainers, Store store, WorldMap world_map,
                      Pokedex pokedex) {
    trainersDestroy(trainers);
    storeDestroy(store);
    worldMapDestroy(world_map);
    pokedexDestroy(pokedex);

}



void pokemonGo(FILE* pokedex_file, FILE* evolution_file, FILE* location_file,
               FILE* input, FILE* output) {
    Trainers trainers = pokemonGoTrainersCreate();
    Store store = pokemonGoStoreCreate();
    Pokedex pokedex = pokemonGoPokedexCreate(pokedex_file, evolution_file);
    WorldMap world_map = pokemonGoWorldMapCreate(location_file, pokedex);

    if (!trainers || !store || !world_map || !pokedex) {
        mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
        destroyPokemonGo(trainers, store, world_map, pokedex);
        return;
    }

    char command[MAX_LINE_SIZE];
    MtmErrorCode result = MTM_SUCCESS;
    // infinite game loop
    while (result != MTM_OUT_OF_MEMORY && result != MTM_CANNOT_OPEN_FILE
           && result != MTM_INVALID_COMMAND_LINE_PARAMETERS) {

        if (!GET_NEXT_LINE(command,input)) break;
        if (command == NULL) break;
        result = pokemonGoProcessCommand(command, trainers, store,
                                         world_map, pokedex, output);
        if (result != MTM_SUCCESS) {
            mtmPrintErrorMessage(stderr, result);
        }
    }
    destroyPokemonGo(trainers, store, world_map, pokedex);
}


/*****************************************************************************
 *                       * Main Program - PokemonGo *
 *
 *   This is a PokemonGo game!
 *   How to play:
 *
 *   pokemon_go_mtm –p <pokedex_filename> -e <evolutions_filename>
 *   -l <locations_filename> [-i <input_file>] [-o <output_file>]
 *
 *   <pokedex_filename>, <evolutions_filename> , <locations_filename>
 *   MUST BE CORRECT
 *
 *   In any case of allocation failure, invalid command line parameters or
 *   a failure in file opening - the program will exit.
 *
 *   otherwise, the program continue running until EOF (or Ctrl+D if no
 *   input_file was given)
 *
 *
 *   available commands:
 *
 *   trainer add <name> <budget> <start_point>
 *   trainer go <name> <location>
 *   store add <item> <value> <quantity>
 *   trainer purchase <name> <item> <value>
 *   battle fight <trainer1> <trainer2> <pokemon1> <pokemon2>
 *   pokemon heal <trainer> <pokemon_id>
 *   pokemon train <trainer> <pokemon_id>
 *   report trainer <trainer>
 *   report locations
 *   report stock
 *
 *
 *
 *   GOTTA CATCH EM ALL !
 *
 *   GOOD LUCK !  :)
 *
 ****************************************************************************/


int main(int argc, char** argv) {
    setvbuf(stdout, NULL, _IONBF, 0); //TODO: remove this
    setvbuf(stderr, NULL, _IONBF, 0);

    if (isValidMainArgs(argc, argv)) {
        FILE* pokedex_file = fopen(argv[2],"r");
        FILE* evolution_file = fopen(argv[4],"r");
        FILE* location_file = fopen(argv[6],"r");
        FILE* input = stdin;
        FILE* output = stdout;
        if (argc == 11) {
            input = fopen(argv[8],"r");
            output = fopen(argv[10],"w+");
        }
        else if (argc == 9) {
            if (!strcmp(argv[7], "-i")) input = fopen(argv[8],"r");
            else output = fopen(argv[8],"w+");
        }
        if (pokedex_file == NULL || evolution_file == NULL ||
                location_file == NULL || input == NULL || output == NULL )
            mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
        else
            pokemonGo(pokedex_file, evolution_file, location_file,
                      input, output);

        fclose(pokedex_file);
        fclose(evolution_file);
        fclose(location_file);
        if (input != stdin) fclose(input);
        if (output != stdout) fclose(output);
    }
    return 0;
}
