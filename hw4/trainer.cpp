//
// Created by ohad on 14-Jan-17.
//

#include "trainer.h"


using mtm::pokemongo::Trainer;
using std::list;
using std::string;

Trainer::Trainer(const std::string& name, const Team& team) :
        t_level(INIT_LEVEL) {
    if (name == "")
        throw TrainerInvalidArgsException();

    t_name = string(name);
    t_pokemon_list = list<Pokemon>();
    t_team = team;
}


Pokemon& Trainer::GetStrongestPokemon() {
    if (t_pokemon_list.size() == 0)
        throw TrainerNoPokemonsFoundException();
    Pokemon strongest_pokemon = t_pokemon_list.front();

    list<Pokemon>::iterator pokemon_iter;
    for (pokemon_iter = t_pokemon_list.begin() ;
         pokemon_iter != t_pokemon_list.end(); ++pokemon_iter) {
        if (*pokemon_iter > strongest_pokemon)
            strongest_pokemon = *pokemon_iter;
    }

    return strongest_pokemon;
}


const Pokemon& Trainer::GetStrongestPokemon() const {
    if (t_pokemon_list.size() == 0)
        throw TrainerNoPokemonsFoundException();
    Pokemon strongest_pokemon = t_pokemon_list.front();

    list<Pokemon>::const_iterator pokemon_iter;
    for (pokemon_iter = t_pokemon_list.begin() ;
         pokemon_iter != t_pokemon_list.end(); ++pokemon_iter) {
        if (*pokemon_iter > strongest_pokemon)
            strongest_pokemon = *pokemon_iter;
    }

    return strongest_pokemon;
}


void Trainer::KillStrongestPokemon() {
    Pokemon strongest_pokemon = this->GetStrongestPokemon();
    list<Pokemon>::iterator pokemon_iter;
    for (pokemon_iter = t_pokemon_list.begin() ;
         pokemon_iter != t_pokemon_list.end(); ++pokemon_iter) {
        if (*pokemon_iter == strongest_pokemon) {
            t_pokemon_list.erase(pokemon_iter);
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
    return (*this == rhs && *this < rhs);
}

bool Trainer::operator>(const Trainer& rhs) const {
    return !(*this <= rhs);
}

bool Trainer::operator>=(const Trainer& rhs) const {
    return (*this == rhs && *this > rhs);
}


bool Trainer::IsAlly(const Trainer& trainer) const {
    return (this->t_team == trainer.t_team);
}


Team Trainer::GetTeam() const {
    return this->t_team;
}


bool Trainer::TryToCatch(Pokemon& pokemon) {
    return this->t_level >= pokemon.Level();
}


std::ostream& mtm::pokemongo::operator<<(std::ostream& output,
                                         const Trainer& trainer) {
    output << trainer.t_name ;
    output << " (" << trainer.t_level << ")" ;
    output << trainer.teamToString() << std::endl;

    list<Pokemon>::iterator it;
    for (it = trainer.t_pokemon_list.begin() ;
         it != trainer.t_pokemon_list.end(); ++it) {
        output << *it << std::endl;
    }

    return output;
}


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
            return false;
        }
        catch (TrainerNoPokemonsFoundException& e) {
            return true;
        }
    }
}