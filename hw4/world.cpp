//
// Created by ohad on 18-Jan-17.
//


#include "world.h"

using mtm::pokemongo::World
using mtm::pokemongo::Location


World::World() :
        world_map(KGraph<std::string, Location*, DIRECTIONS>(nullptr)) {
}

World::~World() {
}



//TODO: GYM
World::GYM::GYM(const string &name) {}

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
        if ((**it).getLevel() == trainer.t_level){

        }
    }
}

World::Pokestop::Item::Item(const std::string &type, const int level) {}

World::Pokestop::Item::~Item() {}

const World::Pokestop::Item::Item(const Item &item) {}

const std::string World::Pokestop::Item::getType(const Item &item) {}

const int World::Pokestop::Item::getLevel(const Item &item) {}



//TODO: Starbucks

World::Starbucks::Starbucks() {}

World::Starbucks::~Starbucks() {}

void World::Starbucks::Arrive(Trainer &trainer) {}

