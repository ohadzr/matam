/**************************************
 *       Header files include         *
 **************************************/

#include "world.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::World
using mtm::pokemongo::Location

/**************************************
 *        Interface Functions         *
 **************************************/

World::World() :
        world_map(KGraph<std::string, Location*, DIRECTIONS>(nullptr)) {
}

World::~World() {
}

World::GYM(const string& name) {

}

World::GYM::~GYM(){}

void World::GYM::switchLeader(Trainer leader) {}

void World::GYM::Arrive(Trainer &trainer) {}

void World::GYM::Leave(Trainer &trainer) {}





//TODO: Pokestop

World::Pokestop::Pokestop() : item_vector(std::vector<const Item*>()) {
}

World::Pokestop::~Pokestop() {
}

void World::Pokestop::addItem(const Item& item) {
    item_vector.push_back(&item);
}

void World::Pokestop::Arrive(Trainer &trainer) {
    for (std::vector<const Item*>::const_iterator it = item_vector.begin() ;
         it != item_vector.end(); ++it) {
        if ((**it).getLevel() <= trainer.GetLevel()){
            trainer.addItem(**it);
            item_vector.erase(it); //TODO: PROBLEM?? does this delete trainer's item?
            break;
        }
    }
}

World::Pokestop::Item::Item(const std::string &type, const int level) :
        type(string(type)), level(level){
}

World::Pokestop::Item::~Item() {}

const World::Pokestop::Item::Item(const Item &item) :
        type(string(item.type)), level(item.level){
}

const std::string World::Pokestop::Item::getType(const Item &item) {
    return item.type;
}

const int World::Pokestop::Item::getLevel(const Item &item) {
    return item.level;
}



//TODO: Starbucks

World::Starbucks::Starbucks() : pokemon_vector(std::vector<Pokemon*>()){}

World::Starbucks::~Starbucks() {}

void World::Starbucks::Arrive(Trainer &trainer) {
    std::vector<Pokemon*>::iterator it = pokemon_vector.begin();
    if (trainer.TryToCatch(**it)) {
        pokemon_vector.erase(it); //TODO: PROBLEM?? - check if this delete the pokemon the trainer caught - maybe send a copy of the pokemon (above)?
    }
}

