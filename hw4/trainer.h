#ifndef TRAINER_H
#define TRAINER_H

/**************************************
 *       Header files include         *
 **************************************/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "pokemon.h"
#include "exceptions.h"
#include "item.h"


/**************************************
 *       Namespace and Classes        *
 **************************************/

namespace mtm {
namespace pokemongo {

// Teams in game.
typedef enum {
  BLUE,
  YELLOW,
  RED,
} Team;

class Trainer {
  private:
    const int INIT_LEVEL = 1;

    std::string t_name;
    int t_level;
    std::vector<Pokemon*> t_pokemon_list;
    std::vector<Item*> t_items;
    Team t_team;
    int fight_bonus;
    std::string teamToString() const;
    static bool trainerCompare(const Trainer& first,
                                 const Trainer& second, bool check_equal);


  public:
/*   Constructs a new trainer with the given name and team.

   @param name the name of the trainer.
   @param team the team to which the trainer belongs.
   @throw TrainerInvalidArgsException if name is an empty string.
   */
  Trainer(const std::string& name, const Team& team);

    /**
     * destructor of trainer, free all memory allocations.
     */
    ~Trainer();

/**   Returns a reference to the strongest Pokemon the trainer owns. Strongest
   Pokemon is determined using the comparison operators provided by the class
   Pokemon. If two Pokemons are of equal strength, the function returns the
   one that was caught earlier by the trainer.

   @return the strongest pokemon.
   @throw TrainerNoPokemonsException if trainer has no Pokemons.*/
  Pokemon& GetStrongestPokemon();
  const Pokemon& GetStrongestPokemon() const;

/**   Kills the strongest Pokemon. Removes the Pokemon that is returned from
   GetStrongestPokemon() from the collection of Pokemons owned by the trainer.

   @throw TrainerNoPokemonsException if trainer has no Pokemons.*/
  void KillStrongestPokemon();

/**   Comparison operators for trainers. Trainers are compared as described in
   the exercise sheet.

   @param rhs the right-hand side operand.*/
  bool operator==(const Trainer& rhs) const;
  bool operator!=(const Trainer& rhs) const;
  bool operator<(const Trainer& rhs) const;
  bool operator>(const Trainer& rhs) const;
  bool operator<=(const Trainer& rhs) const;
  bool operator>=(const Trainer& rhs) const;

/**   Checks whether a given trainer is in the same team as this trainer.

   @param trainer
   @return true iff trainer (argument) and this trainer belong to the same
           team.*/
  bool IsAlly(const Trainer& trainer) const;

/**   Returns the team to which the trainer belongs.

   @return the team to which the trainer belongs.*/
    Team GetTeam() const;

/**   Returns the level of the trainer

   @return the level of the trainer.*/
    int GetLevel() const; //TODO: is this allowed? (not in basic file)

    std::string GetName() const; //TODO: is this allowed? (not in basic file)

    int GetFightBonus() const; //TODO: is this allowed? (not in basic file)

    void updateLevel(int new_level); //TODO: is this allowed? (not in basic file)



/**
 *  Add an item at the end of the trainer's item list
 *
 * @param item - The item to add
 */
    void addItem(Item& item); //TODO: is this allowed? (not in basic file)




/**
 * Find the oldest item the trainer has
 * @return The oldest item the trainer has
 */
    Item* getOldestItem();//TODO: is this allowed? (not in basic file)

/**
 * Find the oldest item the trainer has
 * @return The oldest item the trainer has
 */
    void updateFightBonus(int bonus);//TODO: is this allowed? (not in basic file)



/**   Tries to catch a Pokemon.

   @param pokemon the Pokemon the trainer wishes to catch.
   @return true if the attempt succeeded.*/
  bool TryToCatch(Pokemon& pokemon);

/**   Prints the data of the trainer in the following format:

       "<name> (<level>) <team>\n
        <pokemon1>\n
        <pokemon2>\n
        ..."

   where the Pokemons are ordered from least recently caught to most recently.
   e.g.

       ash (4) YELLOW
       pikachu (3/5.5/87) NORMAL FIRE FLYING
       charmander (2/2.5/100) NORMAL BUG
       pikachu (7/6.5/56) FIRE


   @param output the output stream to which the data is printed.
   @param pokemon the pokemon whose data is printed.
   @return the output stream to which the data is printed.*/
  friend std::ostream& operator<<(std::ostream& output, const Trainer& trainer);
};

std::ostream& operator<<(std::ostream& output, const Trainer& trainer);

}  // namespace mtm
}  // namespace pokemongo

#endif  // TRAINER_H
