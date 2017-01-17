/**************************************
 *       Header files include         *
 **************************************/

#include "pokemon.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::Pokemon;
using std::set;
using std::string;

/**************************************
 *        Interface Functions         *
 **************************************/

Pokemon::Pokemon( const string& species, const set<PokemonType>& types,
                  const double& cp, const int& level) :
                                            p_cp(cp) ,
                                            p_hp(MAX_HP),
                                            p_level(level),
                                            name(string(species)),
                                            p_types(set<PokemonType>(types)) {
    if ( cp <= 0 || level <= 0 || species == "" ) {
        /* invalid parameter */
        throw PokemonInvalidArgsException();
    }
}


Pokemon::Pokemon( const string& species,
                  const double& cp,
                  const int& level):  p_cp(cp) ,
                                      p_hp(MAX_HP),
                                      p_level(level),
                                      name(string(species)),
                                      p_types(GetDefaultTypes(species)) {
    if ( cp <= 0 || level <= 0 || species == "" ) {
        /* invalid parameter */
        throw PokemonInvalidArgsException();
    }
}


Pokemon::Pokemon( const Pokemon& pokemon) :   p_cp(pokemon.p_cp),
                                              p_hp(pokemon.p_hp),
                                              p_level(pokemon.p_level),
                                              name(string(pokemon.name)),
                                 p_types(set<PokemonType>(pokemon.p_types)) {
}

Pokemon& Pokemon::operator=(const Pokemon& pokemon) {
    if (this == &pokemon) {
        return *this;
    }

    name = string(pokemon.name);
    p_types = set<PokemonType>(pokemon.p_types);
    p_cp = pokemon.p_cp;
    p_hp = pokemon.p_hp;
    p_level = pokemon.p_level;

    return *this;
}

bool Pokemon::operator==(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result == 0;
}

bool Pokemon::operator!=(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result != 0;
}

bool Pokemon::operator<(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result < 0;
}

bool Pokemon::operator>(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result > 0;
}

bool Pokemon::operator>=(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result >= 0;
}

bool Pokemon::operator<=(const Pokemon& rhs) const {
    double result = pokemonCompare(*this, rhs);
    return result <= 0;
}

int Pokemon::Level() const {
    return p_level;
}

bool Pokemon::Hit(Pokemon& victim) {
    if( this == &victim ) return false;
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
    for (it = pokemon.p_types.begin() ; it != pokemon.p_types.end(); ++it) {
        output << pokemonTypeToString(*it) << " ";
    }

    output << std::endl;

    return output;
}

/**************************************
 *          Inner Functions           *
 **************************************/

/**
 * function convert given enum PokemonType to string.
 * @param type - the type to convert.
 * @return
 * the maching string.
 */
std::string Pokemon::pokemonTypeToString(const mtm::pokemongo::PokemonType
                                         type) {
    switch (type) {
        case NORMAL:
            return string("NORMAL");
        case ROCK:
            return string("ROCK");
        case BUG:
            return string("BUG");
        case FAIRY:
            return string("FAIRY");
        case GROUND:
            return string("GROUND");
        case GRASS:
            return string("GRASS");
        case WATER:
            return string("WATER");
        case ICE:
            return string("ICE");
        case GHOST:
            return string("GHOST");
        case POISON:
            return string("POISON");
        case ELECTRIC:
            return string("ELECTRIC");
        case FIRE:
            return string("FIRE");
        case FLYING:
            return string("FLYING");
        case PSYCHIC:
            return string("PSYCHIC");
        default:
            return string("");
    }
}
/**
 * function compare between two pokemons.
 * @param first - the first pokemon.
 * @param second - the second pokemon.
 * @return
 * possitive number if the first is bigger, negative if the second is bigger
 * and zero if pokemons equals by the defintion of the work.
 */
double Pokemon::pokemonCompare(const Pokemon& first,const Pokemon& second) {
    double first_hit_power,second_hit_power;
    first_hit_power = (first.p_cp) * (first.p_level);
    second_hit_power = (second.p_cp) * (second.p_level);
    double result = first_hit_power - second_hit_power;
    if (result != 0)
        return result;

    int sum_first=0, sum_second=0;
    set<PokemonType>::iterator it;

    for (it = first.p_types.begin() ; it != first.p_types.end(); ++it) {
        sum_first += (int) *it;
    }

    for (it = second.p_types.begin() ; it != second.p_types.end(); ++it) {
        sum_second += (int) *it;
    }

    return sum_first - sum_second;
}