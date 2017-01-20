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

World::Pokestop::Pokestop() : item_vector(std::vector<Item*>()) {}

World::Pokestop::~Pokestop() {}

World::Pokestop::Pokestop(World::Pokestop & pokestop) {}

void World::Pokestop::addItem(std::string type, int level) {}

void World::Pokestop::Arrive(Trainer &trainer) {}

World::Pokestop::Item::Item(std::string &type, int level) {}

World::Pokestop::Item::~Item() {}

World::Pokestop::Item::Item(Item &item) {}

const std::string World::Pokestop::Item::getType(const Item &item) {}

const int World::Pokestop::Item::getLevel(const Item &item) {}



//TODO: Starbucks

World::Starbucks::Starbucks() {}

World::Starbucks::~Starbucks() {}

World::Starbucks::Starbucks(World::Starbucks &starbucks) {}

void World::Starbucks::Arrive(Trainer &trainer) {}

