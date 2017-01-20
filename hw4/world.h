#ifndef WORLD_H
#define WORLD_H

/**************************************
 *       Header files include         *
 **************************************/

#include <iostream>
#include <string>
#include "trainer.h"
#include "location.h"
#include "pokemon.h"
#include "k_graph.h"

/**************************************
 *               Using                *
 **************************************/

using std::string

/**************************************
 *       Namespace and Classes        *
 **************************************/

namespace mtm {
namespace pokemongo {

typedef int Direction;

static const int NORTH = 0;
static const int SOUTH = 1;
static const int EAST = 2;
static const int WEST = 3;

class World {
    class GYM : public Location {
    private:
        string name;
        Team team;
        Trainer* Leader;
        void switchLeader(Trainer leader);
    public:
        GYM(const string& name );
        ~GYM();
        void Arrive(Trainer& trainer) override ;
        void Leave(Trainer& trainer) override ;
    };


    class Pokestop : public Location {
            private:
            std::vector<const Item*> item_vector;
            friend class mtm::pokemongo::Trainer;
            class Item {
            private:
                std::string type;
                int level;
                friend class mtm::pokemongo::Trainer;
            public:
                Item(const std::string& type,const int level) const;
                ~Item();
                const Item(const Item& item) const;
                const std::string getType(const Item& item);
                const int getLevel(const Item& item);
            };

    public:
        Pokestop();
        ~Pokestop();
        void addItem(const Item& item);
        void Arrive(Trainer& trainer) override ;
    };

    class Starbucks : public Location {
    private:
        std::vector<Pokemon*> pokemon_vector;
    public:
        Starbucks();
        ~Starbucks();
        void Arrive(Trainer& trainer) override ;
    };

 public:
  // Constructs a new empty world.
  World();
  
  // A destructor.
  ~World();
  
/*   Input iterator. Scans a single line from the input stream. The line can be
   one of the following three options:

   (1) "GYM <gym_name>"
       e.g. "GYM taub"
       Adds a gym with the given name to the world.
   (2) "POKESTOP <pokestop_name> <item_type1> <item_level1> <item_type2> <item_level2> ..."
       e.g. "POKESTOP mikhlol POTION 10 CANDY 20 CANDY 13"
       Creates a Pokestop with the given name that contains the given items by
       order, and adds it to the world.
   (3) "STARBUCKS <starbucks_name> <pokemon_species1> <cp1> <level1> <pokemon_species2> <cp2> <level2> ..."
       e.g. "STARBUCKS shani pikachu 2.5 3 pikachu 1 2 charmander 3.45 4"
       Creates a starbucks with the given name that contains Pokemons with the
       given parameters by order, and adds it to the world. The Pokemons will
       have the default types.
   You can assume that none of the pieces of information (location name,
   Pokemon species, etc.) contains a space.

   @param input the input stream.
   @param world the world to which to add the locations.
   @return the input stream.
   @throw WorldInvalidInputLineException if the input line is not one of the
          three options, or one of the parameters is invalid (for example,
          negative CP value, etc.).
   @throw WorldLocationNameAlreadyUsed if there already exists a location with
          the given name in the world.*/
  friend std::istream& operator>>(std::istream& input, World& world);

  // Disable copy constructor.
  World(const World& world) = delete;

 private:
    static const DIRECTIONS = 4;
    KGraph<std::string, Location*, DIRECTIONS>  world_map;

};

std::istream& operator>>(std::istream& input, World& world);

}  // namespace pokemongo
}  // namespace mtm

#endif  // WORLD_H