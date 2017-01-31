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

PokemonGo::~PokemonGo(){
    delete p_world; //TODO: check that calls world defauld ~Dtor
}

void PokemonGo::AddTrainer(const std::string& name, const Team& team,
                           const std::string& location){
    try {
        Trainer* trainer = new Trainer(name, team);

        try {
            WhereIs(name);
            throw PokemonGoTrainerNameAlreadyUsedExcpetion();
        }
        catch (PokemonGoTrainerNotFoundExcpetion& e) {}

        if (!(p_world->location_names.find(location) !=
                p_world->location_names.end()))
            throw PokemonGoLocationNotFoundException();

        (*p_world)[location]->Arrive(*trainer);
    }
    catch (TrainerInvalidArgsException& e) {
        throw PokemonGoInvalidArgsException();
    }
}


void PokemonGo::MoveTrainer(const std::string& trainer_name,
                            const Direction& dir) {
    std::string location = WhereIs(trainer_name); //should throw if not found
    std::vector<Trainer*> trainers = GetTrainersIn(location);

    Trainer* trainer = nullptr;

    std::vector<Trainer*>::const_iterator trainer_it = trainers.begin();
    for (; trainer_it != trainers.end(); trainer_it++) {
        if ((*trainer_it)->GetName() == trainer_name) {
            trainer = *trainer_it;
        }
    }
    if (trainer == nullptr) throw PokemonGoTrainerNotFoundExcpetion();

    KGraph<std::string, Location*, World::DIRECTIONS>::const_iterator it =
            p_world->BeginAt(location);
    try {
        std::string next_location = *(it.Move(dir));
        (*p_world)[location]->Leave(*trainer);
        (*p_world)[next_location]->Arrive(*trainer);
    }
    catch (KGraphIteratorReachedEnd& e) {
        throw PokemonGoReachedDeadEndException();
    }
}


std::string PokemonGo::WhereIs(const std::string& trainer_name) {
    std::set<std::string>::iterator it = p_world->location_names.begin();
    for( ;it != p_world->location_names.end(); ++it ) {
        std::string location_name = *it;
        std::vector<Trainer*> trainers = GetTrainersIn(location_name);
        std::vector<Trainer*>::const_iterator trainer_it = trainers.begin();
        for (; trainer_it != trainers.end(); trainer_it++) {
            if ((*trainer_it)->GetName() == trainer_name)
                return location_name;
        }
    }
    throw PokemonGoTrainerNotFoundExcpetion();
}


const std::vector<Trainer*>& PokemonGo::GetTrainersIn(
                                    const std::string& location) {
    Location* real_location = (*p_world)[location];
    const std::vector<Trainer*>& trainers = real_location->GetTrainers();
    int a = trainers.size();
    if (a < 0) return trainers;
    return trainers;
}

int PokemonGo::GetScore(const Team& team) {
    int team_score = 0;
    // loop over all nodes
    std::set<std::string>::iterator it = p_world->location_names.begin();
    for( ;it != p_world->location_names.end(); ++it ) {
        std::string location_name = *it;
        std::vector<Trainer*> trainers = GetTrainersIn(location_name);
        std::vector<Trainer*>::const_iterator trainer_it = trainers.begin();
        for (; trainer_it != trainers.end(); trainer_it++) {
            Trainer trainer = **trainer_it;
            if (trainer.GetTeam() == team) {
                team_score += trainer.GetFightBonus();
                team_score += trainer.GetLevel();
            }
        }
    }

    return team_score;
}

