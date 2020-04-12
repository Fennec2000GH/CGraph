
#pragma once
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
    double getSelfLoopDensity() const;
    bool hasSelfLoop(const Vertex<T> &v) const;

    //MUTATORS
    pair<Edge<T>*, bool> addEdge(Edge<T> &e);
    pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);
    void addProperty(Property new_property);

private:
    //MEMBER VARIABLES
    unordered_map<Vertex<T>&, unsigned> self_loop_edges; /* also present in Multigraph<T>::edges */
    unordered_set<Property> allowed_properties = {Property::Cycleless, Property::Unmodifiable, Property::SelfLoop, Property::MultipleEdges};

};


#endif //CGRAPH_PSEUDOGRAPH_H
