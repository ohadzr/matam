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

bool TestCombo() {
    /********************************************************************
    *                              tests                               *
    ********************************************************************/

    std::ifstream world_in("world_test.in");
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
//    line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldLocationNameAlreadyUsed,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldLocationNameAlreadyUsed,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_NO_THROW(line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_NO_THROW(line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_NO_THROW(line_stream >> *technion);

    std::getline(world_in, line);
//    std::istringstream line_stream(line);
    ASSERT_THROW(mtm::pokemongo::WorldInvalidInputLineException,
                 line_stream >> *technion);


    return true;
}

int main() {
    RUN_TEST(TestCombo);
    return 0;
}
