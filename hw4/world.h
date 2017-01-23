#ifndef WORLD_H
#define WORLD_H

/**************************************
 *       Header files include         *
 **************************************/


#include <iostream>
#include <string>
#include "location.h"
#include "trainer.h"
#include "pokemon.h"
#include "k_graph_mtm.h"
#include "item.h"
#include <sstream>
#include <vector>
#include <set>

/**************************************
 *               Using                *
 **************************************/

using std::string;
using mtm::pokemongo::Trainer;

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
        static const int LEADER_BONUS = 10;
		static const int WINNER_BONUS = 2;
		static const int LOSER_BONUS = -1;
		static const int LAST_TRAINER_IN_GYM = 1;
         Trainer* Leader;
         //TODO: add comments

        void switchLeader( Trainer& leader );
        void fightOutcome( Trainer& winner, Trainer& loser );
        bool makeFight( Trainer& first , Trainer& second );
        static bool compareByTeam( Trainer& first , Trainer& second );
        static void prepareToBattle( Trainer& first , Trainer& second );
//        static void updateBonusPoints(Trainer &trainer, int bonus);
        static void updateDeathResult(Trainer& first , Trainer& second ,
      		  bool first_died, bool second_died );
        Trainer* findNextLeader();
        Trainer* candidateForLeadership( Team team );
        Trainer* checkTeamSubstitute(Trainer* red_candidate ,
        Trainer* blue_candidate , Trainer* yellow_candidate );
        static Trainer* checkisOneTeamLeft(Trainer* red_candidate ,
        		Trainer* blue_candidate , Trainer* yellow_candidate );
        Trainer* checkBestOutOfTwoSubstitute(Trainer* red_candidate ,
        		Trainer* blue_candidate , Trainer* yellow_candidate );
        bool Fight( Trainer& first , Trainer& second );
    public:
        GYM();
        ~GYM();
        void Arrive(Trainer& trainer) override ;
        void Leave(Trainer& trainer) override ;


    };
    class Pokestop : public Location {
        private:
            std::vector<Item*> item_vector;
            friend class mtm::pokemongo::Trainer;

        public:
        Pokestop(std::vector<std::string> input_vector);
        ~Pokestop();
        void Arrive(Trainer& trainer) override ;
    };

    class Starbucks : public Location {
    private:
        std::vector<Pokemon*> pokemon_vector;
    public:
        Starbucks(std::vector<std::string> input_vector);
        ~Starbucks();
        void Arrive(Trainer& trainer) override ;
    };

public:
  // Constructs a new empty world.
  World();
  
  // A destructor.
  ~World();
  void Connect(std::string const& key_u, //TODO: remove this after inherit KGRAPH
               std::string const& key_v, int i_u, int i_v);
  
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
    static const int DIRECTIONS = 4;
    static const int LOCATION_TYPE = 0;
    static const int LOCATION_NAME = 1;
    static const int ITEM_TYPE = 0;
    static const int ITEM_LEVEL = 1;
    static const int POKEMON_NAME = 0;
    static const int POKEMON_CP = 1;
    static const int POKEMON_LEVEL = 2;

    KGraph<std::string, Location*, DIRECTIONS>  world_map;
    std::set<std::string> location_names;
    std::set<std::string> trainer_names;

    friend class PokemonGo;

    static std::vector<std::string> parseInput(std::istream& input);
    static void createLocationByType(std::string& location_name,
                                     std::string& location_type,
                                     std::vector<std::string> input_vector,
                                     World& world);

};

std::istream& operator>>(std::istream& input, World& world);

}  // namespace pokemongo
}  // namespace mtm

#endif  // WORLD_H
