
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

bool TestComboKGraph() {


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
    ASSERT_TRUE(graph["one"] == 1);
    ASSERT_TRUE(graph["zero"] == 0);
    ASSERT_TRUE(graph["still zero"] == 0);
    ASSERT_TRUE(graph.Contains("still zero"));

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

    ASSERT_NO_THROW(graph.Connect(two, 2));
    ASSERT_THROW(KGraphEdgeOutOfRange, graph.Connect(two, 3));
    ASSERT_THROW(KGraphEdgeOutOfRange ,graph.Connect(two, -1));
    ASSERT_NO_THROW(graph.Disconnect(two, one));
    ASSERT_NO_THROW(graph.Connect(one, two, 0 ,0));

    ASSERT_TRUE(graph.Contains(one));
    ASSERT_TRUE(graph.Contains(four));
    ASSERT_FALSE(graph.Contains("five"));

    KGraph<string, int, 3>::iterator it = graph.BeginAt(four);
    ASSERT_TRUE(*it == "four");
    ASSERT_NO_THROW(graph.Remove(it));
    ASSERT_THROW(KGraphKeyNotFoundException, graph.Remove("five"));
    it = graph.BeginAt(one);
    ASSERT_NO_THROW(it.Move(2));
    ASSERT_THROW(KGraphIteratorReachedEnd, graph.Remove(it));


    return true;
}

int main() {
    RUN_TEST(TestComboKGraph);
    return 0;
}
