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
define COMMAND_HANDLE(cmd_name, name, cmd_action, action, arg_counter, num) \
                                        (!strcmp(cmd_name, name)) \
                                        && (!strcmp(cmd_action, action)) &&   \
                                        (arg_counter!=num)




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

int static countArgsInCommand( char* command ) {
    int counter = 0;
    char* command_copy = stringCopy( command );

    char *current_word = strtok(command_copy, SPACE_DELIMITER);
    while (current_word) {
        current_word = strtok(NULL, SPACE_DELIMITER);
        counter++;
    }
    stringDestroy( command );
    return counter;
}

MtmErrorCode pokemonGoAddTrainer( char* command , Pokedex pokedex , Store store ,  int arg_counter , WorldMap world_map, Trainers trainers,File* output) {

    char* trainer_name =  strtok(NULL, SPACE_DELIMITER);
    char* start_point = strtok(NULL, SPACE_DELIMITER);
    int budget = strtok(NULL, SPACE_DELIMITER);
    sscanf(command, "%s %d %s" , trianer_name, budget, start_point);

    if ( (!trianer_name) || (!budget) || (!start_point) ) return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if ( !(pokemonTrainerIsValidArgs( trainer_name, start_point, budget)) ) return MTM_INVALID_ARGUMENT;
    PokemonTrainer trianer = pokemonTrainerCreate(trainer_name, start_point, budget);
    if ( trianer ) return MTM_OUT_OF_MEMORY;
    if ( trainersDoesTrainerExist(trainers,trianer) ) return MTM_TRAINER_NAME_ALREADY_EXISTS;
    if ( worldMapDoesLocationExist(world_map,location) ) return MTM_LOCATION_DOES_NOT_EXIST;
    PokemonTrainerResult result = pokemonTrainerGoHunt(PokemonTrainer trainer, char* location, WorldMap world_map, Pokedex pokedex, FILE* output);



    PokemonTrainerResult result = trainersAddTrainer(Trainers trainers,
            PokemonTrainer trainer);










    PokemonTrainer trainer = pokemonTrainerCreate(trainer_name, start_point, budget);
    if (trainer == NULL) return MTM_OUT_OF_MEMORY;
    PokemonTrainerResult result = pokemonTrainerGoHunt(trainer, start_point, world_map, pokedex, world_map);
    if (result);
    PokemonTrainerResult result = trainersAddTrainer(trainers, trainer);
    if (result);

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
        return pokemonGoPokemonHeal();
    if (COMMAND_HANDLE(section,"pokemon",action,"train",arg_counter, 4))
        return pokemonGoPokemonTrain();
    if (COMMAND_HANDLE(section,"report",action,"trainer",arg_counter, 3))
        return pokemonGoAddTrainerReport();
    if (COMMAND_HANDLE(section,"report",action,"locations",arg_counter,2))
        return pokemonGoWorldMapReport();
    if (COMMAND_HANDLE(section, "report",action, "stock", arg_counter, 5))
        return pokemonGoStoreReport();

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
