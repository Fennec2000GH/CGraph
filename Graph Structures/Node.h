
#pragma once
#include "Edge.h"
#include <algorithm>
#include <optional>
#include <unordered_set>
#include <vector>
using namespace std;

#ifndef CGRAPH_NODE_H
#define CGRAPH_NODE_H

//FORWARD DECLARATION
template <typename T>
class Edge;

template <typename T = int>
class Node {
friend class Graph;

public:
    //CONSTRUCTORS
    Node();
    Node(T new_val);
    Node(T new_val, int new_capacity);

    //ACCESSORS
    int getId() const;
    virtual size_t getDegree() const = 0;
    bool hasSelfLoop() const;
    bool isMarked() const;
    bool hasCapacity() const;
    unsigned getCapacity() const;

protected:
    //MUTATORS
    void addEdge(Edge<T> &new_edge);
    void setSelfloop(bool new_self_loop);
    void setMarked(bool new_marker);
    void increaseCapacity(unsigned new_capacity);
    void decreaseCapacity(unsigned new_capacity, unordered_set<Edge<T>&> to_delete);
    void decreaseCapacity(unsigned new_capacity, unordered_set<Node<T>&> to_delete);

    //MEMBER VARIABLES
    int id;
    optional<unsigned> capacity;
    bool self_loop;
    bool marker;
    T val;
    unordered_set<Edge<T>&> neighbors;

};

#endif //CGRAPH_NODE_H
