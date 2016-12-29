//
// Created by ohad on 28-Dec-16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pokedex.h"
#include "pokemon_trainer.h"
#include "pokedex.h"
#include "location.h"
#include "store.h"
#include "print_utils.h"


#define MAX_LINE_SIZE 250
#define SPACE_DELIMITER " "
#define SEMILICOLON_DELIMITER ";"
#define COMMAND_HANDLE(cmd_name, name, cmd_action, action, arg_counter, num) \
                                        (!strcmp(cmd_name, name)) \
                                        && (!strcmp(cmd_action, action)) &&   \
                                        (arg_counter!=num)




/********************************
 * Helper Function Declarations *
 ********************************/

static int countArgsInCommand( char* command );

static MtmErrorCode handlePokemonTrainerResult(PokemonTrainerResult result);

static int charToInt(char* int_as_char);

/****************************************
 *    Assistent PokemonGO Funcs         *
 ****************************************/



int countArgsInCommand( char* command ) {
    int counter = 0;
    char *current_word = strtok(command, SPACE_DELIMITER);
    while (current_word) {
        current_word = strtok(NULL, SPACE_DELIMITER);
        counter++;
    }
    return counter;
}


MtmErrorCode handlePokemonTrainerResult(PokemonTrainerResult result) {
    switch (result) {
        case POKEMON_TRAINER_NULL_ARG:
            return MTM_INVALID_ARGUMENT;
        case POKEMON_TRAINER_POKEMON_DOESNT_EXIST:
            return MTM_TRAINER_DOES_NOT_EXIST;
        case POKEMON_TRAINER_OUT_OF_MEMORY:
            return MTM_OUT_OF_MEMORY;
        case POKEMON_TRAINER_ITEM_OUT_OF_STOCK:
            return MTM_ITEM_OUT_OF_STOCK;
        case POKEMON_TRAINER_INSUFFICIENT_BUDGET:
            return MTM_BUDGET_IS_NOT_SUFFICIENT;
        case POKEMON_TRAINER_ALREADY_IN_LOCATION:
            return MTM_TRAINER_ALREADY_IN_LOCATION;
        case POKEMON_TRAINER_LOCATION_IS_NOT_REACHABLE:
            MTM_LOCATION_IS_NOT_REACHABLE;
        case POKEMON_TRAINER_INVALID_AGR:
            MTM_INVALID_ARGUMENT;
        case POKEMON_TRAINER_POKEMON_HP_AT_MAX:
            MTM_HP_IS_AT_MAX;
        case POKEMON_TRAINER_ALREADY_EXIST:
            MTM_TRAINER_NAME_ALREADY_EXISTS;
        case POKEMON_TRAINER_SUCCESS:MTM_SUCCESS;
    }
    return MTM_SUCCESS;
}

int charToInt(char* int_as_char) {
    assert(int_as_char != NULL);

    int num;
    sscanf(int_as_char, "%d", &num);

    return num;
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



    char location_info[250];
    char *first_part, *second_part,*location_name,*pokemon_name, *near_location;

    while (fgets(location_info, MAX_LINE_SIZE, location_file)) {
        first_part = strtok(location_info, SEMILICOLON_DELIMITER);
        if (first_part == NULL) continue;
        second_part = strtok(NULL, SEMILICOLON_DELIMITER);

        location_name = strtok(first_part, SPACE_DELIMITER);
        Location location = locationCreate(location_name);
        pokemon_name = strtok(NULL, SPACE_DELIMITER);
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
            pokemon_name = strtok(NULL, SPACE_DELIMITER);
        }

        near_location = strtok(second_part, SPACE_DELIMITER);
        while (near_location != NULL) {
            NearLocation new_near_location = nearLocationCreate(near_location);
            LocationResult result = locationAddNearLocation(location,
                                                            new_near_location);
            if (result != LOCATION_SUCCESS) {
                worldMapDestroy(world_map);
                locationDestroy(location);
                nearLocationDestroy(near_location);
                return NULL;
            }

            nearLocationDestroy(near_location);
            near_location = strtok(NULL, SPACE_DELIMITER);
        }

        WorldMapResult result = worldMapAddLocation(world_map, location);
        if (result == LIST_OUT_OF_MEMORY) {
            worldMapDestroy(world_map);
            locationDestroy(location);
        }

    }

    return world_map;
}


Pokedex pokemonGoPokedexCreate(FILE* pokedex_file, FILE* evolution_file) {
    if (!pokedex_file && !evolution_file) return NULL;

    Pokedex pokedex = pokedexCreate();
    if (pokedex == NULL) return NULL;

    char pokemon_line[250], *pokemon_name, *initial_cp;

    while (fgets(pokemon_line, MAX_LINE_SIZE, pokedex_file)) {
        pokemon_name = strtok(pokemon_line, SPACE_DELIMITER);
        if (pokemon_name == NULL) continue;

        initial_cp = strtok(NULL, SPACE_DELIMITER);
        int cp;
        sscanf(initial_cp, "%d", &cp);
        PokemonInfo pokemon_info = pokedexPokemonInfoCreate(pokemon_name, cp);
        if (pokemon_info == NULL) {
            pokedexDestroy(pokedex);
            return NULL;
        }

        char* type = strtok(NULL, SPACE_DELIMITER);
        while (type != NULL) {
            pokedexAddType(pokedex, pokemon_name, type);
            type = strtok(NULL, SPACE_DELIMITER);
        }
        pokedexPokemonInfoDestroy(pokemon_info);
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


MtmErrorCode pokemonGoTrainerBattle(Pokedex pokedex, Trainers trainers) {


}

MtmErrorCode pokemonGoPokemonHeal(Trainers trainers, FILE* output) {
    if (trainers == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    char* trainer_name = strtok(NULL, SPACE_DELIMITER); //TODO: dup with next - please fix
    char* pokemon_id_char = strtok(NULL, SPACE_DELIMITER);
    int pokemon_id = charToInt(pokemon_id_char);


    if (!trainersDoesTrainerExist(trainers, trainer_name))
        return MTM_TRAINER_DOES_NOT_EXIST;

    PokemonTrainer trainer = trainersGetTrainer(trainers,trainer_name);

    PokemonTrainerResult result = pokemonTrainerHealPokemon(trainer,
                                                             pokemon_id);
    return handlePokemonTrainerResult(result);

}

MtmErrorCode pokemonGoPokemonTrain(Trainers trainers, FILE* output) {
    if (trainers == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    char* trainer_name = strtok(NULL, SPACE_DELIMITER);
    char* pokemon_id_char = strtok(NULL, SPACE_DELIMITER);
    int pokemon_id = charToInt(pokemon_id_char);


    if (!trainersDoesTrainerExist(trainers, trainer_name))
        return MTM_TRAINER_DOES_NOT_EXIST;

    PokemonTrainer trainer = trainersGetTrainer(trainers,trainer_name);

    PokemonTrainerResult result = pokemonTrainerTrainPokemon(trainer,
                                                             pokemon_id);
    return handlePokemonTrainerResult(result);

}


MtmErrorCode pokemonGoTrainerReport(Trainers trainers, FILE* output) {
    if (trainers == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) return MTM_CANNOT_OPEN_FILE;

    char* trainer_name = strtok(NULL, SPACE_DELIMITER);

    if (!trainersDoesTrainerExist(trainers, trainer_name))
        return MTM_TRAINER_DOES_NOT_EXIST;

    PokemonTrainer trainer = trainersGetTrainer(trainers,trainer_name);

    PokemonTrainerResult result = pokemonTrainerReport(trainer, output);

    return handlePokemonTrainerResult(result);
}


MtmErrorCode pokemonGoWorldMapReport(WorldMap world_map, FILE* output) {
    if (world_map == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) MTM_CANNOT_OPEN_FILE;

    worldMapPrintReport(world_map, output);
    return MTM_SUCCESS;
}


MtmErrorCode pokemonGoStoreReport(Store store, FILE* output) {
    if (store == NULL) return MTM_OUT_OF_MEMORY;
    if (output == NULL) MTM_CANNOT_OPEN_FILE;

    storePrintStock(store, output);
    return MTM_SUCCESS;
}



bool pokemonGoProcessCommand(char* command, Trainers trainers,
                             Store store, WorldMap world_map, Pokedex pokedex,
                             FILE* input, FILE* output) {
    int arg_counter = countArgsInCommand(command);
    if (arg_counter < 2) return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    char* section = strtok(command, SPACE_DELIMITER);
    char* action = strtok(NULL, SPACE_DELIMITER);

    if (COMMAND_HANDLE(section, "trainer",action, "add", arg_counter, 5))
        return pokemonGoAddTrainer();
    if (COMMAND_HANDLE(section, "trainer",action, "go", arg_counter, 4))
        return pokemonGoTrainerGoHunt();
    if (COMMAND_HANDLE(section,"trainer",action,"purchase",arg_counter,5))
        return pokemonGoTrainerPurchase();
    if (COMMAND_HANDLE(section, "store",action, "add", arg_counter, 5))
        return pokemonGoStoreAddItem();
    if (COMMAND_HANDLE(section, "battle",action,"fight", arg_counter, 6))
        return pokemonGoTrainerBattle();
    if (COMMAND_HANDLE(section, "pokemon",action, "heal", arg_counter,4))
        return pokemonGoPokemonHeal(trainers, output);
    if (COMMAND_HANDLE(section,"pokemon",action,"train",arg_counter, 4))
        return pokemonGoPokemonTrain(trainers, output);
    if (COMMAND_HANDLE(section,"report",action,"trainer",arg_counter, 3))
        return pokemonGoTrainerReport(trainers, output);
    if (COMMAND_HANDLE(section,"report",action,"locations",arg_counter,2))
        return pokemonGoWorldMapReport(world_map, output);
    if (COMMAND_HANDLE(section, "report",action, "stock", arg_counter, 5))
        return pokemonGoStoreReport(store, output);

    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}



void pokemonGo(FILE* pokedex_file, FILE* evolution_file, FILE* location_file,
               FILE* input, FILE* output) {
    Trainers trainers = pokemonGoTrainersCreate();
    Store store = pokemonGoStoreCreate();
    Pokedex pokedex = pokemonGoPokedexCreate(pokedex_file, evolution_file);
    WorldMap world_map = pokemonGoWorldMapCreate(location_file, pokedex);

    if (!trainers && !store && !world_map && !pokedex) {
        mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
        destroyPokemonGo(trainers, store, world_map, pokedex);
        return;
    }

    char command[MAX_LINE_SIZE];
    bool continue_loop = true;
    while (continue_loop) {
        fgets(command, MAX_LINE_SIZE, input);
        continue_loop = pokemonGoProcessCommand(command, trainers, store,
                                          world_map, pokedex, input, output);
    }
    destroyPokemonGo(trainers, store, world_map, pokedex);
}





int main(int argc, char** argv) {
    if (argc < 7 || argc > 11 || (argc%2 != 1) || !strcmp(argv[1], "-p") ||
            !strcmp(argv[3], "-e") || !strcmp(argv[5], "-l")) {
        mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
    }

    else if (argc == 9 && (strcmp(argv[7], "-i") &&
                            strcmp(argv[7], "-o"))) {
        mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
    }

    else if (argc == 11 && strcmp(argv[7], "-i") && strcmp(argv[9], "-o")) {
        mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
    }

    else {
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
