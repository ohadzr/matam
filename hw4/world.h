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

class World : public KGraph<std::string, Location*, 4>{
    class GYM : public Location {
    private:
        static const int LEADER_BONUS = 10;
		static const int WINNER_BONUS = 2;
		static const int LOSER_BONUS = -1;
		static const int LAST_TRAINER_IN_GYM = 1;
        Trainer* Leader;

        /**
         * function canculate the winner's new level after battle.
         * @param winner_old_level - the level before the battle.
         * @param loser_old_level - the level before the battle.
         * @return
         * winner's new level after battle.
         */
        int winnerNewLevel(int winner_old_level, int loser_old_level);
        /**
         * function calculate pokemon's new boost after eat candy.
         * @param pokmon_old_level - pokemon's old level.
         * @return
         * boost points.
         */
        double pokemonBoost(int pokmon_old_level );
        /**
         * function update the new leader of the given GYM.
         * @param leader - the new leader.
         */
        void switchLeader( Trainer& leader );
        /**
         * function update the winner's level and suitable bonus points each.
         * @param winner - the winner of fight.
         * @param loser - the trainer who lost the fight.
         */
        void fightOutcome( Trainer& winner, Trainer& loser );
        /**
         * function holds the fight between 2 given trainers.
         * @param first - the first trainer.
         * @param second - the second trainer.
         * @return
         * true if the second trainer won the fight, false else.
         */
        bool makeFight( Trainer& first , Trainer& second );
        /**
         * function compare wich trainer is stronger based on thier teams.
         * @param first - the first trainer.
         * @param second - the second trainer.
         * @return
         * true if the second trainer won the fight, false else.
         */
        static bool compareByTeam( Trainer& first , Trainer& second );
        /**
         * function make each trainer use his oldest item and update the use
         * effects on HP /CP of the strongest pokemon. assert both trainers has
         * at least one pokemon.
         * @param first - the first trainer.
         * @param second - the second trainer.
         */
         void prepareToBattle( Trainer& first , Trainer& second );
        /**
         * function update teams bonus points.
         * @param trainer - the triner's whom his bonuse is updated in team.
         * @param bonus - the size of bonus added to team ( can be negative).
         */
       //static void updateBonusPoints(Trainer &trainer, int bonus);
        /**
         * function delete pokemon who died over a fight from trainer, r.i.p.
         * @param first - the first trainer.
         * @param second - the second trainer.
         * @param first_died - true if first's strongest pokemon died.
         * @param second_died  true if second's strongest pokemon died.
         */
        static void updateDeathResult(Trainer& first , Trainer& second ,
      		  bool first_died, bool second_died );
        /**
         * function detect the best substatite for the GYM from it's trainers.
         * @return
         * nullptr if no one was found worthy to posses such power,
         * or the selected trainer.
         */
        Trainer* findNextLeader();
        /**
         * function serch for the best option from a given team to replace
         * leader.
         * @param team - the team being checked.
         * @return
         * nullptr if no one was found worthy to posses such power,
         * or the selected trainer.
         */
        Trainer* candidateForLeadership( Team team );
        /**
         * function check witch one of the candidate is a suitable replacer.
         * @param red_candidate - the red team candidate.
         * @param blue_candidate - the blue team candidate.
         * @param yellow_candidate - the yellow team candidate.
         * @return
         * nullptr if no one was found worthy to posses such power,
         * or the selected trainer.
         */
        Trainer* checkTeamSubstitute(Trainer* red_candidate ,
        Trainer* blue_candidate , Trainer* yellow_candidate );
        /**
         * function check if there is only one team members in GYM.
         * @param red_candidate - the red team candidate.
         * @param blue_candidate - the blue team candidate.
         * @param yellow_candidate - the yellow team candidate.
         * @return
         * if there more then one team return nullptr, else reaturn the best
         * replacer.
         */
        static Trainer* checkisOneTeamLeft(Trainer* red_candidate ,
        		Trainer* blue_candidate , Trainer* yellow_candidate );
        /**
         * function check if there are two teams members in GYM.
         * @param red_candidate - the red team candidate.
         * @param blue_candidate - the blue team candidate.
         * @param yellow_candidate - the yellow team candidate.
         * @return
         * the best trainer out of them both, although both must be great
         * people , nullptr else.
         */
        Trainer* checkBestOutOfTwoSubstitute(Trainer* red_candidate ,
        		Trainer* blue_candidate , Trainer* yellow_candidate );
        /**
         * function preform a fight between two trainers, after asserting they
         * have at least one pokemon and both prepared for fight.
         * @param first - the first trainer.
         * @param second - the second trainer.
         * @return
         * true if the second trainer won the fight, false else.
         */
        bool Fight( Trainer& first , Trainer& second );
    public:
        /**
         * defult constructor of GYM.
         */
        GYM();
        /**
         * defult destructor of GYM.
         */
        ~GYM();
        /**
         * override location function of trainer arraive to GYM.
         * operate a few actions such as add trainer to GYM's trainers list,
         * and update GYM's leader if neccery.
         * @param trainer - the trainer to be added to GYM.
         */
        void Arrive(Trainer& trainer) override ;
        /**
         * override location function of trainer leave from GYM.
         * operate a few actions such as remove trainer from GYM's trainers
         * list, and update GYM's leader if neccery.
         * @param trainer - the trainer to be removed from GYM.
         */
        void Leave(Trainer& trainer) override ;
    };

    class Pokestop : public Location {
        private:
            std::vector<Item*> item_vector = std::vector<Item*>();
            friend class mtm::pokemongo::Trainer;

        public:
        /**
         * constructor of Pokestop.
         * @param input_vector - the command to Intentionlly build a Pokestop,
         * with parameters.
         */
        Pokestop(std::vector<std::string>& input_vector);
        /**
         * destructor of Pokestop.
         */
        ~Pokestop();
        /**
          * override location function of trainer arraive to Pokestop.
          * operate a few actions such as add trainer to Pokestop's trainers
          * list, and if found item trainer can get give it to him.
          * @param trainer - the trainer to be added to Pokestop.
          */
        void Arrive(Trainer& trainer) override ;
    };

    class Starbucks : public Location {
    private:
        std::vector<Pokemon*> pokemon_vector;
    public:
        /**
         * constructor of Starbucks.
         * @param input_vector - the command to Intentionlly build a Starbucks,
         * with parameters.
         */
        Starbucks(std::vector<std::string>& input_vector);
        /**
         * destructor for Starbucks.
         */
        ~Starbucks();
        /**
          * override location function of trainer arraive to Starbucks.
          * operate a few actions such as add trainer to Starbucks's trainers
          * list, and try to catch a pokemon if exist.
          * @param trainer - the trainer to be added to Starbucks.
          */
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

  void Insert(string location_name, Location* new_location);
  void Remove(string location_name);

private:
    static const int DIRECTIONS = 4;
    static const int LOCATION_TYPE = 0;
    static const int LOCATION_NAME = 1;
    static const int ITEM_TYPE = 0;
    static const int ITEM_LEVEL = 1;
    static const int POKEMON_NAME = 0;
    static const int POKEMON_CP = 1;
    static const int POKEMON_LEVEL = 2;
    static const string STRING_TO_INT = "0123456789";
    static const string STRING_TO_DOUBLE = "0123456789.";

    std::set<std::string> location_names;

    friend class PokemonGo;

    /**
     * function refine given input in strings vector and take care of cration
     * of sutible elemnts instructed.
     * @param location_name - the new location name, not an empty string.
     * @param location_type - GYM, Starbucks or Pokestop.
     * @param input_vector - a string vector with filterd command line.
     * @param world - the world to initialize.
     */
    void createLocationByType(std::string& location_name,
                                     std::string& location_type,
                                     std::vector<std::string> input_vector,
                                     World& world);
    /**
     * function parse lines from input into string vector.
     * @param input - input stream.
     * @return
     * the string vector. //TODO: shoudent be reprence or a pointer?
     */
    static std::vector<std::string> parseInput(std::istream& input);

};
/**
 * function execute operator input read.
 * @param input - input stream.
 * @param world - the world to initialize.
 * @return
 * input stream.
 */
std::istream& operator>>(std::istream& input, World& world);

}  // namespace pokemongo
}  // namespace mtm

#endif  // WORLD_H
