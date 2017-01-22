/**************************************
 *       Header files include         *
 **************************************/

#include "pokemon_go.h"

/**************************************
 *               Using                *
 **************************************/
using mtm::pokemongo::World;
using mtm::pokemongo::PokemonGo;

/**************************************
 *       Namespace and Classes        *
 **************************************/


PokemonGo::PokemonGo(const World* world): p_world(world){}

PokemonGo::~PokemonGo(){}

void PokemonGo::AddTrainer(
    const std::string& name, const Team& team, const std::string& location){

}


void PokemonGo::MoveTrainer(const std::string& trainer_name, const Direction& dir);
std::string PokemonGo::WhereIs(const std::string& trainer_name);
const std::vector<Trainer*>& PokemonGo::GetTrainersIn(const std::string& location);
int PokemonGo::GetScore(const Team& team);
