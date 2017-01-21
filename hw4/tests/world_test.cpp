/**************************************
 *       Header files include         *
 **************************************/

#include "../world.h"
#include "test_utils.h"

/**************************************
 *               Using                *
 **************************************/


/**************************************
 *               Tests                *
 **************************************/

bool GYMTestCombo() {
    /********************************************************************
     *                              tests                               *
     ********************************************************************/

//    ASSERT_NO_THROW(Trainer("Ash",Team::BLUE));
//    ASSERT_NO_THROW(Trainer("Misti",Team::RED));
//    ASSERT_NO_THROW(Trainer("Ohad",Team::YELLOW));
//    ASSERT_NO_THROW(Trainer("Sahar",Team::YELLOW));
//
//    ASSERT_THROW(mtm::pokemongo::TrainerInvalidArgsException,
//    		Trainer("",Team::YELLOW));

    return true;
}

bool PokestopTestCombo() {
    /********************************************************************
     *                              tests                               *
     ********************************************************************/

//    ASSERT_NO_THROW(Trainer("Ash",Team::BLUE));
//    ASSERT_NO_THROW(Trainer("Misti",Team::RED));
//    ASSERT_NO_THROW(Trainer("Ohad",Team::YELLOW));
//    ASSERT_NO_THROW(Trainer("Sahar",Team::YELLOW));
//
//    ASSERT_THROW(mtm::pokemongo::TrainerInvalidArgsException,
//    		Trainer("",Team::YELLOW));

    return true;
}

bool StarbucksTestCombo() {
    /********************************************************************
     *                              tests                               *
     ********************************************************************/

//    ASSERT_NO_THROW(Trainer("Ash",Team::BLUE));
//    ASSERT_NO_THROW(Trainer("Misti",Team::RED));
//    ASSERT_NO_THROW(Trainer("Ohad",Team::YELLOW));
//    ASSERT_NO_THROW(Trainer("Sahar",Team::YELLOW));
//
//    ASSERT_THROW(mtm::pokemongo::TrainerInvalidArgsException,
//    		Trainer("",Team::YELLOW));

    return true;
}

int main() {
    RUN_TEST(GYMTestCombo);
    GYM();
    ~GYM();

	void switchLeader( Trainer& leader );

    void Arrive(Trainer& trainer) override ;
    void Leave(Trainer& trainer) override ;
    bool Fight( Trainer& first , Trainer& second );
    void fightOutcome( Trainer& winner, Trainer& loser );
    bool makeFight( Trainer& first , Trainer& second );
    bool compareByTeam( Trainer& first , Trainer& second );
    void prepareToBattle( Trainer& first , Trainer& second );
    void upDateBonusPoints(  Trainer& trainer , int bonus );
    void updateDeathResult(Trainer& first , Trainer& second ,
  		  bool first_died, bool second_died );
    Trainer* findNextLeader();
    Trainer* candidateForLeadership( Team team );
    Trainer* checkTeamSubstitute(Trainer* red_candidate ,
    		Trainer* blue_candidate , Trainer* yellow_candidate );
    Trainer* checkisOneTeamLeft(Trainer* red_candidate ,
    		Trainer* blue_candidate , Trainer* yellow_candidate );
    Trainer* checkBestOutOfTwoSubstitute(Trainer* red_candidate ,
    		Trainer* blue_candidate , Trainer* yellow_candidate );
    Team GYMgetTeam();

    RUN_TEST(PokestopTestCombo);
    Item(const std::string& type,const int level) const;
    ~Item();
    const Item(const Item& item) const;
    const std::string getType();
    const int getLevel();



    Pokestop();
    ~Pokestop();
    void addItem(const Item& item);
    void Arrive(Trainer& trainer) override ;
    RUN_TEST(StarbucksTestCombo);
    Starbucks();
    ~Starbucks();
    void Arrive(Trainer& trainer) override ;

    RUN_TEST(WorldTestCombo);
    World();
    ~World();

    return 0;
}
