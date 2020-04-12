
#pragma once
#include "Vertex.h"
#include <iostream>
#include <optional>
using namespace std;

#ifndef CGRAPH_EDGE_H
#define CGRAPH_EDGE_H

//FORWARD DECLARATION
template <typename T>
class Graph;

template <typename T>
class Vertex;

template <typename T = int>
class Edge {
friend class Graph<T>;

public:
    //CONSTRUCTORS
    Edge(const Vertex<T> &new_vertex1, const Vertex<T> &new_vertex2);
    Edge(const Vertex<T> &new_vertex1, const Vertex<T> &new_vertex2, bool new_directed);
    Edge(const Vertex<T> &new_vertex1, const Vertex<T> &new_vertex2, bool new_directed, double new_weight);
    Edge(const Edge<T> &other_edge);

    //DESTRUCTORS
    ~Edge();

    //OPERATOR OVERLOADING
    bool operator == (const Edge<T> &e) const;
    bool operator != (const Edge<T> &e) const;
    bool operator <= (const Edge<T> &e) const;
    bool operator >= (const Edge<T> &e) const;
    bool operator < (const Edge<T> &e) const;
    bool operator > (const Edge<T> &e) const;

    //ACCESSORS
    Vertex<T>& first() const;
    Vertex<T>& second() const;
    bool isDirected() const;
    bool isWeighted() const;
    double getWeight() const;
    bool isSelfLoop() const;

private:
    //MUTATORS
    void setFirst(Vertex<T> &new_vertex1);
    void setSecond(Vertex<T> &new_vertex2);
    void setDirected(bool new_directed);
    void setWeight(double new_weight);

    //MEMBER VARIABLES
    Vertex<T> &v1;
    Vertex<T> &v2;
    bool directed;
    optional<double> weight; 

};


#endif //CGRAPH_EDGE_H
