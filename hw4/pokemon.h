#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <set>
#include <string>
#include "exceptions.h"

namespace mtm {
namespace pokemongo {

// Possible Pokemon types.
typedef enum {
  NORMAL = 0,
  ROCK = 1,
  BUG = 2,
  FAIRY = 3,
  GROUND = 4,
  GRASS = 5,
  WATER = 6,
  ICE = 7,
  GHOST = 8,
  POISON = 9,
  ELECTRIC = 10,
  FIRE = 11,
  FLYING = 12,
  PSYCHIC = 13,
} PokemonType;

class Pokemon {
  private:
    const double MAX_HP = 100.0;
    const double MIN_HP = 0.0;
    const double MIN_CP_BOOST = 1.0;

    double p_cp, p_hp;
    int p_level;
    std::string name;
    std::set<PokemonType> p_types;
    static double pokemonCompare(const Pokemon& first,
                                 const Pokemon& second);
    static std::string pokemonTypeToString(const
                                           mtm::pokemongo::PokemonType type);

  public:
  // Computes the default set of Pokemon types for a given species of Pokemons.
  //
  // @param species the species of the Pokemon.
  // @return the default set of types for the given species.
//  static std::set<PokemonType> GetDefaultTypes(const std::string& species); //TODO: remove comment

  // Constructs a new Pokemon with the specified data.
  //
  // @param species the species of the Pokemon.
  // @param types the types of the Pokemon.
  // @param cp the CP value of the Pokemon.
  // @param level the level of the Pokemon.
  // @throw PokemonInvalidArgsException if a non-positive level or CP value were
  //        passed, or if species is an empty string.
  Pokemon( std::string& species, //TODO: bring back the consts
           std::set<PokemonType>& types,
           double& cp,
           int& level);

  // Constructs a new Pokemon with the specified data and the default types for
  // its species.
  //
  // @param species the species of the Pokemon.
  // @param cp the CP value of the Pokemon.
  // @param level the level of the Pokemon.
  // @throw PokemonInvalidArgsException if a non-positive level or CP value were
  //        passed, or if species is an empty string.
//  Pokemon( std::string& species,  double& cp,  int& level); //TODO: remove comment
  
  // Copy constructor.
  //
  // @param pokemon the pokemon to copy.
  Pokemon( const Pokemon& pokemon);
  
  // Assignment operator.
  //
  // @param pokemon assignee.
  Pokemon& operator=(const Pokemon& pokemon);

  // Comparison operators for Pokemons. Pokemons are compared as described in
  // the exercise sheet.
  //
  // @param rhs the right-hand side operand.
  bool operator==(const Pokemon& rhs) const;
  bool operator!=(const Pokemon& rhs) const;
  bool operator<(const Pokemon& rhs) const;
  bool operator>(const Pokemon& rhs) const;
  bool operator<=(const Pokemon& rhs) const;
  bool operator>=(const Pokemon& rhs) const;
  
  // Prints the data of the Pokemon in the following format:
  //
  //     "<species> (<level>/<CP>/<HP>) <type1> <type2> ..."
  //
  // where the types are ordered by their numerical value.
  // e.g.
  //
  //     pikachu (3/5.5/87) NORMAL FIRE FLYING
  //
  // @param output the output stream to which the data is printed.
  // @param pokemon the pokemon whose data is printed.
  // @return the output stream to which the data is printed.
  friend std::ostream& operator<<(std::ostream& output, const Pokemon& pokemon);

  // Returns the level of the Pokemon.
  //
  // @return the level of the Pokemon.
  int Level() const;

  // "Hits" the given Pokemon by reducing its HP value by the hit power of this
  // Pokemon.
  //
  // @param the Pokemon to hit.
  // @return true iff the hitten Pokemon died (HP reached zero).
  bool Hit(Pokemon& victim);

  // Heals the Pokemon by increasing its HP to 100.
  void Heal();

  // Trains the Pokemon by multiplying its CP value by the given boost.
  //
  // @param boost the boost by which the CP value is multiplied.
  // @throw PokemonInvalidArgsException if boost is not bigger than 1.
  void Train(const double& boost);
};

std::ostream& operator<<(std::ostream& output, const Pokemon& pokemon);

}  // namespace pokemongo
}  // namespace mtm

#endif  // POKEMON_H
