/**************************************
 *       Header files include         *
 **************************************/

#include "../pokemon.h"
#include "test_utils.h"

///**************************************
// *               Using                *
// **************************************/
//
//using mtm::pokemongo::Pokemon;
//using mtm::pokemongo::PokemonType;
//using std::set;
//using std::string;
//
///**************************************
// *               Tests                *
// **************************************/
//
//bool pokemonTestCtor() {
//    /********************************************************************
//     *                          initialization                          *
//     ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set<PokemonType> types1 = set<PokemonType>();
//    types1.insert(PokemonType::ELECTRIC);
//    types1.insert(PokemonType::NORMAL);
//    string pikachu_name = "Pikachu";
//    double pikacho_cp = 30.3;
//    int pikacho_level = 3;
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set<PokemonType> types2 = set<PokemonType>();
//    types2.insert(PokemonType::FIRE);
//    string Cyndaquil_name = "Cyndaquil";
//    double Cyndaquil_cp = 100.0;
//    int Cyndaquil_level = 4;
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    //check if throw empty string
//    set<PokemonType> types3 = set<PokemonType>();
//    types3.insert(PokemonType::NORMAL);
//    string Bad_pokemon1_name = "";
//    double Bad_pokemon1_cp = 90.9;
//    int Bad_pokemon1_level = 4;
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
////    string poor_pokemon_name = "poor_pokemon";
////    double poor_pokemon_cp = 80.0;
////    int poor_pokemon_level = 7;
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    //check if throw invalid cp
//    set <mtm::pokemongo::PokemonType>types5 =
//            set<mtm::pokemongo::PokemonType>();
//    types3.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string Bad_pokemon3_name = "Bad_pokemon3";
//    double Bad_pokemon3_cp = -90.8;
//    int Bad_pokemon3_level = 4;
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    //check if throw invalid level
//    set<PokemonType> types6 = set<PokemonType>();
//    types6.insert(PokemonType::GROUND);
//    types6.insert(PokemonType::NORMAL);
//    types6.insert(PokemonType::WATER);
//    string Bad_pokemon4_name = "Bad_pokemon4";
//    double Bad_pokemon4_cp = 40.8;
//    int Bad_pokemon4_level = 0;
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//
//    ASSERT_NO_THROW(Pokemon(pikachu_name,types1,pikacho_cp,pikacho_level));
//    ASSERT_NO_THROW(Pokemon(Cyndaquil_name,types2,Cyndaquil_cp,Cyndaquil_level));
//    ASSERT_THROW(mtm::pokemongo::PokemonInvalidArgsException,Pokemon(
//            Bad_pokemon1_name,types3,Bad_pokemon1_cp,Bad_pokemon1_level));
//   //ASSERT_NO_THROW(Pokemon(poor_pokemon_name,poor_pokemon_cp,poor_pokemon_level));
//    ASSERT_THROW(mtm::pokemongo::PokemonInvalidArgsException,
//                  Pokemon(Bad_pokemon3_name,types5,
//                      Bad_pokemon3_cp,Bad_pokemon3_level));
//    ASSERT_THROW(mtm::pokemongo::PokemonInvalidArgsException,
//                  Pokemon(Bad_pokemon4_name,types6,
//                      Bad_pokemon4_cp,Bad_pokemon4_level));
//
//
//    return true;
//}
//
//bool pokemonTestCopyCtor() {
//    /********************************************************************
//     *                          initialization                          *
//     ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types1 = set<PokemonType>();
//    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
//    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string pikachu_name = "Pikachu";
//    double pikachu_cp = 30.3;
//    int pikachu_level = 3;
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types2 = set<PokemonType>();
//    string togopi_name = "Togopi";
//    double togopi_cp = 30.3;
//    int togopi_level = 3;
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//    Pokemon pikachu(pikachu_name,types1,pikachu_cp,pikachu_level);
//    Pokemon pikachu_copy(pikachu);
//    ASSERT_TRUE(pikachu == pikachu_copy);
//
//    Pokemon togopi(togopi_name,types2,togopi_cp,togopi_level);
//    Pokemon togopi_copy(togopi);
//    ASSERT_TRUE(togopi == togopi_copy);
//
//    return true;
//}
//
//bool pokemonTestOperators() {
//
//	/********************************************************************
//	 *                          initialization                          *
//	 ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types1 = set<PokemonType>();
//    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
//    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string pikachu_name = "Pikachu";
//    double pikachu_cp = 30.3;
//    int pikachu_level = 3;
//    Pokemon pikachu(pikachu_name,types1,pikachu_cp,pikachu_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types2 = set<PokemonType>();
//    string togopi_name = "Togopi";
//    double togopi_cp = 30.3;
//    int togopi_level = 3;
//    Pokemon togopi(togopi_name,types2,togopi_cp,togopi_level);
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//    Pokemon pikachu_test1 = pikachu;
//    togopi = pikachu;
//    ASSERT_TRUE(pikachu == pikachu_test1);
//    ASSERT_TRUE(pikachu == togopi);
//
//    return true;
//}
//
//bool pokemonTestGetLevel() {
//    /********************************************************************
//     *                          initialization                          *
//     ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types1 = set<PokemonType>();
//    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
//    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string pikachu_name = "Pikachu";
//    double pikachu_cp = 30.3;
//    int pikachu_level = 3;
//    Pokemon pikachu = Pokemon(pikachu_name,types1,pikachu_cp,pikachu_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types2 = set<PokemonType>();
//    string togopi_name = "Togopi";
//    double togopi_cp = 30.3;
//    int togopi_level = 5;
//    Pokemon togopi = Pokemon(togopi_name,types2,togopi_cp,togopi_level);
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//
//    ASSERT_TRUE( pikachu.Level() == 3 );
//    ASSERT_TRUE( togopi.Level() == 5 );
//
//    return true;
//}
//
//bool pokemonTestPokemonCompare() {
//    /********************************************************************
//     *                          initialization                          *
//     ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types1 = set<PokemonType>();
//    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
//    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
//    types1.insert(mtm::pokemongo::PokemonType::ROCK);
//    string pikachu_name = "Pikachu";
//    double pikachu_cp = 6;
//    int pikachu_level = 4;
//    Pokemon pikachu = Pokemon(pikachu_name,types1,pikachu_cp,pikachu_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types2 = set<PokemonType>();
//    string togopi_name = "Togopi";
//    double togopi_cp = 12;
//    int togopi_level = 2;
//    Pokemon togopi = Pokemon(togopi_name,types2,togopi_cp,togopi_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types3 = set<PokemonType>();
//    types3.insert(mtm::pokemongo::PokemonType::FIRE);
//    types3.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string charmander_name = "Charmander";
//    double charmander_cp = 4;
//    int charmander_level = 6;
//    Pokemon charmander = Pokemon(charmander_name,types3,charmander_cp,
//                                 charmander_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types4 = set<PokemonType>();
//    types4.insert(mtm::pokemongo::PokemonType::PSYCHIC);
//    string myo_name = "Myo";
//    double myo_cp = 3;
//    int myo_level = 8;
//    Pokemon myo = Pokemon(myo_name,types4,myo_cp,myo_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types5 = set<PokemonType>();
//    types4.insert(mtm::pokemongo::PokemonType::FIRE);
//    string sahar_name = "Sahar";
//    double sahar_cp = 4;
//    int sahar_level = 2;
//    Pokemon sahar = Pokemon(sahar_name,types5,sahar_cp,sahar_level);
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//
//    ASSERT_TRUE(  !(pikachu == togopi) );
//    ASSERT_TRUE(  pikachu == charmander );
//    ASSERT_TRUE(  !(togopi ==  charmander) );
//    ASSERT_TRUE(  myo !=  charmander );
//    ASSERT_TRUE(  myo >  charmander );
//    ASSERT_TRUE(  myo >=  charmander );
//    ASSERT_TRUE( togopi != myo );
//    ASSERT_TRUE( togopi <= myo );
//    ASSERT_TRUE( togopi < myo );
//    ASSERT_TRUE( sahar < myo );
//    ASSERT_TRUE( sahar < togopi );
//    ASSERT_TRUE( sahar < charmander );
//
//    return true;
//}
//
//bool pokemonTestHit() {
//    /********************************************************************
//     *                          initialization                          *
//     ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types1 = set<PokemonType>();
//    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
//    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
//    types1.insert(mtm::pokemongo::PokemonType::ROCK);
//    string pikachu_name = "Pikachu";
//    double pikachu_cp = 6;
//    int pikachu_level = 4;
//    Pokemon pikachu = Pokemon(pikachu_name,types1,pikachu_cp,pikachu_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types2 = set<PokemonType>();
//    string togopi_name = "Togopi";
//    double togopi_cp = 12;
//    int togopi_level = 2;
//    Pokemon togopi = Pokemon(togopi_name,types2,togopi_cp,togopi_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types3 = set<PokemonType>();
//    types3.insert(mtm::pokemongo::PokemonType::FIRE);
//    types3.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string charmander_name = "Charmander";
//    double charmander_cp = 4;
//    int charmander_level = 6;
//    Pokemon charmander = Pokemon(charmander_name,types3,charmander_cp,
//                                 charmander_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types4 = set<PokemonType>();
//    types4.insert(mtm::pokemongo::PokemonType::PSYCHIC);
//    string myo_name = "Myo";
//    double myo_cp = 3;
//    int myo_level = 8;
//    Pokemon myo = Pokemon(myo_name,types4,myo_cp,myo_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types5 = set<PokemonType>();
//    types4.insert(mtm::pokemongo::PokemonType::FIRE);
//    string sahar_name = "Sahar";
//    double sahar_cp = 4;
//    int sahar_level = 2;
//    Pokemon sahar = Pokemon(sahar_name,types5,sahar_cp,sahar_level);
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//    ASSERT_TRUE( !charmander.Hit(myo) );
//    ASSERT_TRUE( !togopi.Hit(myo) );
//    ASSERT_TRUE( !pikachu.Hit(myo) );
//    ASSERT_TRUE( !sahar.Hit(myo));
//    ASSERT_TRUE( myo.Hit(myo) );
//    ASSERT_TRUE( pikachu.Hit(myo) );
//
//    return true;
//}
//
//bool pokemonTestHeal() {
//    /********************************************************************
//     *                          initialization                          *
//     ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types1 = set<PokemonType>();
//    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
//    types1.insert(mtm::pokemongo::PokemonType::NORMAL);
//    types1.insert(mtm::pokemongo::PokemonType::ROCK);
//    string pikachu_name = "Pikachu";
//    double pikachu_cp = 6;
//    int pikachu_level = 4;
//    Pokemon pikachu = Pokemon(pikachu_name,types1,pikachu_cp,pikachu_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types2 = set<PokemonType>();
//    string togopi_name = "Togopi";
//    double togopi_cp = 12;
//    int togopi_level = 2;
//    Pokemon togopi = Pokemon(togopi_name,types2,togopi_cp,togopi_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types3 = set<PokemonType>();
//    types3.insert(mtm::pokemongo::PokemonType::FIRE);
//    types3.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string charmander_name = "Charmander";
//    double charmander_cp = 4;
//    int charmander_level = 6;
//    Pokemon charmander = Pokemon(charmander_name,types3,charmander_cp,
//                                 charmander_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types4 = set<PokemonType>();
//    types4.insert(mtm::pokemongo::PokemonType::PSYCHIC);
//    string myo_name = "Myo";
//    double myo_cp = 3;
//    int myo_level = 8;
//    Pokemon myo = Pokemon(myo_name,types4,myo_cp,myo_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types5 = set<PokemonType>();
//    types4.insert(mtm::pokemongo::PokemonType::FIRE);
//    string sahar_name = "Sahar";
//    double sahar_cp = 4;
//    int sahar_level = 2;
//    Pokemon sahar = Pokemon(sahar_name,types5,sahar_cp,sahar_level);
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//    ASSERT_TRUE( !charmander.Hit(myo) );
//    ASSERT_TRUE( !togopi.Hit(myo) );
//    ASSERT_TRUE( !pikachu.Hit(myo) );
//    ASSERT_TRUE( !sahar.Hit(myo));
//    ASSERT_TRUE( myo.Hit(myo) );
//    ASSERT_TRUE( pikachu.Hit(myo) );
//    myo.Heal();
//    ASSERT_TRUE( !pikachu.Hit(myo) );
//    ASSERT_TRUE( !pikachu.Hit(myo) );
//    ASSERT_TRUE( !pikachu.Hit(myo) );
//    ASSERT_TRUE( !pikachu.Hit(myo) );
//    ASSERT_TRUE( pikachu.Hit(myo) );
//    return true;
//}
//
//bool pokemonTestTrain() {
//    /********************************************************************
//     *                          initialization                          *
//     ********************************************************************/
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types1 = set<PokemonType>();
//    types1.insert(mtm::pokemongo::PokemonType::ELECTRIC);
//    types1.insert(mtm::pokemongo::PokemonType::FAIRY);
//    string pikachu_name = "Pikachu";
//    double pikachu_cp = 6;
//    int pikachu_level = 4;
//    Pokemon pikachu = Pokemon(pikachu_name,types1,pikachu_cp,pikachu_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types3 = set<PokemonType>();
//    types3.insert(mtm::pokemongo::PokemonType::FIRE);
//    types3.insert(mtm::pokemongo::PokemonType::NORMAL);
//    string charmander_name = "Charmander";
//    double charmander_cp = 1;
//    int charmander_level = 6;
//    Pokemon charmander = Pokemon(charmander_name,types3,charmander_cp,
//                                 charmander_level);
//
//    /* -------------------  initialize one pokemon  ------------------- */
//
//    set <PokemonType>types4 = set<PokemonType>();
//    types4.insert(mtm::pokemongo::PokemonType::PSYCHIC);
//    types4.insert(mtm::pokemongo::PokemonType::PSYCHIC);
//    types4.insert(mtm::pokemongo::PokemonType::PSYCHIC);
//    string myo_name = "Myo";
//    double myo_cp = 4;
//    int myo_level = 6;
//    Pokemon myo = Pokemon(myo_name,types4,myo_cp,myo_level);
//
//    /********************************************************************
//     *                              tests                               *
//     ********************************************************************/
//
//    ASSERT_THROW(mtm::pokemongo::PokemonInvalidArgsException,
//                 charmander.Train(0) );
//    ASSERT_TRUE( myo == pikachu );
//    myo.Train(2);
//    ASSERT_TRUE( myo > pikachu );
//
//    return true;
//}
//
//bool pokemonTest() {
//    RUN_TEST(pokemonTestCtor);
//    RUN_TEST(pokemonTestCopyCtor);
//    RUN_TEST(pokemonTestOperators);
//    RUN_TEST(pokemonTestGetLevel);
//    RUN_TEST(pokemonTestPokemonCompare);
//    RUN_TEST(pokemonTestHit);
//    RUN_TEST(pokemonTestHeal);
//    RUN_TEST(pokemonTestTrain);
//    /* print test will be tested in pokemon go */
//    return true;
//}
//
//int main() {
//    pokemonTest();
//    return 0;
//}
