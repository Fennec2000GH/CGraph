
#include "SimpleGraph.h"

//SimpleGraph
//CONSTRUCTORS
template <typename T>
SimpleGraph<T>::SimpleGraph():Graph() { }

template <typename T>
SimpleGraph<T>::SimpleGraph(string new_title):Graph(new_title) { }

template <typename T>
simpleGraph<T>::SimpleGraph(const SimpleGraph<T> &other_graph):Graph(other_graph) { }

//DESTRUCTORS
Graph<T>::~SimpleGraph() { }

