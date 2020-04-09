
#pragma once
#include "../Graph Structures/Graph.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef CGRAPH_SIMPLEDIRECTEDGRAPH_H
#define CGRAPH_SIMPLEDIRECTEDGRAPH_H

template <typename T>
class SimpleDirectedGraph : public Graph<T> {
public:
    //CONSTRUCTORS
    SimpleDirectedGraph();
    SimpleDirectedGraph(string new_title);
    SimpleDirectedGraph(const SimpleDirectedGraph<T> &other_graph);

    //DESTRUCTORS
    ~SimpleDirectedGraph();

    //ACCESSORS
    size_t netDegree(const Vertex<T> &v) const;
    size_t inDegree(const Vertex<T> &v) const;
    size_t outDegree(const Vertex<T> &v) const;

    //MUTATORS
    pair<Edge<T>*, bool> addEdge(Edge<T> &e);
    pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(typename Graph<T>::edge_iterator first, typename Graph<T>::edge_iterator last);
    unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);
    pair<Edge<T>*, bool> removeEdge(const Edge<T> &e);
    pair<Edge<T>*, bool> removeEdge(Vertex<T> &v1, Vertex<T> &v2);
    void setEdgeWeight(Edge<T> &e, double new_weight);
    void setEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2, double new_weight);
    void removeEdgeWeight(Edge<T> &e);
    void removeEdgeWeight(const Vertex<T> &v1, const Vertex<T> &v2);
    void addProperty(Property new_property);



private:
    //MEMBER VARIABLES
    unordered_set<Property> allowed_properties = {Property::Cycleless, Property::Unmodifiable, Property::DirectedEdges};

};


#endif //CGRAPH_SIMPLEDIRECTEDGRAPH_H
