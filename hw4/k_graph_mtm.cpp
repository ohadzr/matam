//
// Created by ohad on 16-Jan-17.
//

#include "k_graph_mtm.h"


using mtm::KGraph;
using std::set;

template <typename KeyType, typename ValueType, int k> //TODO: is this a good copy? general enough?
KGraph::Node::Node(KeyType const &key, ValueType const &value) :
        key(key), value(value){
    arcs = set::set();
}


KGraph::Node::~Node() {
}

