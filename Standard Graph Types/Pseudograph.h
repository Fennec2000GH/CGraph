
#pragma once
#include <iostream>
#include <string>
using namespace std;

#ifndef CGRAPH_PSEUDOGRAPH_H
#define CGRAPH_PSEUDOGRAPH_H

template <typename T>
class Pseudograph : public Multigraph<T> {
public:
    //CONSTRUCTORS
    Pseudograph();
    Pseudograph(string new_title);
    Pseudograph(const Pseudograph<T> &other_graph);

    //DESTRUCTORS
    ~Pseudograph();

    //ACCESSORS
    unsigned getDegree(const Vertex<T> &v) const;
    unsigned getSelfLoopDensity() const;
    bool hasSelfLoop(const Vertex<T> &v) const;

    //MUTATORS
    pair<Edge<T>*, bool> addEdge(Edge<T> &e);
    pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);
    void addProperty(Property new_property);

private:
    //MEMBER VARIABLES
    unordered_set<Property> allowed_properties = {Property::Cycleless, Property::Unmodifiable, Property::SelfLoop, Property::MultipleEdges};
};


#endif //CGRAPH_PSEUDOGRAPH_H
