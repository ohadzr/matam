/**************************************
 *       Header files include         *
 **************************************/

#include "../pokemon_go.h"
#include <fstream>
#include "test_utils.h"



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
  ifstream world_in("tests/sahar_world_test.in");
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

  ASSERT_NO_THROW(earth->Connect("hong-kong", "rome", SOUTH, NORTH));
  ASSERT_NO_THROW(earth->Connect("hong-kong", "tokyo", NORTH, SOUTH));
  ASSERT_NO_THROW(earth->Connect("mumbai", "hong-kong", WEST, EAST));
  ASSERT_NO_THROW(earth->Connect("mumbai", "berlin", SOUTH, NORTH ));
  ASSERT_NO_THROW(earth->Connect("berlin", "alexandria", EAST, WEST));
  ASSERT_NO_THROW(earth->Connect("shanghai", "mumbai", SOUTH, NORTH));
  ASSERT_NO_THROW(earth->Connect("paris", "berlin", EAST, WEST));
  ASSERT_NO_THROW(earth->Connect("paris", "london", NORTH, SOUTH));
  ASSERT_NO_THROW(earth->Connect("paris", "madrid", SOUTH, NORTH));
  ASSERT_NO_THROW(earth->Connect("berlin", "tazmania", SOUTH, NORTH));
  ASSERT_NO_THROW(earth->Connect("tokyo", "saint-petersburg", NORTH, SOUTH));
  ASSERT_NO_THROW(earth->Connect("london", "alexandria", WEST, EAST));

  PokemonGo pokemon_go( earth );

  ASSERT_NO_THROW( pokemon_go.AddTrainer("Ash", YELLOW, "mumbai") );
  ASSERT_NO_THROW( pokemon_go.AddTrainer("Sahar", RED, "paris") );
  ASSERT_THROW( PokemonGoLocationNotFoundException,
		  pokemon_go.AddTrainer("Sahar2", RED, "akraba") );
  ASSERT_THROW( PokemonGoTrainerNameAlreadyUsedExcpetion,
		  pokemon_go.AddTrainer("Sahar", RED, "mumbai") );
  ASSERT_NO_THROW(pokemon_go.AddTrainer("Ohad", BLUE, "sydney"));
  ASSERT_NO_THROW(pokemon_go.AddTrainer("Tomer", RED, "alexandria"));
  ASSERT_EQUAL( pokemon_go.WhereIs( "Ash" ), "mumbai" );
  ASSERT_EQUAL( pokemon_go.WhereIs( "Sahar" ), "paris" );
  ASSERT_THROW( PokemonGoTrainerNotFoundExcpetion, pokemon_go.WhereIs( "Gal" ));

  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 2 );
  ASSERT_EQUAL( pokemon_go.GetScore( YELLOW ), 11 );
  ASSERT_EQUAL( pokemon_go.GetScore( BLUE ), 11 );

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

  const vector<Trainer*>& trainers_in_rome =
          pokemon_go.GetTrainersIn("rome");
  ASSERT_TRUE( trainers_in_rome.empty() );

  earth->Remove("paris");

  ASSERT_THROW( PokemonGoReachedDeadEndException,
                pokemon_go.MoveTrainer( "Sahar", EAST ) );

  output << *(trainers_in_berlin[0]);
  output << *(trainers_in_berlin[1]);
  output << *(trainers_in_berlin[2]);

  ASSERT_EQUAL(output.str(),
               "Sahar (1) RED\n"
               "pikachu(1/2/97)\n"
               "Tomer (1) RED\n"
			   "pikachu(1/1/100)\n"
		  	   "Ash (2) YELLOW\n"
               "charmander(1/3/98)\n"); //TODO: replace this with real types!!!

  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 1 );
  ASSERT_EQUAL( pokemon_go.GetScore( YELLOW ), 14 );

  ASSERT_NO_THROW( pokemon_go.MoveTrainer( "Tomer", NORTH ) );
  ASSERT_EQUAL( pokemon_go.GetScore( RED ), 11 );

  const vector<Trainer*>& trainers_in_sydney =
     pokemon_go.GetTrainersIn("sydney");
  ASSERT_EQUAL( trainers_in_sydney.size() , 1 );


  earth->Remove("sydney");
  ASSERT_NO_THROW(pokemon_go.AddTrainer("Ohad", BLUE, "rome"));

  return true;
}


int main() {
    RUN_TEST(TestPokemonGo);
    return 0;
}
