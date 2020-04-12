
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

    //OPERATOR OVERLOADING
    bool operator == (const Vertex<T> &v) const;
    bool operator != (const Vertex<T> &v) const;
    bool operator <= (const Vertex<T> &v) const;
    bool operator >= (const Vertex<T> &v) const;
    bool operator < (const Vertex<T> &v) const;
    bool operator > (const Vertex<T> &v) const;

    //ACCESSORS
    int getID() const;
    bool isMarked() const;
    bool hasCapacity() const;
    int getCapacity() const;
    bool equals(const Vertex<T> &other_vertex) const;

private:
    //MUTATORS
    void setMarked(bool new_marker);

    //MEMBER VARIABLES
    T val;
    int id;
    bool marker;
    optional<unsigned> capacity;

};

#endif //CGRAPH_NODE_H
