
#pragma once
#include "Edge.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
using namespace std;

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H

//FORWARD DECLARATIONS
template <typename T>
class Data;

template <typename T>
class AdjacencyList;

template <typename T>
class AdjacencyMatrix;

//enum for graph type and features
enum Property { Cycleless, SelfLoops, Unmodifiable, WeightedEdges, MultipleEdges, DirectedEdges, MixedEdges };

template <typename T>
class Graph {
//FRIEND CLASS DECLARATIONS
friend class Data<T>;
friend class AdjacencyList<T>;
friend class AdjacencyMatrix<T>;

//ITERATOR RENAMES
using vertex_iterator = typename unordered_set<Vertex<T>&>::iterator;
using const_vertex_iterator = typename unordered_set<Vertex<T>&>::const_iterator;
using edge_iterator = typename unordered_set<Edge<T>&>::iterator;
using const_edge_iterator = typename unordered_set<Edge<T>&>::const_iterator;

public:
    //CONSTRUCTORS
    Graph();
    Graph(string new_title);
    Graph(string new_title, unordered_set<Property> new_properties);
    Graph(Graph<T> &other_graph);

    //DESTRUCTORS
    ~Graph();

    //ITERATORS
    vertex_iterator vbegin();
    vertex_iterator vend();
    const_vertex_iterator cvbegin();
    const_vertex_iterator cvend();
    edge_iterator ebegin();
    edge_iterator eend();
    const_edge_iterator cebegin();
    const_edge_iterator ceend();

    //ACCESSORS
    string getTitle() const;
    unsigned vertexCount() const;
    unsigned edgeCount() const;
    unsigned getDegree(const Vertex<T> &v) const;
    bool containsVertex(const Vertex<T> &v) const;
    bool containsEdge(const Edge<T> &e) const;
    bool containsMatchingEdge(const Edge<T> &e) const;
    bool containsEdge(const Vertex<T> &v1, const Vertex<T> &v2) const;
    bool isUndirected() const;
    bool isDirected() const;
    bool isUnweighted() const;
    bool isWeighted() const;
    bool isMixed() const;
    bool isModifiable() const;
    bool isMultigraph() const;
    bool isPseudograph() const;
    bool isSimple() const;
    bool allowsSelfLoops() const;
    bool hasSelfLoops() const;
    bool hasSelfLoops(const Vertex<T> &v) const;
    Edge<T>& getEdge(const Vertex<T> &v1, const Vertex<T> &v2) const;
    unordered_set<Vertex<T>&> vertexSet() const;
    unordered_set<Edge<T>&> edgeSet() const;
    unordered_set<Vertex<T>&> vertexNeighborhood(const Vertex<T> &v) const;
    unordered_set<Edge<T>&> edgeNeighborhood(const Vertex<T> &v) const;

    //MUTATORS
    void set_title(const string &new_title);
    virtual pair<Vertex<T>*, bool> addVertex();
    virtual pair<Vertex<T>*, bool> addVertex(const Vertex<T> &new_vertex);
    virtual pair<Vertex<T>*, bool> removeVertex(Vertex<T> &deleted_vertex);
    virtual pair<Edge<T>*, bool> addEdge(const Edge<T> &e);
    virtual pair<Edge<T>*, bool> addEdge(Vertex<T> &v1, Vertex<T> &v2);
    virtual unordered_set<pair<Edge<T>*, bool>> addAllEdges(edge_iterator first, edge_iterator last);
    virtual unordered_set<pair<Edge<T>*, bool>> addAllEdges(const unordered_set<Edge<T>&> edge_set);
    virtual pair<Edge<T>*, bool> removeEdge(const Edge<T> &e);
    virtual pair<Edge<T>*, bool> removeEdge(Vertex<T> &v1, Vertex<T> &v2);
    virtual void addProperty(Property new_property) = 0;

private:
    //MEMBER VARIABLES
    string title;
    unordered_set<Vertex<T>&> vertices;
    unordered_set<Edge<T>&> edges;
    unordered_set<Property> properties;

};

#endif //CGRAPH_GRAPH_H
