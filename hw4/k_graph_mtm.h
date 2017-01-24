#ifndef K_GRAPH_MTM_H
#define K_GRAPH_MTM_H

#include "exceptions.h"
#include <vector>
#include <set>


namespace mtm {

/* Requirements: KeyType::operator<,
               KeyType::operator==,
               KeyType and ValueType copy c'tor*/
template<typename KeyType, typename ValueType, int k> class KGraph {
 protected:
/*   A node. Represents the basic data unit in a kGraph. Has a key, a value, and
   connected to at most k other nodes through k edges numbered from 0 to k-1.*/
  class Node {
  private:
      KeyType key;
      ValueType value;
      std::vector<Node*> arcs;

  public:
/*     Constructs a new node with the given key and value.

     @param key key of the new node.
     @param value value of the new node.*/

    Node(KeyType const &key, ValueType const &value):
            key(KeyType(key)), value(ValueType(value)) {
        arcs = std::vector<Node*>();

        for (int i=0; i<k ; i++) {
            arcs.push_back(nullptr);
        }

    }
    /* A destructor.*/
    ~Node() {}

/*     Returns the key of the node.

     @return the key of the node.*/
    KeyType const& Key() const {
        return key;
    }

/*     Returns the value of the node.

     @return the value of the node.*/
    ValueType& Value(){
        return value;
    }
    ValueType const& Value() const {
      return value;
    }

/*     Returns a reference to the pointer to the neighbor node connected through
     edge i.

     @return (reference to) a pointer to the node connected through edge i.*/
    Node*& operator[](int i) {
      return arcs[i];
    }
    const Node* const operator[](int i) const {
      return arcs[i];
    }
  };
 public:
  class const_iterator;  // forward declaration

/*   An iterator. Used to iterate over the data in a kGraph. At every given
   moment, the iterator points either to one of the nodes in the graph, or to
   the end of the graph.*/
  class iterator {
    private:
      Node* curr_node;
      KGraph* curr_graph;
      friend class const_iterator;
    public:
/*     Constructs a new iterator that points to a given node in the given graph.

     @param node the node the new iterator points to.
     @param graph the kGraph over which the iterator iterates.*/
    iterator(Node* node, KGraph* graph) : curr_node(node), curr_graph(graph) {
    }

/*     A copy constructor.

     @param it the iterator to copy.*/
    iterator(const iterator& it) : curr_node(it.curr_node),
                                   curr_graph(it.curr_graph) {
    }

/*     A destructor.*/
    ~iterator() {}

/*     Moves the iterator to point to the node that is connected to the current
     node through edge i.

     @param i the edge over which to move.
     @return a reference to *this (the same iterator) after moving it.
     @throw KGraphEdgeOutOfRange if i is not in the range [0,k-1]
     @throw KGraphIteratorReachedEnd when trying to move an iterator that
            points to the end of the graph.*/
    iterator& Move(int i) {
        if (i < 0 || i > k-1)
            throw KGraphEdgeOutOfRange();
        if (curr_node == nullptr)
            throw KGraphIteratorReachedEnd();
        curr_node = (*curr_node)[i];
        return *this;
    }

/*     Dereferne operator. Return the key of the node pointed by the iterator.

     @return the key of the node to which the iterator points.
     @throw KGraphIteratorReachedEnd when trying to dereference an iterator
            that points to the end of the graph.*/
    KeyType const& operator*() const {
        if (curr_node == nullptr)
            throw KGraphIteratorReachedEnd();
        return curr_node->Key();
    }

/*     Equal operator. Two iterators are equal iff they either point to the same
     node in the same graph, or to the end of the same graph.

     @param rhs right hand side operand.
     @return true iff the iterators are equal.*/
    bool operator==(const iterator& rhs) const {
        if (curr_graph != rhs.curr_graph) //TODO: check if this enough or should I implement operator== for graph
            return false;

        // if same graph
        if (curr_node == nullptr && rhs.curr_node == nullptr)
            return true;
        if (curr_node == nullptr || rhs.curr_node == nullptr)
            return false;

        return curr_node->Key() == rhs.curr_node->Key();
    }

/*     Not equal operator (see definition of equality above).

     @param rhs right hand side operand.
     @return true iff the iterators are not equal.*/
    bool operator!=(const iterator& rhs) const {
        return !(*this == rhs);
    }

/*     Equal operator for a const iterator as the right-hand side operand.

     @param rhs right hand side operand.
     @return true iff the iterators are equal.*/
    bool operator==(const const_iterator& rhs) const {
        if (curr_graph != rhs.curr_graph) //TODO: check if this enough or should I implement operator== for graph
            return false;

        // if same graph
        if (curr_node == nullptr && rhs.curr_node == nullptr)
            return true;
        if (curr_node == nullptr || rhs.curr_node == nullptr)
            return false;

        return curr_node->Key() == rhs.curr_node->Key();
    }

/*     Not equal operator for a const iterator as the right-hand side operand.

     @param rhs right hand side operand.
     @return true iff the iterators are not equal.*/
    bool operator!=(const const_iterator& rhs) const {
        return !(*this == rhs);
    }
  };

/*   A const iterator. Used to iterate over the data in a constant kGraph.
   Similarly to a regular iterator, at every given moment, the iterator points
   either to one of the nodes in the graph, or to the end of the graph.*/
  class const_iterator {
  private:
      const Node* curr_node;
      const KGraph* curr_graph;
   public:
      friend class iterator;
/*     Constructs a new const iterator that points to a given node in the given
     graph.

     @param node the node the new iterator points to.
     @param graph the kGraph over which the iterator iterates.*/
    const_iterator(const Node* node, const KGraph* graph) :
            curr_node(node), curr_graph(graph) {
    }

/*     A copy constructor.

     @param it the iterator to copy.*/
    const_iterator(const const_iterator& it): curr_node(it.curr_node),
                                              curr_graph(it.curr_graph) {
    }

/*     Conversion from a regular iterator. Constucts a new const iterator that
     points to the same node as the given iterator.

     @param it the iterator we would like to convert to const iterator.*/
    const_iterator(const iterator& it): curr_node(it.curr_node),
                                        curr_graph(it.curr_graph) {
    }
/*     A destructor.*/
    ~const_iterator() {}

/*     Moves the iterator to point to the node that is connected to the current
     node through edge i.

     @param i the edge over which to move.
     @return a reference to *this (the same iterator) after moving it.
     @throw KGraphEdgeOutOfRange if i is not in the range [0,k-1]
     @throw KGraphIteratorReachedEnd when trying to move an iterator that
            points to the end of the graph.*/
    const_iterator& Move(int i) {
        if (i < 0 || i > k-1)
            throw KGraphEdgeOutOfRange();
        if (curr_node == nullptr)
            throw KGraphIteratorReachedEnd();
        curr_node = (*curr_node)[i];
        return *this;
    }

/*     Dereferne operator. Return the key of the node pointed by the iterator.

     @return the key of the node to which the iterator points.
     @throw KGraphIteratorReachedEnd when trying to dereference an iterator
            that points to the end of the graph.*/
    KeyType const& operator*() const {
        if (curr_node == nullptr)
            throw KGraphIteratorReachedEnd();
        return curr_node->Key();
    }

/*     Equal operator. Two iterators are equal iff they either point to the same
     node in the same graph, or to the end of the same graph.

     @param rhs righ hand side operand.
     @return true iff the iterators are equal.*/
    bool operator==(const const_iterator& rhs) const {
        if (curr_graph != rhs.curr_graph) //TODO: check if this enough or should I implement operator== for graph
            return false;

        // if same graph
        if (curr_node == nullptr && rhs.curr_node == nullptr)
            return true;
        if (curr_node == nullptr || rhs.curr_node == nullptr)
            return false;

        return curr_node->Key() == rhs.curr_node->Key();
    }

/*     Not equal operator (see definition of equality above).

     @param rhs right hand side operand.
     @return true iff the iterators are not equal.*/
    bool operator!=(const const_iterator& rhs) const {
        return !(*this == rhs);
    }
  };


    private:
        std::set<Node*> nodes;
        const ValueType k_default_value;


    public:
/*   Constructs a new empty kGraph with the given default value.

   @param default_value the default value in the graph.*/
  explicit KGraph(ValueType const& default_value) :
          nodes(std::set<Node*>()),
          k_default_value(ValueType(default_value)){
  }


/*   A copy constructor. Copies the given graph. The constructed graph will have
   the exact same structure with copied data.

   @param k_graph the graph to copy.*/
  KGraph(const KGraph& k_graph) :
          nodes(std::set<Node*>(k_graph.nodes)),
          k_default_value(k_graph.k_default_value){
  }

/*   A destructor. Destroys the graph together with all resources allocated.*/
  ~KGraph() {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end() ; set_iter++) {
          delete (*set_iter);
      }
  }

/*   Returns an iterator to the node with the given key.

   @param i the key of the node which the returned iterator points to.
   @return iterator the newly constructed iterator.
   @throw KGraphKeyNotFoundException when the given key is not found in the
          graph.*/
  iterator BeginAt(KeyType const& i) {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end() ; set_iter++) {
          if ( (*set_iter)->Key() == i ) {
              Node* node = *set_iter;
              return iterator(node ,this);
          }
      }
      throw KGraphKeyNotFoundException();
  }
  const_iterator BeginAt(KeyType const& i) const {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end() ; set_iter++) {
          if ( (*set_iter)->Key() == i ) {
              const Node* node = *set_iter;
              return const_iterator(node ,this);
          }
      }
      throw KGraphKeyNotFoundException();
  }

/*   Returns an iterator to the end of the graph.

   @return iterator an iterator to the end of the graph.*/
  const_iterator End() const {
      return const_iterator(nullptr, this);
  }

/*   Inserts a new node with the given data to the graph.

   @param key the key to be assigned to the new node.
   @param value the value to be assigned to the new node.
   @throw KGraphKeyAlreadyExistsExpection when trying to insert a node with a
          key that already exists in the graph.*/
  void Insert(KeyType const& key, ValueType const& value) {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end(); set_iter++) {
          if ((*set_iter)->Key() == key){
              throw KGraphKeyAlreadyExistsExpection();
          }
      }
      Node* node = new Node(key,value);
      nodes.insert(node);

  }

/*   Inserts a new node with the given key and the default value to the graph.

   @param key the key to be assigned to the new node.
   @throw KGraphKeyAlreadyExistsExpection when trying to insert a node with a
          key that already exists in the graph.*/
  void Insert(KeyType const& key) {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end(); set_iter++) {
          if ((*set_iter)->Key() == key){
              throw KGraphKeyAlreadyExistsExpection();
          }
      }
      Node* node = new Node(key, k_default_value);
      nodes.insert(node);
  }

/*   Removes the node with the given key from the graph.

   @param key the key of the node to be removed.
   @throw KGraphKeyNotFoundException when trying to remove a key that cannot
          be found in the graph.*/
  void Remove(KeyType const& key) {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end(); set_iter++) {
          if ((*set_iter)->Key() == key) {
              Node* node = *set_iter;
              for (int i=0; i<k ;i++){
                  if ( (*node)[i] != nullptr ) {
                      Disconnect((*set_iter)->Key(), ((*node)[i])->Key());
                  }
              }
              delete (*set_iter);
              nodes.erase(set_iter);
              return;
          }
      }
      throw KGraphKeyNotFoundException();
  }

/*   Removes the node pointed by the given iterator from the graph. If the
   given iterator neither points to a node in this graph nor to the end of
   this graph, the behaviour of this function is undefined.

   @param it the iterator that points to the node to be removed.
   @throw KGraphIteratorReachedEnd when the given iterator points to the end
          of the graph.*/
  void Remove(const iterator& it) {
      KeyType key = it.operator*();
      Remove(key);
  }

/*   The subscript operator. Returns a reference to the value assigned to
   the given key in the graph. If the key does not exist, inserts a new node
   to the graph with the given key and the default value, then returns a
   refernce to its value.

   @param key the key to return its value.
   @return the value assigned to the given key.*/
  ValueType& operator[](KeyType const& key) {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end() ; set_iter++) {
          Node node = (**set_iter);
          if ( node.Key() == key ) {
              return node.Value();
          }
      }
      Insert(key);
      return (*this)[key];
  }

/*   A const version of the subscript operator. Returns the value assigned to
   the given key in the graph. If the key does not exist, throws an exception.

   @param key the key to return its value.
   @return the value assigned to the given key.
   @throw KGraphKeyNotFoundException if the given key cannot be found in the
          graph.*/
  ValueType const& operator[](KeyType const& key) const {
      typename std::set<Node*>::iterator set_iter = nodes.begin();
      for (; set_iter != nodes.end() ; set_iter++) {
          Node node = (**set_iter);
          if ( node.Key() == key ) {
              return node.Value();
          }
      }
      throw KGraphKeyNotFoundException();
  }

/*   Checks whether the graph contains the given key.

   @param key
   @return true iff the graph contains the given key.*/
  bool Contains(KeyType const& key) const {
      for (typename std::set<Node*>::iterator set_iter = nodes.begin();
           set_iter != nodes.end() ; set_iter++) {
          if ( (*set_iter)->Key() == key ) {
              return true;
          }
      }
      return false;
  }

/*   Connects two nodes in the graph with an edge.

   @param key_u the key of the first node.
   @param key_v the key of the second node.
   @param i_u the index of the new edge at the first node.
   @param i_v the index of the new edge at the second node.
   @throw KGraphKeyNotFoundException if at least one of the given keys cannot
          be found in the graph.
   @throw KGraphEdgeOutOfRange if i is not in the range [0,k-1].
   @throw KGraphNodesAlreadyConnected if the two nodes are already connected.
   @throw KGraphEdgeAlreadyInUse if at least one of the indices of the edge at
          one of the nodes is already in use.*/
  void Connect(KeyType const& key_u, KeyType const& key_v, int i_u, int i_v) {
      if (!Contains(key_u) || !Contains(key_v))
          throw KGraphKeyNotFoundException();
      if (i_u < 0 || i_u > k-1 || i_v < 0 || i_v > k-1)
          throw KGraphEdgeOutOfRange();

      typename std::set<Node*>::iterator set_iter;
      set_iter = nodes.begin();

      Node* node_u = nullptr;
      Node* node_v = nullptr;
      for (; set_iter != nodes.end() ; set_iter++) {
          if ( (*set_iter)->Key() == key_u ) {
              node_u = *set_iter;
          }
          if ( (*set_iter)->Key() == key_v ) {
              node_v = *set_iter;
          }
      }
      if (node_u == nullptr || node_v == nullptr) return;

      for (int i=0; i<k; i++) {
          if ((*node_u)[i] == nullptr) continue;
          if (((*node_u)[i])->Key() == node_v->Key())
              throw KGraphNodesAlreadyConnected();
      }
      if ((*node_u)[i_u] != nullptr || (*node_v)[i_v] != nullptr)
          throw KGraphEdgeAlreadyInUse();

      (*node_u)[i_u] = node_v;
      (*node_v)[i_v] = node_u;
  }

/*   Connects a node to itself via a self loop.

   @param key the key of the node.
   @param i the index of the self loop.
   @throw KGraphKeyNotFoundException if the given keys cannot be found in the
          graph.
   @throw KGraphEdgeOutOfRange if i is not in the range [0,k-1]
   @throw KGraphNodesAlreadyConnected if the node is already self connected.
   @throw KGraphEdgeAlreadyInUse if the index of the self loop is already in
          use.*/
  void Connect(KeyType const& key, int i) {
      if (!Contains(key))
          throw KGraphKeyNotFoundException();
      if (i < 0 || i > k-1 )
          throw KGraphEdgeOutOfRange();

      typename std::set<Node*>::iterator set_iter;
      set_iter = nodes.begin();
      Node* node = nullptr;
      for (; set_iter != nodes.end() ; set_iter++) {
          if ((*set_iter)->Key() == key) {
              node = *set_iter;
          }
      }
      if (node == nullptr) return;
      if (((*node)[i]) == node)
          throw KGraphNodesAlreadyConnected();
      if ((*node)[i] != nullptr)
          throw KGraphEdgeAlreadyInUse();

      (*node)[i] = node;
  }

/*   Disconnects two connected nodes.

   @param key_u the key of the first node.
   @param key_v the key of the second node.
   @throw KGraphKeyNotFoundException if at least one of the given keys cannot
          be found in the graph.
   @throw kGraphNodesAreNotConnected if the two nodes are not connected.*/
  void Disconnect(KeyType const& key_u, KeyType const& key_v) {
      if (!Contains(key_u) || !Contains(key_v))
          throw KGraphKeyNotFoundException();

      typename std::set<Node*>::iterator set_iter = nodes.begin();
      Node* node_u = nullptr;
      Node* node_v = nullptr;
      for (; set_iter != nodes.end() ; set_iter++) {
          if ( (*set_iter)->Key() == key_u ) {
              node_u = *set_iter;
          }
          if ( (*set_iter)->Key() == key_v ) {
              node_v = *set_iter;
          }
      }

      for (int i=0; i < k ; i++) {
          if ((*node_u)[i]->Key() == node_v->Key())
              (*node_u)[i] = nullptr;
      }

      for (int i=0; i < k ; i++) {
          if ((*node_v)[i]->Key() == node_u->Key()) {
              (*node_v)[i] = nullptr;
              return;
          }
      }
      throw kGraphNodesAreNotConnected();
  }

};

}  // namespace mtm

#endif  // K_GRAPH_MTM_H
