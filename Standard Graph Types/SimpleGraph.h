
#pragma once
#include "Graph.h"
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
    ~SimpleGraph();

private:
    //MEMBER VARIABLES


};


#endif //CGRAPH_SIMPLEUNDIRECTEDGRAPH_H
