
#pragma once
#include "Graph.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef CGRAPH_SIMPLEDIRECTEDGRAPH_H
#define CGRAPH_SIMPLEDIRECTEDGRAPH_H

template <typename T>
class SimpleDirectedGraph : public Graph {
public:
    //CONSTRUCTORS
    SimpleDirectedGraph();
    SimpleDirectedGraph(string new_title);
    SimpleDirectedGraph(const SimpleDirectedGraph<T> &other_graph);

    //DESTRUCTORS
    ~SimpleDirectedGraph();

    //ACCESSORS


    //MUTATORS

private:
    //MEMBER VARIABLES
    unordered_set<Property> allowed_properties = {Property::Cycleless, Property::Unmodifiable, Property::DirectedEdges}

};


#endif //CGRAPH_SIMPLEDIRECTEDGRAPH_H
