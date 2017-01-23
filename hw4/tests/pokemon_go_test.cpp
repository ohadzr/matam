/**************************************
 *       Header files include         *
 **************************************/

#include "../pokemon_go.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "test_utils.h"
#include "../trainer.h"
#include "../pokemon.h"


/**************************************
 *               Using                *
 **************************************/

using namespace mtm::pokemongo;
using namespace std;
using std::string;
using mtm::pokemongo::World;
using mtm::pokemongo::PokemonGo;

/**************************************
 *               Tests                *
 **************************************/

void SetUpWorld(World* world) {
  ifstream world_in("C:\\Users\\ohad\\ClionProjects\\matam\\hw4\\example_test\\world.in");
  string line;

  while (std::getline(world_in, line)) {
      istringstream line_stream(line);
      line_stream >> *world;
  }
}

bool TestPokemonGo() {
/********************************************************************
 *                          initialization                          *
 ********************************************************************/
/* -------------------      brand new world     ------------------- */

  World* earth = new World();
  SetUpWorld(earth);
  ostringstream output;

  earth->Connect("hong-kong", "rome", NORTH, SOUTH);
  earth->Connect("hong-kong", "tokyo", SOUTH, NORTH);
  earth->Connect("mumbai", "hong-kong", EAST, WEST);
  earth->Connect("mumbai", "berlin", NORTH, SOUTH);
  earth->Connect("mumbai", "alexandria", WEST, EAST);
  earth->Connect("shanghi", "mumbai", NORTH, SOUTH);
  earth->Connect("shanghi", "berlin", SOUTH, NORTH);
  earth->Connect("paris", "berlin", WEST, EAST);
  earth->Connect("paris", "london", SOUTH, NORTH);
  earth->Connect("paris", "madrid", NORTH, SOUTH);
  earth->Connect("berlin", "tazmania", NORTH, SOUTH);
  earth->Connect("tokyo", "saint-petesburg", SOUTH, NORTH);
  earth->Connect("london", "alexandria", EAST, WEST);

  PokemonGo pokemon_go( earth );

  ASSERT_NO_THROW( pokemon_go.AddTrainer("Ash", YELLOW, "mumbai") );
  ASSERT_NO_THROW( pokemon_go.AddTrainer("Sahar", RED, "paris") );
  ASSERT_THROW( PokemonGoLocationNotFoundException,
		  pokemon_go.AddTrainer("Sahar", RED, "akraba") );
  ASSERT_THROW( PokemonGoTrainerNameAlreadyUsedExcpetion,
		  pokemon_go.AddTrainer("Sahar", RED, "mumbai") );
  ASSERT_NO_THROW(pokemon_go.AddTrainer("Ohad", BLUE, "mumbai"));
  ASSERT_NO_THROW(pokemon_go.AddTrainer("Tomer", RED, "alexandria"));
  ASSERT_EQUAL( pokemon_go.WhereIs( "Ash" ), "mumbai" );
  ASSERT_EQUAL( pokemon_go.WhereIs( "Sahar" ), "paris" );
  ASSERT_THROW( PokemonGoTrainerNotFoundExcpetion, pokemon_go.WhereIs( "Gal" ));

  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 2 );
  ASSERT_EQUAL( pokemon_go.GetScore( YELLOW ), 11 );
  ASSERT_EQUAL( pokemon_go.GetScore( BLUE ), 10 );

  ASSERT_THROW( PokemonGoReachedDeadEndException,
		  pokemon_go.MoveTrainer( "Ash", EAST ));

  ASSERT_THROW( PokemonGoReachedDeadEndException,
		  pokemon_go.MoveTrainer( "Ohad", EAST ));
  ASSERT_THROW( PokemonGoReachedDeadEndException,
		  pokemon_go.MoveTrainer( "Ohad", WEST ));
  ASSERT_THROW( PokemonGoReachedDeadEndException,
		  pokemon_go.MoveTrainer( "Ohad", NORTH ));
  ASSERT_THROW( PokemonGoReachedDeadEndException,
		  pokemon_go.MoveTrainer( "Ohad", SOUTH ));

  ASSERT_NO_THROW( pokemon_go.MoveTrainer( "Ash", NORTH ) );
  ASSERT_EQUAL( pokemon_go.GetScore( YELLOW ), 1 );

  ASSERT_NO_THROW( pokemon_go.MoveTrainer( "Sahar", EAST ) );
  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 12 );

  ASSERT_NO_THROW( pokemon_go.MoveTrainer( "Tomer", WEST ) );
  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 12 );

  ASSERT_NO_THROW( pokemon_go.MoveTrainer( "Ash", SOUTH ) );
  ASSERT_NO_THROW( pokemon_go.MoveTrainer( "Ash", SOUTH ) );

  const vector<Trainer*>& trainers_in_berlin =
     pokemon_go.GetTrainersIn("berlin");
  ASSERT_EQUAL( trainers_in_berlin.size() , 3 );

  output << *trainers_in_berlin[0];
  output << *trainers_in_berlin[1];
  output << *trainers_in_berlin[2];

  ASSERT_EQUAL(output.str(),
               "Sahar 1 RED\n"
               "pikachu(1/2/88)\n"
               "Tomer 2 RED\n"
			   "pikachu(1/1/100)\n"
		  	   "Ash 2 YELLOW\n"
               "charmander(3/4/98) NORMAL BUG FAIRY ICE GHOST\n");

  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 11 );
  ASSERT_EQUAL( pokemon_go.GetScore( YELLOW ), 4 );

  ASSERT_NO_THROW( pokemon_go.MoveTrainer( "Tomer", NORTH ) );
  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 21 );

  const vector<Trainer*>& trainers_in_sydney =
     pokemon_go.GetTrainersIn("sydney");
  ASSERT_EQUAL( trainers_in_sydney.size() , 1 );

  const vector<Trainer*>& trainers_in_rome =
     pokemon_go.GetTrainersIn("rome");
  ASSERT_TRUE( trainers_in_rome.empty() );

  return true;
}


int main() {
    TestPokemonGo();

    return 0;
}
