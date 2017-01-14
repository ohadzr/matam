//
// Created by ohad on 14-Jan-17.
//

#include "trainer.h"




using mtm::pokemongo::Trainer;
using std::list;

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