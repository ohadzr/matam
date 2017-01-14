//
// Created by ohad on 13-Jan-17.
//

#include "pokemon.h"
using mtm::pokemongo::Pokemon;
using std::set;
using std::string;


Pokemon::Pokemon( string& species,  set<PokemonType>& types,
                  double& cp, int& level) :
                                            name(nullptr) ,
                                            p_types(nullptr) ,
                                            p_cp(cp) ,
                                            p_level(level) {
    if ( cp <= 0 || level <= 0 || species == "" ) {
        // invalid parameter
        throw PokemonInvalidArgsException();
    }

    this->name = string(species);
    this->p_types = set(types);

}


Pokemon::Pokemon( string& species,
                  double& cp,
                  int& level): name(nullptr) , p_types(nullptr) ,
                              p_cp(cp) , p_level(level) {
    if ( cp <= 0 || level <= 0 || species == "" ) {
        // invalid parameter
        throw PokemonInvalidArgsException();
    }

    this->name = string(species);
    this->p_types = set(GetDefaultTypes(species));
}


Pokemon::Pokemon( const Pokemon& pokemon) :   name(nullptr),
                                              p_types(nullptr),
                                              p_cp(pokemon.p_cp),
                                              p_level(pokemon.p_level) {
    this->name = string(pokemon.name);
    this->p_types = set(pokemon.p_types);

}

Pokemon& operator=(const Pokemon& pokemon) {
    Pokemon new_pokemon = Pokemon(pokemon);
    return new_pokemon;
}



