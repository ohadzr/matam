/**************************************
 *       Header files include         *
 **************************************/

#include "../world.h"
#include "test_utils.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::World;

/**************************************
 *               Tests                *
 **************************************/

bool TestComboWorld() {
    /********************************************************************
    *                              tests                               *
    ********************************************************************/


    std::ifstream world_in("tests/world_test.in");
    std::string line;

//    while (std::getline(world_in, line)) {
//          std::istringstream line_stream(line);
//          line_stream >> *world;
//  }
    World* technion = new World();

    std::getline(world_in, line);
    std::istringstream line_stream(line);
    ASSERT_NO_THROW(line_stream >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream1(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream1 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream2(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream2 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream3(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream3 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream4(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream4 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream5(line);
    ASSERT_THROW(mtm::pokemongo::WorldLocationNameAlreadyUsed,
                 line_stream5 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream6(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream6 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream7(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream7 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream8(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream8 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream9(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream9 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream10(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream10 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream11(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream11 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream12(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream12 >> *technion);

    std::getline(world_in, line);
        std::istringstream line_stream13_a(line);
        ASSERT_NO_THROW(line_stream13_a >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream13(line);
    ASSERT_THROW(mtm::pokemongo::WorldLocationNameAlreadyUsed,
                 line_stream13 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream14(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream14 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream15(line);
    ASSERT_NO_THROW(line_stream15 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream16(line);
    ASSERT_NO_THROW(line_stream16 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream17(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream17 >> *technion);

    std::getline(world_in, line);
    std::istringstream line_stream18(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream18 >> *technion);

    delete technion;

    return true;
}

int main() {
    RUN_TEST(TestComboWorld);
    return 0;
}
