
#pragma once
#include "Edge.h"
#include <algorithm>
#include <limits>
#include <optional>
#include <unordered_set>
#include <vector>
using namespace std;

#ifndef CGRAPH_NODE_H
#define CGRAPH_NODE_H

//FORWARD DECLARATION
template <typename T>
class Graph;

template <typename T>
class Edge;

template <typename T = int>
class Vertex {
friend class Graph<T>;

public:
    //CONSTRUCTORS
    Vertex();
    Vertex(T new_val);
    Vertex(T new_val, unsigned new_capacity);
    Vertex(const Vertex<T> &other_vertex);

   //DESTRUCTORS
   ~Vertex();

    //ACCESSORS
    int getId() const;
    bool hasSelfLoop() const;
    bool isMarked() const;
    bool hasCapacity() const;
    unsigned getCapacity() const;
    unordered_set<Vertex<T>&> vertexNeighborhood() const;
    unordered_set<Edge<T>&> edgeNeighborhood() const;

private:
    //MUTATORS
    void setSelfloop(bool new_self_loop);
    void setMarked(bool new_marker);
    void increaseCapacity(unsigned new_capacity);
    void decreaseCapacity(unsigned new_capacity, unordered_set<Edge<T>&> to_delete);
    void decreaseCapacity(unsigned new_capacity, unordered_set<Vertex<T>&> to_delete);

    //MEMBER VARIABLES
    int id;
    bool self_loop;
    bool marker;
    optional<unsigned> capacity;
    T val;
    unordered_set<Edge<T>&> neighbors;

};

#endif //CGRAPH_NODE_H