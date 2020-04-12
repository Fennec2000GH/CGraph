
#pragma once
#include "../Graph Structures/Graph.h"
#include <unordered_set>
using namespace std;

#ifndef CGRAPH_SIMPLEUNDIRECTEDGRAPH_H
#define CGRAPH_SIMPLEUNDIRECTEDGRAPH_H

template <typename T>
class SimpleGraph : public Graph<T> {
public:
    //CONSTRUCTORS
    SimpleGraph();
    SimpleGraph(string new_title);
    SimpleGraph(const SimpleGraph<T> &other_graph);

    //DESTRUCTORS

    //ACCESSORS

    //MUTATORS
    pair<Edge<T>*, bool> addEdge(Edge<T> &e);
    pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);
    void addProperty(Property new_property);


private:
    //MEMBER VARIABLES
    unordered_set<Property> allowed_properties = {Property::Cycleless, Property::Unmodifiable};

};


#endif //CGRAPH_SIMPLEUNDIRECTEDGRAPH_H
