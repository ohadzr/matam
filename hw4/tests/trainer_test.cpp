/**************************************
 *       Header files include         *
 **************************************/

#include "../pokemon.h"
#include "../trainer.h"
#include "test_utils.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::Pokemon;
using mtm::pokemongo::PokemonType;
using mtm::pokemongo::Trainer;
using mtm::pokemongo::Team;
using mtm::pokemongo::Item;

using std::set;
using std::vector;
using std::string;

/**************************************
 *               Tests                *
 **************************************/

bool trainerTestCtor() {
    /********************************************************************
     *                              tests                               *
     ********************************************************************/

    ASSERT_NO_THROW(Trainer("Ash",Team::BLUE));
    ASSERT_NO_THROW(Trainer("Misti",Team::RED));
    ASSERT_NO_THROW(Trainer("Ohad",Team::YELLOW));
    ASSERT_NO_THROW(Trainer("Sahar",Team::YELLOW));

    ASSERT_THROW(mtm::pokemongo::TrainerInvalidArgsException,
    		Trainer("",Team::YELLOW));

    return true;
}

bool trainerTestGetStrongestPokemon() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types1 = set<PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);

    Pokemon pikachu = Pokemon("Pikachu",types1,6,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types2 = set<PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::FIRE);
    types2.insert(mtm::pokemongo::PokemonType::NORMAL);

    Pokemon charmander = Pokemon("Charmander",types2,1,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types3 = set<PokemonType>();
    types3.insert(mtm::pokemongo::PokemonType::PSYCHIC);

    Pokemon togopi = Pokemon("Togopi",types3,4,1);

    /* --------------------  initialize trainers  --------------------- */

    Trainer ash = Trainer("Ash",Team::BLUE);
    Trainer misti = Trainer("Misti",Team::YELLOW);
    Trainer sahar = Trainer("sahar",Team::RED);
    /********************************************************************
     *                              tests                               *
     ********************************************************************/

    ASSERT_TRUE(ash.TryToCatch(pikachu));
    ASSERT_TRUE(ash.TryToCatch(charmander));
    ASSERT_TRUE(misti.TryToCatch(togopi));

    ASSERT_TRUE(ash.GetStrongestPokemon()== pikachu);
    ASSERT_TRUE(misti.GetStrongestPokemon()== togopi);
    ASSERT_THROW(mtm::pokemongo::TrainerNoPokemonsFoundException,
    		sahar.GetStrongestPokemon());

    return true;
}

bool trainerTestKillStrongestPokemon() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types1 = set<PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);

    Pokemon pikachu = Pokemon("Pikachu",types1,6,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types2 = set<PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::FIRE);
    types2.insert(mtm::pokemongo::PokemonType::NORMAL);

    Pokemon charmander = Pokemon("Charmander",types2,1,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types3 = set<PokemonType>();
    types3.insert(mtm::pokemongo::PokemonType::PSYCHIC);

    Pokemon togopi = Pokemon("Togopi",types3,4,1);

    /* --------------------  initialize trainers  --------------------- */

    Trainer ash = Trainer("Ash",Team::BLUE);
    Trainer misti = Trainer("Misti",Team::YELLOW);
    ash.TryToCatch(pikachu);
    ash.TryToCatch(charmander);
    misti.TryToCatch(togopi);

    /********************************************************************
     *                              tests                               *
     ********************************************************************/

    ash.KillStrongestPokemon();
    misti.KillStrongestPokemon();

    ASSERT_THROW(mtm::pokemongo::TrainerNoPokemonsFoundException,
    		misti.GetStrongestPokemon());
    ASSERT_TRUE(ash.GetStrongestPokemon()== charmander);

    return true;
}

bool trainerTestOperators() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types1 = set<PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);

    Pokemon pikachu = Pokemon("Pikachu",types1,6,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types2 = set<PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::FIRE);
    types2.insert(mtm::pokemongo::PokemonType::NORMAL);

    Pokemon charmander = Pokemon("Charmander",types2,1,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types3 = set<PokemonType>();
    types3.insert(mtm::pokemongo::PokemonType::PSYCHIC);

    Pokemon togopi = Pokemon("Togopi",types3,4,1);

    /* --------------------  initialize trainers  --------------------- */

    Trainer ash = Trainer("Ash",Team::BLUE);
    Trainer misti = Trainer("Misti",Team::YELLOW);
    Trainer ohad = Trainer("Ohad",Team::YELLOW);
    Trainer sahar = Trainer("Sahar",Team::RED);

    ash.TryToCatch(pikachu);
    ash.TryToCatch(charmander);
    misti.TryToCatch(togopi);

    /********************************************************************
     *                              tests                               *
     ********************************************************************/

    ASSERT_TRUE( sahar == ohad );
    ASSERT_TRUE( ash != misti );
    ASSERT_TRUE( ash > misti );
    ASSERT_TRUE( misti > ohad );
    ASSERT_TRUE( misti >= ohad );
    ASSERT_TRUE( sahar < ash );
    ASSERT_TRUE( sahar <= ash );


    misti.KillStrongestPokemon();
    ASSERT_TRUE( sahar == misti );

    return true;
}

bool trainerTestIsAlly() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types1 = set<PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);

    Pokemon pikachu = Pokemon("Pikachu",types1,6,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types2 = set<PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::PSYCHIC);

    Pokemon togopi = Pokemon("Togopi",types2,4,1);

    /* --------------------  initialize trainers  --------------------- */

    Trainer ash = Trainer("Ash",Team::BLUE);
    Trainer misti = Trainer("Misti",Team::YELLOW);
    Trainer ohad = Trainer("Ohad",Team::YELLOW);
    Trainer sahar = Trainer("Sahar",Team::RED);

    /********************************************************************
     *                              tests                               *
     ********************************************************************/

    ASSERT_TRUE( misti.IsAlly(ohad) );
    ASSERT_TRUE( !ash.IsAlly(ohad) );
    ASSERT_TRUE( !sahar.IsAlly(ohad) );
    ASSERT_TRUE( !misti.IsAlly(ash) );


    return true;
}

bool trainerTestGetTeam() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types1 = set<PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);

    Pokemon pikachu = Pokemon("Pikachu",types1,6,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types2 = set<PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::PSYCHIC);

    Pokemon togopi = Pokemon("Togopi",types2,4,1);

    /* --------------------  initialize trainers  --------------------- */

    Trainer ash = Trainer("Ash",Team::BLUE);
    Trainer misti = Trainer("Misti",Team::YELLOW);
    Trainer ohad = Trainer("Ohad",Team::YELLOW);
    Trainer sahar = Trainer("Sahar",Team::RED);

    /********************************************************************
     *                              tests                               *
     ********************************************************************/

    ASSERT_EQUAL(ash.GetTeam(),Team::BLUE);
    ASSERT_EQUAL(misti.GetTeam(),Team::YELLOW);
    ASSERT_EQUAL(sahar.GetTeam(),Team::RED);
    ASSERT_EQUAL(ohad.GetTeam(),misti.GetTeam());

    return true;
}

bool trainerTestTryToCatch() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types1 = set<PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);

    Pokemon pikachu = Pokemon("Pikachu",types1,6,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types2 = set<PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::PSYCHIC);

    Pokemon togopi = Pokemon("Togopi",types2,4,1);

    /* --------------------  initialize trainers  --------------------- */

    Trainer ash = Trainer("Ash",Team::BLUE);
    Trainer misti = Trainer("Misti",Team::YELLOW);
    Trainer ohad = Trainer("Ohad",Team::YELLOW);
    Trainer sahar = Trainer("Sahar",Team::RED);

    /********************************************************************
     *                              tests                               *
     ********************************************************************/
    ASSERT_TRUE( misti == ash );
    ASSERT_TRUE( misti.TryToCatch(togopi));
    ASSERT_TRUE( ash.TryToCatch(pikachu));
    ASSERT_TRUE( ash.TryToCatch(togopi));
    ASSERT_TRUE( ash.TryToCatch(pikachu));
    ASSERT_TRUE( misti < ash );

    return true;
}

bool trainerTestGetsAndUpdate() {
    /********************************************************************
     *                          initialization                          *
     ********************************************************************/
    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types1 = set<PokemonType>();
    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);

    Pokemon pikachu = Pokemon("Pikachu",types1,6,1);

    /* -------------------  initialize one pokemon  ------------------- */

    set <PokemonType>types2 = set<PokemonType>();
    types2.insert(mtm::pokemongo::PokemonType::PSYCHIC);

    Pokemon togopi = Pokemon("Togopi",types2,4,1);

    /* --------------------  initialize trainers  --------------------- */

    Trainer ash = Trainer("Ash",Team::BLUE);
    Trainer misti = Trainer("Misti",Team::YELLOW);
    Trainer ohad = Trainer("Ohad",Team::YELLOW);

    /* --------------------    initialize items    --------------------- */
    Item item1 = Item("POTION", 20);
    Item item2 = Item("CANDY", 10);
    Item item3 = Item("POTION", 34);

    /********************************************************************
     *                              tests                               *
     ********************************************************************/
    ASSERT_TRUE( misti.GetName() == "Misti");
    ASSERT_TRUE( ohad.GetName() == "Ohad");
    ASSERT_TRUE( ash.GetLevel() == 1 );
    ASSERT_TRUE( ash.TryToCatch(togopi));
    ASSERT_TRUE( ash.GetLevel() == 1 );
    ash.updateLevel(4);
    ASSERT_TRUE( ash.GetLevel() == 4 );
    ASSERT_TRUE( ash.TryToCatch(pikachu));
    ASSERT_TRUE( ash.GetFightBonus() == 0 );
    ash.updateFightBonus(3);
    ASSERT_TRUE( ash.GetFightBonus() == 3 );
    ohad.addItem( &item1 );
    ohad.addItem( &item2 );
    ohad.addItem( &item2 );
    ohad.addItem( &item3 );
    Item* ohad_item = ohad.getOldestItem();
    ASSERT_TRUE((ohad_item->getLevel() == 34)&&ohad_item->getType() == "POTION");

    return true;
}
bool trainerTest() {

    RUN_TEST(trainerTestCtor);
    RUN_TEST(trainerTestGetStrongestPokemon);
    RUN_TEST(trainerTestKillStrongestPokemon);
    RUN_TEST(trainerTestOperators);
    RUN_TEST(trainerTestIsAlly);
    RUN_TEST(trainerTestGetTeam);
    RUN_TEST(trainerTestTryToCatch);
    RUN_TEST(trainerTestGetsAndUpdate);
	/* print test will be tested in pokemon go */

    return true;
}

int main() {
    trainerTest();
    return 0;
}
