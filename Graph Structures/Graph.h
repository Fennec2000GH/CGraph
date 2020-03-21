
#pragma once
#include "Edge.h"
#include <algorithm>
#include <iostream>
#include <unordered_set>
using namespace std;

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H

enum Property { SelfLoop, WeightedEdges, MultipleEdges, DirectedEdges };

template <typename T>
class Graph {
public:
    //CONSTRUCTORS
    Graph();
    Graph(string new_title);
    Graph(string new_title, unordered_set<Property> new_properties);
    Graph(Graph<T> &other_graph);

    //DESTRUCTORS
    ~Graph();

    //ACCESSORS
    string getTitle() const;
    size_t vertexCount() const;
    size_t edgeCount() const;
    bool containsVertex(const Vertex<T> &v) const;
    bool containsEdge(const Edge<T> &e) const;
    bool containsEdge(const Vertex<T> &v1, const Vertex<T> &v2) const;
    Edge<T>& getEdge(const Vertex<T> &v1, const Vertex<T> &v2) const;
    unordered_set<Vertex<T>&> vertexSet() const;
    unordered_set<Edge<T>&> edgeSet() const;
    unordered_set<Vertex<T>&> vertexNeighborhood(const Vertex<T> &v) const;
    unordered_set<Edge<T>&> edgeNeighborhood(const Vertex<T> &v) const;

    //MUTATORS
    void set_title(const string &new_title);
    pair<Vertex<T>*, bool> addVertex(const Vertex<T> &new_vertex);
    pair<Vertex<T>*, bool> removeVertex(Vertex<T> &deleted_vertex);
    pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    pair<Edge<T>*, bool> removeEdge(const Edge<T> &e);
    pair<Edge<T>*, bool> removeEdge(Vertex<T> &v1, Vertex<T> &v2);


private:
    //MEMBER VARIABLES
    string title;
    unordered_set<Vertex<T>&> vertices;
    unordered_set<Edge<T>&> edges;
    unordered_set<Property> properties;

};


#endif //CGRAPH_GRAPH_H
