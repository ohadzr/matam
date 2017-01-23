
/**************************************
 *       Header files include         *
 **************************************/

#include "../k_graph_mtm.h"
#include "test_utils.h"

/**************************************
 *               Using                *
 **************************************/

using namespace mtm;
using namespace std;

/**************************************
 *               Tests                *
 **************************************/

bool TestCombo() {


    KGraph<string, int, 3> graph = KGraph<string, int, 3>(0);

    std::string zero = "zero";
    std::string one = "one";
    std::string two = "two";
    std::string three = "three";
    std::string four = "four";
    std::string no_number = "no number";


    ASSERT_NO_THROW(graph.Insert(one, 1));
    ASSERT_NO_THROW(graph.Insert(two, 2));
    ASSERT_NO_THROW(graph.Insert(three, 3));
    ASSERT_NO_THROW(graph.Insert(four, 4));
    ASSERT_NO_THROW(graph.Insert(zero));
    ASSERT_NO_THROW(graph.Insert(no_number));

    ASSERT_NO_THROW(graph.Connect(one, two, 0 ,0));
    ASSERT_THROW(KGraphNodesAlreadyConnected,
                 graph.Connect(one, two, 0 ,0));
    ASSERT_THROW(KGraphNodesAlreadyConnected,
                 graph.Connect(one, two, 1 ,1));
    ASSERT_THROW(KGraphNodesAlreadyConnected,
                 graph.Connect(one, two, 1 ,0));
    ASSERT_THROW(KGraphNodesAlreadyConnected,
                 graph.Connect(one, two, 0 ,1));
    ASSERT_THROW(KGraphNodesAlreadyConnected,
                 graph.Connect(two, one, 1 ,0));
    ASSERT_THROW(KGraphNodesAlreadyConnected,
                 graph.Connect(two, one, 0 ,0));

    ASSERT_THROW(KGraphEdgeAlreadyInUse ,graph.Connect(three, two, 1 ,0));
    ASSERT_NO_THROW(graph.Connect("three", "two", 0 ,1));



    return true;
}

int main() {
    RUN_TEST(TestCombo);
    return 0;
}