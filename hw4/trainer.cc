
/**************************************
 *       Header files include         *
 **************************************/

#include "trainer.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::Trainer;
using mtm::pokemongo::Pokemon;
using mtm::pokemongo::Team;
using std::vector;
using std::string;

/**************************************
 *        Interface Functions         *
 **************************************/

Trainer::Trainer(const std::string& name, const Team& team) :
        t_name(string(name)), t_level(INIT_LEVEL),
		t_pokemon_list(std::vector<Pokemon>()),t_items(std::vector<Item*>()),
        t_team(team), fight_bonus(0) {
    if (name == "")
        throw TrainerInvalidArgsException();
}

Trainer::~Trainer() {}

Pokemon& Trainer::GetStrongestPokemon() {
    if (t_pokemon_list.size() == 0)
        throw TrainerNoPokemonsFoundException();
    Pokemon* strongest_pokemon = &(t_pokemon_list.front());
    for ( std::vector<Pokemon>::iterator it = t_pokemon_list.begin();
    		it != t_pokemon_list.end() ; ++it) {
        if (*it > *strongest_pokemon)
            *strongest_pokemon = *it;
    }
    return *strongest_pokemon;
}


const Pokemon& Trainer::GetStrongestPokemon() const {
    if (t_pokemon_list.size() == 0)
        throw TrainerNoPokemonsFoundException();
    if (t_pokemon_list.size() == 1)
        return t_pokemon_list[0];
    std::vector<Pokemon>::const_iterator it_strongest = t_pokemon_list.begin();
    for ( std::vector<Pokemon>::const_iterator it = t_pokemon_list.begin();
    		it != t_pokemon_list.end() ; ++it) {
        if (*it > *it_strongest){
            it_strongest = it;
        }
    }
    return (*it_strongest);
}


void Trainer::KillStrongestPokemon() {
    Pokemon strongest_pokemon = this->GetStrongestPokemon();
    for (std::vector<Pokemon>::iterator it = t_pokemon_list.begin() ;
         it != t_pokemon_list.end(); ++it) {
        if ( *it == strongest_pokemon) {
            //delete *it;
            t_pokemon_list.erase(it);
            return;
        }
    }
}

bool Trainer::operator==(const Trainer& rhs) const {
    return trainerCompare(*this, rhs, true);
}


bool Trainer::operator!=(const Trainer& rhs) const {
    return !(*this == rhs);
}

bool Trainer::operator<(const Trainer& rhs) const {
    return trainerCompare(*this, rhs, false);
}

bool Trainer::operator<=(const Trainer& rhs) const {
    return (*this == rhs || *this < rhs);
}

bool Trainer::operator>(const Trainer& rhs) const {
    return !(*this <= rhs);
}

bool Trainer::operator>=(const Trainer& rhs) const {
    return (*this == rhs || *this > rhs);
}


bool Trainer::IsAlly(const Trainer& trainer) const {
    return (this->t_team == trainer.t_team);
}


Team Trainer::GetTeam() const {
    return this->t_team;
}

int Trainer::GetLevel() const {
    return this->t_level;
}

void Trainer::updateLevel(int new_level) {
    t_level = new_level;
}

void Trainer::addItem(Item* item) {
    t_items.push_back(item);
}

mtm::pokemongo::Item* Trainer::getOldestItem() {
    if (t_items.size() == 0)
        return nullptr;
    Item* item = t_items.front();
    t_items.erase(t_items.begin());
    return item;
}


void Trainer::updateFightBonus(int bonus) {
    fight_bonus += bonus;
}

bool Trainer::TryToCatch(Pokemon& pokemon) {
    if ( t_level < pokemon.Level() )
        return false;
    t_pokemon_list.push_back(pokemon);
    return true;
}


std::ostream& mtm::pokemongo::operator<<(std::ostream& output,
                                         const Trainer& trainer) {
    output << trainer.t_name ;
    output << " (" << trainer.t_level << ") " ;
    output << trainer.teamToString() << std::endl;
    for (std::vector<Pokemon>::const_iterator it = trainer.t_pokemon_list.begin() ;
         it != trainer.t_pokemon_list.end(); ++it) {
        output << (*it) << std::endl;
    }
    return output;
}

/**
 * function convert team enum value into string.
 * @return
 * the maching string.
 */
std::string Trainer::teamToString() const {
    switch (this->t_team) {
        case BLUE:
            return string("BLUE");
        case YELLOW:
            return string("YELLOW");
        case RED:
            return string("RED");
        default:
            return string("");
    }
}

/**
 * function compare trainers.
 * @param first - the first trainer.
 * @param second - the second trainer.
 * @param check_equal - is true if user of this function want to check if
 * first == second, and false if user want to check another inequality operator.
 * @return
 * depend on check_equal value function return true if so and false if not.
 */
bool Trainer::trainerCompare(const Trainer& first,
                             const Trainer& second, bool check_equal) {
    try {
        Pokemon left_strength = first.GetStrongestPokemon();
        try {
            Pokemon right_strength = second.GetStrongestPokemon();
            if (check_equal)
                return left_strength == right_strength;
            else
                return left_strength < right_strength;
        }
        catch (TrainerNoPokemonsFoundException& e) {
            return false;
        }
    }
    catch (TrainerNoPokemonsFoundException& e) {
        try {
            second.GetStrongestPokemon();
            return !check_equal;
        }
        catch (TrainerNoPokemonsFoundException& e) {
            return check_equal;
        }
    }
}

std::string Trainer::GetName() const {
    return t_name;
}

int Trainer::GetFightBonus() const {
    return fight_bonus;
}
