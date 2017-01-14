//
// Created by ohad on 13-Jan-17.
//

#include "pokemon.h"

using namespace mtm::pokemongo;
using std::set;
using std::string;


Pokemon::Pokemon( string& species,  set<PokemonType>& types,
                  double& cp, int& level) :
                                            name(nullptr) ,
                                            p_types(nullptr) ,
                                            p_cp(cp) ,
                                            p_hp(MAX_HP),
                                            p_level(level) {
    if ( cp <= 0 || level <= 0 || species == "" ) {
        // invalid parameter
        throw PokemonInvalidArgsException();
    }

    name = string(species);
    p_types = set(types);

}


Pokemon::Pokemon( string& species,
                  double& cp,
                  int& level): name(nullptr) , p_types(nullptr) ,
                               p_hp(MAX_HP), p_cp(cp) , p_level(level) {
    if ( cp <= 0 || level <= 0 || species == "" ) {
        // invalid parameter
        throw PokemonInvalidArgsException();
    }

    name = string(species);
    p_types = set(GetDefaultTypes(species));

}


Pokemon::Pokemon( const Pokemon& pokemon) :   name(nullptr),
                                              p_types(nullptr),
                                              p_cp(pokemon.p_cp),
                                              p_hp(MAX_HP),
                                              p_level(pokemon.p_level) {
    name = string(pokemon.name);
    p_types = set(pokemon.p_types);

}

Pokemon& operator=(const Pokemon& pokemon) {
    Pokemon new_pokemon = Pokemon(pokemon);
    return new_pokemon;
}

bool operator==(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    //double result = (this->p_cp * this->p_level) - (rhs.p_cp * rhs.p_level); TODO: delete
    return result == 0;
}


bool operator!=(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result != 0;
}

bool operator<(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result < 0;
}

bool operator>(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result > 0;
}

bool operator>=(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result >= 0;
}

bool operator<=(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result <= 0;
}


//TODO: add explanation
/**
 *
 * @param first
 * @param second
 * @return
 */
double Pokemon::pokemonCompare(const Pokemon& first,
                               const Pokemon& second) {
    double first_hit_power,second_hit_power;
    first_hit_power = (first.p_cp) * (first.p_level);
    second_hit_power = (second.p_cp) * (second.p_level);

    return first_hit_power - second_hit_power;
}


int Pokemon::Level() const {
    return p_level;
}

bool Pokemon::Hit(Pokemon& victim) {
    double hit_power = p_cp * p_level;
    victim.p_hp -= hit_power;
    if (victim.p_hp <= MIN_HP) {
        victim.p_hp = MIN_HP;
        return true;
    }
    return false;
}

void Pokemon::Heal() {
    p_hp = MAX_HP;
}

void Pokemon::Train(const double& boost) {
    if (boost <= MIN_CP_BOOST ) {
        throw PokemonInvalidArgsException();
    }

    p_cp *= boost;
}


std::ostream& mtm::pokemongo::operator<<(std::ostream& output,
                                         const Pokemon& pokemon) {
    output << pokemon.name ;
    output << " (" << pokemon.p_level << "/" << pokemon.p_cp << "/";
    output << pokemon.p_hp << ") ";

    set<PokemonType>::iterator it;
    for (it = pokemon.p_types.begin() ; it != pokemon.p_types.end(); ++it) { //TODO: check if print types by enum order
        output << *it << " ";                                               //TODO: check if last space is valid
    }

    output << std::endl;

    return output;
}